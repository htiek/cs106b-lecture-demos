/* File: TreeDrawing.h
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * Type representing a drawing of a binary tree. If you have a pointer to the root
 * of a binary tree, you can write
 *
 *     TreeDrawing drawing = makeDrawingOf(root);
 *
 * to get the drawing. From there, you can call
 *
 *     drawing.draw(window);
 *
 * to draw it inside a window.
 *
 * The makeDrawingOf function is designed to be permissive about what it accepts,
 * so there are minimal requirements on what kinds of trees it'll work with. By
 * default, it assumes you're giving it a pointer to a struct with fields named
 * 'left' and 'right' that store the children. It also doesn't assume there's any
 * data in the nodes that you'd like to display.
 *
 * If this isn't the case - either you have some data per node you want to display
 * or you have different names for the child pointers - you can override this behavior
 * by passing extra information into the makeDrawingOf function.
 *
 *   1. If your node type has a field whose value you'd like to display on each
 *      of the nodes in the tree, you can pass its name as a second argument to
 *      makeDrawingOf. For example:
 *
 *          TreeDrawing drawing = makeDrawingOf(root, value);
 *
 *      will draw the binary tree and show what's stored in the field 'value' of
 *      each node.
 *
 *   2. If your node has child pointers not named left and right - say, they're named
 *      zero and one - you can pass in the names of those fields into makeDrawingOf.
 *      For example:
 *
 *          TreeDrawing drawing = makeDrawingOf(codingTree, zero, one);
 *
 * You can combine these together if you'd like. For example, suppose you have this
 * type representing a Huffman node:
 *
 *     struct HuffmanNode {
 *         char ch;
 *         HuffmanNode* zero;
 *         HuffmanNode* one;
 *     };
 *
 * You could then visualize the Huffman tree, seeing the values in each node, by making
 * a drawing like this:
 *
 *     TreeDrawing drawing = makeDrawingOf(codingTree, ch, zero, one);
 *
 * If you'd like more fine-grained control over what gets displayed in each node, or how
 * to navigate down the tree, you can alternatively explicitly call the TreeDrawing
 * constructors, passing in callbacks that perform this function.
 *
 * The TreeDrawing type does not have ownership of your tree, and assumes that the nodes
 * you created will still exist and be unmodified when it comes time to draw the tree. If
 * you destroy or rewire the tree after making a drawing, Weird Things can happen.
 */

#pragma once

#include "gtypes.h"
#include "gwindow.h"
#include <functional>
#include <memory>
#include <string>
#include <sstream>

/* Type: Labeler
 *
 * A type representing a function that takes in a node and outputs
 * a string used to label that node in a drawing of the tree.
 */
template <typename NodeType>
using Labeler = std::function<std::string (NodeType*)>;

/* Type: Walker
 *
 * A type representing a function that takes in a node and outputs
 * one of its children.
 */
template <typename NodeType>
using Walker = std::function<NodeType* (NodeType*)>;

class TreeDrawing {
private:
    /* Makes NodeType a dependent type so that Labeler and Walker won't be
     * used to do type inference on NodeType in later templates.
     */
    template <typename NodeType> struct Types {
        using Labeler = ::Labeler<NodeType>;
        using Walker  = ::Walker<NodeType>;
    };

    /* Detects whether the given type has left and right fields. */
    template <typename NodeType> struct HasLeftRightFields {
    private:
        typedef typename std::remove_cv<NodeType>::type CoreNode;

        /* These types must have different sizes. */
        struct Yes {
            char buffer[137];
        };
        using No = char;

        /* SFINAE check to see if two types are equal. */
        template <typename A, typename B> struct AreEqual {

        };
        template <typename A> struct AreEqual<A, A> {
            using result = int;
        };

        /* Make sure that the given type has a field of the appropriate
         * name whose type matches what we want it to be.
         */
        template <typename U> static Yes check(
            typename AreEqual<
                typename std::remove_reference<decltype(std::declval<U>().*&U::left)>::type,
                CoreNode*
            >::result
        );
        template <typename U> static No  check(...);

    public:
        static constexpr bool value
            = std::is_same<decltype(check<CoreNode>(0)), Yes>::value;
    };

    /* Left/right accessor function. */
    template <typename NodeType> static NodeType* defaultLeft(NodeType* root) {
        static_assert(HasLeftRightFields<NodeType>::value, "Tree type must have fields named 'left' and 'right' that point to its children. If you want to override this behavior, use makeDrawingOf and specify the names of the child pointers.");
        return root->left;
    }
    template <typename NodeType> static NodeType* defaultRight(NodeType* root) {
        static_assert(HasLeftRightFields<NodeType>::value, "Tree type must have fields named 'left' and 'right' that point to its children. If you want to override this behavior, use makeDrawingOf and specify the names of the child pointers.");
        return root->right;
    }

    /* Default printing function. */
    static std::string defaultLabeler(const void*) {
        return "";
    }

public:
    /* Constructs a TreeDrawing that doesn't draw anything. */
    TreeDrawing() = default;

    /* Constructs a TreeDrawing for the given tree. There are four
     * available forms you can use:
     *
     *    makeDrawingOf(root) will work assuming that root is a pointer
     *      to the root of a tree. The fields 'left' and 'right' need to
     *      be present so we can walk the tree. Nothing will be displayed
     *      on the nodes in the drawings; that is, this will just draw
     *      the shape of the tree.
     *
     *    makeDrawingOf(root, displayField) works as above, except that the
     *      field named 'displayField' will be shown as a label on the nodes.
     *
     *    makeDrawingOf(root, leftField, rightField) works like the one-arg
     *      version, except that we will use the names of the fields leftField
     *      and rightField instead of 'left' and 'right'.
     *
     *    makeDrawingOf(root, displayField, leftField, rightField) combines all
     *      these together.
     *
     * You can, of course, not use any of these and go through the public interface
     * of the constructors, but those require the use of lambda/callback functions.
     */
    #define makeDrawingOf(root, ...) /* something internal */

    /* Constructs a TreeDrawing of the given tree. Any type may be
     * used here as long as it has publicly-accessible fields named
     * 'left' and 'right' and uses nullptr to mark missing nodes.
     */
    template <typename NodeType>
    explicit TreeDrawing(NodeType* root);

    /* Constructs a TreeDrawing for the given tree that uses the provided
     * labeler.
     */
    template <typename NodeType>
    explicit TreeDrawing(NodeType* root,
                         typename Types<NodeType>::Labeler labeler);

    /* Constructs a TreeDrawing for the given tree that uses the provided
     * functions to walk the tree. This is useful if, for example, your
     * children are not named 'left' and 'right' and instead go by names like
     * 'zero' and 'one.'
     */
    template <typename NodeType>
    explicit TreeDrawing(NodeType* root,
                         typename Types<NodeType>::Walker left,
                         typename Types<NodeType>::Walker right);

    /* Constructs a TreeDrawing for the given tree that uses the provided
     * labeler and walker.
     */
    template <typename NodeType>
    explicit TreeDrawing(NodeType* root,
                         typename Types<NodeType>::Labeler labeler,
                         typename Types<NodeType>::Walker left,
                         typename Types<NodeType>::Walker right);

    /* Draws the tree, using as much space in the given window/canvas as
     * possible.
     */
    void draw(GWindow& window) const;
    void draw(GCanvas* canvas) const;

    /* Draws the tree at the given location within the indicated bounds. */
    void draw(GWindow& window, const GRectangle& bounds) const;
    void draw(GCanvas* canvas, const GRectangle& bounds) const;

private:
    /* Every node has unit diameter. */
    static const double kNodeRadius;

    /* Intended spacing between nodes on the same level. This is
     * the amount from the center of one node to the next. It's
     * two diameters of a node.
     */
    static const double kMinSeparation;

    /* Vertical spacing between nodes. */
    static const double kVerticalSpacing;

    /* Simpler representation of the tree that's fed as input to the actual
     * tree layout algorithm. This is done both to firewall off the .cpp from
     * the templates of the .h and to make things easier to read/maintain.
     * However, it's most definitely not necessary.
     */
    struct Node {
        std::shared_ptr<Node>        left;
        std::shared_ptr<Node>        right;
        std::function<std::string()> label;
        GPoint                       position;
    };

    /* Intermediate node structure for building a tree. */
    struct ThreadedNode {
        /* Left and right children. (We own our children.) */
        std::unique_ptr<ThreadedNode> leftChild;
        std::unique_ptr<ThreadedNode> rightChild;

        /* Next nodes along the left and right hulls of the tree. For nodes
         * that are on the actual hull of the tree, these will point to
         * the next node on the hull when moving in the indicated direction.
         * For nodes that are not on the actual hull of the tree, these values
         * will not be read.
         */
        ThreadedNode* leftHull  = nullptr;
        ThreadedNode* rightHull = nullptr;

        /* Signed distance from the node to the next nodes on the left/right
         * hull from this point.
         */
        double leftHullDistance  = -kMinSeparation / 2;
        double rightHullDistance =  kMinSeparation / 2;
    };

    /* Result from one level of the recursion. */
    struct ThreadedLayout {
        /* Pointer to tree root. */
        std::unique_ptr<ThreadedNode> root;

        /* Leftmost and rightmost leaves. */
        ThreadedNode* extremeLeft;
        double extremeLeftOffset;

        ThreadedNode* extremeRight;
        double extremeRightOffset;
    };

    /* Converts the original tree into our internal tree format. */
    template <typename NodeType> static std::shared_ptr<Node> convert(NodeType* root,
                                                                      Labeler<NodeType> labeler,
                                                                      Walker<NodeType> left,
                                                                      Walker<NodeType> right) {
        if (root == nullptr) return nullptr;

        return std::shared_ptr<Node>(new Node{
                                              convert(left(root),  labeler, left, right),
                                              convert(right(root), labeler, left, right),
                                              [=] () { return labeler(root); },
                                              {}
                                          });
    }

    /* Does the layout logic. */
    void performLayout();
    static ThreadedLayout layOutTree(Node* root);
    static void placeNodesIn(Node* inputRoot,
                             ThreadedNode* root,
                             double x = 0,
                             double y = 0);
    static GRectangle boundsFor(Node* root);

    /*** Data Members ***/

    /* Root of the reference tree. */
    std::shared_ptr<Node> root_;

    /* Radius of each node. */
    double nodeRadius_;

    /* Bounding box for all nodes. */
    GRectangle bounds_{0, 0, 0, 0};
};

/* * * * * Implementation Below This POint * * * * */

template <typename NodeType>
TreeDrawing::TreeDrawing(NodeType* root) :
    TreeDrawing(root, defaultLabeler) {

}

template <typename NodeType>
TreeDrawing::TreeDrawing(NodeType* root,
                         typename Types<NodeType>::Labeler labeler)
    : TreeDrawing(root, labeler,
                  defaultLeft<NodeType>,
                  defaultRight<NodeType>){

}

template <typename NodeType>
TreeDrawing::TreeDrawing(NodeType* root,
                         typename Types<NodeType>::Walker left,
                         typename Types<NodeType>::Walker right)
    : TreeDrawing(root, defaultLabeler, left, right){

}

template <typename NodeType>
TreeDrawing::TreeDrawing(NodeType* root,
                         typename Types<NodeType>::Labeler labeler,
                         typename Types<NodeType>::Walker left,
                         typename Types<NodeType>::Walker right) {
    root_ = convert(root, labeler, left, right);
    performLayout();
}

/**** makeDrawingOf implementation ****/

class TreeDrawingDetail {
public:
    /* Generic toString implementation. */
    template <typename T> static std::string toString(const T& value) {
        std::ostringstream builder;
        builder << value;
        return builder.str();
    }

    /* Not meant to be instantiated. */
    TreeDrawingDetail() = delete;
};

#undef makeDrawingOf

/* One-arg version */
#define MAKE_DRAWING_1(root) TreeDrawing(root)

/* Two-arg version extracts the given field */
#define MAKE_DRAWING_2(root, displayField) \
    TreeDrawing(root,\
                [](decltype(root) node) {  return TreeDrawingDetail::toString(node->displayField); })

/* Three-arg version uses the given left/right fields. */
#define MAKE_DRAWING_3(root, leftField, rightField) \
    TreeDrawing(root, \
                [](decltype(root) node) { return node->leftField; },  \
                [](decltype(root) node) { return node->rightField; })


/* Four-arg version uses all these. */
#define MAKE_DRAWING_4(root, displayField, leftField, rightField) \
    TreeDrawing(root, \
                [](decltype(root) node) { return TreeDrawingDetail::toString(node->displayField); },\
                [](decltype(root) node) { return node->leftField; },  \
                [](decltype(root) node) { return node->rightField; })


/* Macro to select which one to use. */
#define SELECTOR(V1, V2, V3, V4, CHOSEN, ...) CHOSEN
#define SELECT(...) SELECTOR(__VA_ARGS__, MAKE_DRAWING_4, MAKE_DRAWING_3, MAKE_DRAWING_2, MAKE_DRAWING_1)(__VA_ARGS__)
#define makeDrawingOf(...) SELECT(__VA_ARGS__)
