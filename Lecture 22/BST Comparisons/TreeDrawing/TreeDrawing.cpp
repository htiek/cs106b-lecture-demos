/* File: TreeDrawing.cpp
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * Implementation of the binary tree layout algorithm from "Tidier Drawings of Trees" by
 * Edward Reingold and John Tilford. The algorithm works bottom up. For each subtree, it
 * forms the convex hull of the tree, represented as two chains (a chain around the left
 * of the tree and a chain around the right of the tree), maintaining information about
 * the relative offsets between nodes. When joining two trees together, the trees are
 * positioned such that their convex hulls have a certain minimum horizontal separation,
 * then the hulls are updated.
 *
 * The runtime for the algorithm is O(n), where n is the number of nodes in the tree.
 */
#include "TreeDrawing.h"
#include <utility>
#include <limits>
#include <algorithm>

/*************************************************************************
 *************************************************************************
 *************             Node Placement Logic              *************
 *************************************************************************
 *************************************************************************/

/* Every node has unit diameter. */
const double TreeDrawing::kNodeRadius = 0.5;

/* Intended spacing between nodes on the same level. This is
 * the amount from the center of one node to the next. It's
 * two diameters of a node.
 */
const double TreeDrawing::kMinSeparation = 4 * kNodeRadius;

/* Vertical spacing between nodes. */
const double TreeDrawing::kVerticalSpacing = 4 * kNodeRadius;

void TreeDrawing::performLayout() {
    nodeRadius_ = kNodeRadius; // Always

    /* Lay out the tree and find the root. */
    auto layout = layOutTree(root_.get());
    auto layoutRoot = std::move(layout.root);

    /* Walk the tree to position each node in logical space. */
    placeNodesIn(root_.get(), layoutRoot.get());

    /* Compute a bounding box. */
    bounds_ = boundsFor(root_.get());
}

/* Runs the layout algorithm. Each recursive call returns a pointer to a threaded
 * tree node, as well as the extreme leaves in the tree.
 */
TreeDrawing::ThreadedLayout TreeDrawing::layOutTree(Node* root) {
    /* Base Case: If the tree is empty, we don't need to do anything. */
    if (root == nullptr) {
        return { nullptr, nullptr, 0, nullptr, 0 };
    }
    /* Base Case: If we are a leaf, no recursion is needed. */
    else if (root->left == nullptr && root->right == nullptr) {
        ThreadedNode* result = new ThreadedNode(); // Defaults are all okay here

        /* We are both the leftmost and rightmost leaf. */
        return { std::unique_ptr<ThreadedNode>(result), result, 0, result, 0 };
    }
    /* Base Case: If we only have a right child, just lay that part out. */
    else if (root->left == nullptr) {
        ThreadedNode* result = new ThreadedNode();

        /* Lay out the right subtree. */
        auto rightResult   = layOutTree(root->right.get());

        /* It's now our right child. */
        result->rightChild = std::move(rightResult.root);

        /* Our left and right hulls now continue to the node below us. */
        result->leftHull = result->rightHull = result->rightChild.get();

        /* The distance to each is the regular offset, in a positive direction. */
        result->leftHullDistance = result->rightHullDistance = kMinSeparation / 2;

        /* The extreme points are copied from the right, and are shifted
         * over by the distance from the root node to the new nodes.
         */
        return {
            std::unique_ptr<ThreadedNode>(result),
            rightResult.extremeLeft,
            rightResult.extremeLeftOffset + result->leftHullDistance,
            rightResult.extremeRight,
            rightResult.extremeRightOffset + result->leftHullDistance
        };
    }
    /* Base Case: If we just have a left child, lay it out as well. */
    else if (root->right == nullptr) {
        ThreadedNode* result = new ThreadedNode();

        /* Lay out the left subtree. */
        auto leftResult   = layOutTree(root->left.get());

        /* It's now our left child. */
        result->leftChild = std::move(leftResult.root);

        /* Our left and right hulls now continue to the node below us. */
        result->leftHull = result->rightHull = result->leftChild.get();

        /* The distance to each is the regular offset, in a negative direction. */
        result->leftHullDistance = result->rightHullDistance = -kMinSeparation / 2;

        /* The extreme points are copied from the left, and are shifted
         * over by the distance from the root node to the new nodes.
         */
        return {
            std::unique_ptr<ThreadedNode>(result),
            leftResult.extremeLeft,
            leftResult.extremeLeftOffset + result->leftHullDistance,
            leftResult.extremeRight,
            leftResult.extremeRightOffset + result->leftHullDistance
        };
    }
    /* Recursive Case: Lay out both subtrees and link them together. */
    else {
        /* Start by laying out the children. */
        auto leftLayout  = layOutTree(root->left.get());
        auto rightLayout = layOutTree(root->right.get());

        /* Our left/right children and left/right hulls are now these
         * nodes.
         */
        auto* result = new ThreadedNode();
        result->leftChild  = std::move(leftLayout.root);
        result->rightChild = std::move(rightLayout.root);
        result->leftHull   = result->leftChild.get();
        result->rightHull  = result->rightChild.get();

        /* We will be working with two coordinate systems: one relative to
         * the root of the left subtree, and one relative to the root of the
         * right subtree. Each of those trees will be placed to the left and
         * right of the overall root. These next values give us the offsets
         * from the overall tree root to the roots of those trees.
         */
        double leftRootX  = -kMinSeparation / 2;
        double rightRootX = +kMinSeparation / 2;

        /* Coordinates, within the left and right coordinate systems, of
         * the current nodes in those spaces.
         */
        double leftX  = 0;
        double rightX = 0;

        /* The current nodes in the left and right trees. */
        auto* left  = result->leftHull;
        auto* right = result->rightHull;

        while (left->rightHull != nullptr && right->leftHull != nullptr) {
            /* Take a step downward along the hulls, updating the positions
             * as we go.
             */
            leftX  += left->rightHullDistance;
            left    = left->rightHull;
            rightX += right->leftHullDistance;
            right   = right->leftHull;

            /* Convert from local space to global space, then measure the separation. */
            double distance = (rightX + rightRootX) - (leftX + leftRootX);

            /* If they're too close, we need to push them apart. */
            if (distance < kMinSeparation) {
                double delta  = kMinSeparation - distance;

                /* Push each from the other. */
                leftRootX  -= delta / 2;
                rightRootX += delta / 2;
            }
        }

        /* The two trees are now equidistantly separated from the center
         * point. We now know their offsets.
         */
        result->leftHullDistance  = leftRootX;
        result->rightHullDistance = rightRootX;

        /* At this point, we've walked as far down the hulls as we can.
         * We now may need to update the hulls after the merge. To do
         * this, we're going to look at the rightmost node in the right
         * tree and the leftmost node in the left tree and see if they
         * need to be linked in. We also need to track the extreme nodes
         * in the bottom layer of the overall tree.
         */
        ThreadedNode* extremeLeft;
        ThreadedNode* extremeRight;
        double        extremeLeftDistance;
        double        extremeRightDistance;

        /* Left tree continues. */
        if (left->rightHull != nullptr) {
            /* The right subtree's extreme right node previously was the
             * terminus of the right hull. But now that the trees are linked,
             * the right hull actually continues along the right hull of the
             * left tree.
             */
            rightLayout.extremeRight->rightHull = left->rightHull;

            /* Calculate the distance from the node on the extreme right to
             * the next node on the right hull. This involves some coordinate
             * system changes.
             *
             * 1. Change the position of the extreme right leaf of the right
             *    tree from right tree coordinates to global coordinates.
             * 2. Change the position of the next node on the left tree's
             *    right hull from left tree coordinates to global coordinates.
             * 3. Compute the distance between them.
             */
            double extremeRightGlobal = rightRootX + rightLayout.extremeRightOffset;
            double nextHullGlobal     = leftRootX  + leftX + left->rightHullDistance;
            rightLayout.extremeRight->rightHullDistance = nextHullGlobal - extremeRightGlobal;

            /* The extreme nodes come from the left. */
            extremeLeft  = leftLayout.extremeLeft;
            extremeRight = leftLayout.extremeRight;

            /* Their offsets are shifted by the left tree offset. */
            extremeLeftDistance  = leftLayout.extremeLeftOffset  + leftRootX;
            extremeRightDistance = leftLayout.extremeRightOffset + leftRootX;
        }
        /* Right tree continues. */
        else if (right->leftHull != nullptr) {
            /* Analogous to above. */
            leftLayout.extremeLeft->leftHull = right->leftHull;

            double extremeLeftGlobal = leftRootX  + leftLayout.extremeLeftOffset;
            double nextHullGlobal    = rightRootX + rightX + right->leftHullDistance;
            leftLayout.extremeLeft->leftHullDistance = nextHullGlobal - extremeLeftGlobal;

            extremeLeft  = rightLayout.extremeLeft;
            extremeRight = rightLayout.extremeRight;

            extremeLeftDistance  = rightLayout.extremeLeftOffset  + rightRootX;
            extremeRightDistance = rightLayout.extremeRightOffset + rightRootX;
        }
        /* Both trees ended. */
        else {
            /* No threads are needed because the hulls are correct as-is.
             * The extreme nodes come from the extreme nodes of
             * the two trees.
             */
            extremeLeft  = leftLayout.extremeLeft;
            extremeRight = rightLayout.extremeRight;

            extremeLeftDistance  = leftLayout.extremeLeftOffset  + leftRootX;
            extremeRightDistance = leftLayout.extremeRightOffset + rightRootX;
        }

        /* Propagate our results upward. */
        return {
            std::unique_ptr<ThreadedNode>(result),
            extremeLeft,  extremeLeftDistance,
            extremeRight, extremeRightDistance
        };
    }
}

/* Given relative offsets, places all nodes in the tree. We've built up
 * a parallel tree to the input tree, so we'll walk both simultaneously.
 */
void TreeDrawing::placeNodesIn(Node* inputRoot,
                               ThreadedNode* root,
                               double x,
                               double y) {
    if (root == nullptr) return;

    /* Position the node itself. */
    inputRoot->position = { x, y };

    /* Recursively place nodes to the left and right. */
    placeNodesIn(inputRoot->left.get(),  root->leftChild.get(),  x + root->leftHullDistance,  y + kVerticalSpacing);
    placeNodesIn(inputRoot->right.get(), root->rightChild.get(), x + root->rightHullDistance, y + kVerticalSpacing);
}

/* Computes a bounding box for the given set of points. The bounding box is inflated by
 * one radius in each direction.
 */
GRectangle TreeDrawing::boundsFor(Node* root) {
    /* Gather all points. */
    Set<Node*> nodes;
    std::function<void(Node*)> recListNodes = [&](Node* root) {
        if (root != nullptr) {
            nodes += root;
            recListNodes(root->left.get());
            recListNodes(root->right.get());
        }
    };
    recListNodes(root);

    /* Edge Case: Empty trees get trivial bounds. */
    if (nodes.isEmpty()) {
        /* Everything does indeed lie in this box. Setting the dimensions
         * to 1 avoids a zero-divide in graphics code not expecting this to be
         * empty.
         */
        return { 0, 0, 1, 1 };
    }

    /* Find the min/max x/y coordinates. */
    double minX =  std::numeric_limits<double>::infinity();
    double minY =  std::numeric_limits<double>::infinity();
    double maxX = -std::numeric_limits<double>::infinity();
    double maxY = -std::numeric_limits<double>::infinity();

    for (auto node: nodes) {
        minX = std::min(minX, node->position.x);
        minY = std::min(minY, node->position.y);
        maxX = std::max(maxX, node->position.x);
        maxY = std::max(maxY, node->position.y);
    }

    /* Compute a bounding box. */
    double width  = maxX - minX;
    double height = maxY - minY;

    /* Inflate it by one node radius for drawing purposes. */
    return {
        minX - kNodeRadius,
        minY - kNodeRadius,
        width  + 2 * kNodeRadius,
        height + 2 * kNodeRadius
    };
}

/*************************************************************************
 *************************************************************************
 *************                Rendering Logic                *************
 *************************************************************************
 *************************************************************************/

namespace {
    /* Graphics Parameters */
    const char kBackgroundColor[] = "white";
    const char kLineColor[]       = "black";
    const char kNodeColor[]       = "#ffffc0";
    const char kFontColor[]       = "#000000";
    const double kLineWidth       = 2.0;

    /* Pick a Unicode-rich monospace font that is likely to exist on the
     * system so we don't get annoying "populating font family aliases"
     * warnings.
     */
    const char kFont[] =
        #ifdef __APPLE__
            "Lucida Grande"
        #elif defined(_WIN32)
            "Lucida Sans Unicode"
        #else
            "Monospace"
        #endif
    ;

    const int kInitialFontSize = 24;

    void drawTextIn(GCanvas* canvas, const std::string& text, const GRectangle& bounds) {
        GText label(text);
        label.setColor(kFontColor);

        for (int fontSize = kInitialFontSize; fontSize > 0; fontSize--) {
            std::string font = kFont + std::string("-") + std::to_string(fontSize);
            label.setFont(font);

            /* Does it fit? If so, draw it. */
            if (label.getWidth() <= bounds.width && label.getHeight() <= bounds.height) {
                double x = bounds.x + (bounds.width  - label.getWidth())  / 2.0;

                /* Height is the sum of the font ascent/descent. */
                int height = label.getFontAscent() + label.getFontDescent();

                /* Offset by font ascent to get everything centered. */
                double y = bounds.y + (bounds.height - height) / 2.0 + label.getFontAscent();

                label.setLocation(x, y);
                canvas->draw(&label);
                return;
            }
        }
    }
}

/* Drawing in a window fills the window. */
void TreeDrawing::draw(GWindow& window) const {
    draw(window, {
             0, 0,
             window.getCanvasWidth(),
             window.getCanvasHeight()
         });
}

/* Drawing in a canvas fills the canvas. */
void TreeDrawing::draw(GCanvas* canvas) const {
    draw(canvas, {
             0, 0, canvas->getWidth(), canvas->getHeight()
         });
}

/* To draw inside a window, draw in its canvas. */
void TreeDrawing::draw(GWindow& window, const GRectangle& bounds) const {
    draw(window.getCanvas(), bounds);
}

void TreeDrawing::draw(GCanvas* canvas, const GRectangle& bounds) const {
    /* Clear our area. */
    canvas->setColor(kBackgroundColor);
    canvas->fillRect(bounds);

    /* No tree? No problem! Just don't draw anything. */
    if (!root_) return;

    /* Figure out the aspect ratio and bounds to use. */
    double width  = bounds.width;
    double height = bounds.height;

    double aspectRatio = bounds_.width / bounds_.height;

    /* Too tall. */
    if (width / height > aspectRatio) {
        width = aspectRatio * height;
    }
    /* Too wide. */
    else {
        height = width / aspectRatio;
    }

    double baseX  = bounds.x + (bounds.width  -  width) / 2.0;
    double baseY  = bounds.y + (bounds.height - height) / 2.0;

    double xScale = width  / bounds_.width;
    double yScale = height / bounds_.height;

    /* Helper function: node to center point. */
    auto centerOf = [&](Node* node) -> GPoint {
        GPoint result = {
            baseX + (node->position.x - bounds_.x) * xScale,
            baseY + (node->position.y - bounds_.y) * yScale
        };
        return result;
    };

    /* Recursively draw the tree nodes. */
    std::function<void (Node*)> recDrawNodes = [&](Node* node) {
        if (node == nullptr) return;

        /* Draw the node. */
        auto center = centerOf(node);
        auto xRad   = nodeRadius_ * xScale;
        auto yRad   = nodeRadius_ * yScale;

        GRectangle bounds = {
            center.x - xRad, center.y - yRad, 2 * xRad, 2 * yRad
        };

        GOval oval(bounds.x, bounds.y, bounds.width, bounds.height);
        oval.setFilled(true);
        oval.setColor(kLineColor);
        oval.setFillColor(kNodeColor);
        oval.setLineWidth(kLineWidth);
        canvas->draw(&oval);

        /* Draw the label. Fit everything inside a square inscribed within the circle. This
         * assumes everything is in a 1:1 aspect ratio, so the scale is the same in
         * both directions.
         */
        double newRadius = sqrt(0.5) * xScale * nodeRadius_;
        GRectangle textBounds = {
            center.x - newRadius, center.y - newRadius, 2 * newRadius, 2 * newRadius
        };

        drawTextIn(canvas, node->label(), textBounds);

        /* Recursion! */
        recDrawNodes(node->left.get());
        recDrawNodes(node->right.get());
    };

    /* Recursively draw tree lines. */
    std::function<void (Node*)> recDrawLines = [&](Node* node) {
        if (node == nullptr) return;

        if (node->left != nullptr) {
            auto p0 = centerOf(node);
            auto p1 = centerOf(node->left.get());

            GLine line(p0, p1);
            line.setColor(kLineColor);
            line.setLineWidth(kLineWidth);
            canvas->draw(&line);

            recDrawLines(node->left.get());
        }
        if (node->right != nullptr) {
            auto p0 = centerOf(node);
            auto p1 = centerOf(node->right.get());

            GLine line(p0, p1);
            line.setColor(kLineColor);
            line.setLineWidth(kLineWidth);
            canvas->draw(&line);

            recDrawLines(node->right.get());
        }
    };

    recDrawLines(root_.get());
    recDrawNodes(root_.get());
}
