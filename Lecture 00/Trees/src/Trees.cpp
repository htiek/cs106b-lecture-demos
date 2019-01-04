/*
 * File: Trees.cpp
 * ---------------
 * A program that generates trees using recursion!
 */

#include "random.h"
#include "gwindow.h"
#include "gobjects.h"
#include <cmath>
using namespace std;

namespace { // Private helper functions and constants
    /* Branching angle. */
    const double kMinAngle = -70 * M_PI / 180;
    const double kMaxAngle = +70 * M_PI / 180;

    /* Base angle */
    const double kBaseAngle = -90 * M_PI / 180;

    /* Number of branches at each tree. */
    const int kMinBranchingFactor = 4;
    const int kMaxBranchingFactor = 6;

    /* Maximum level of the tree. */
    const int kMaxLevel = 7;

    /* What fraction of the length to assign to the current branch versus the rest of the
     * trees. Higher values mean that the trunk is longer and the branches are shorter;
     * smaller values mean that the trunk is shorter and the branches are longer.
     */
    const double kTrunkFraction = 0.4;

    /* Colors to use for drawing the tree */
    const string kBranchColors[kMaxLevel + 1] = {
       "whoops!", // This is never used
       "#006000", // Leaves are green
       "#008000", // Below that is slightly brighter.
       "#00a000", // Below that is brighter green. Thanks, Bob Ross!
       "#904000", // Branches are mostly brown
       "#a05000",
       "#905000",
       "#984800",
    };

    /* Line thicknesses to use for drawing the tree. */
    const int kBranchWidths[kMaxLevel + 1] = {
        0,
        1,
        2,
        3,
        5,
        8,
        13,
        21
    };

    /* Draws a line from the source to the destination, using the specified color. */
    void drawLine(GWindow& window, GPoint source, GPoint dest, string color, int width) {
        GLine line(source, dest);
        line.setLineWidth(width);
        line.setColor(color);
        window.draw(line);
    }
}

void recDrawTree(GWindow& window, GPoint source, double height, double theta, int order) {
    /* An order-0 tree consists of no leaves or branches. */
    if (order == 0) return;

    /* We're next going to draw a line representing the trunk of the tree. To work out the
     * coordinates, we'll factor in our current location, length, and angle.
     */
    GPoint dest = {
        source.getX() + kTrunkFraction * height * cos(theta),
        source.getY() + kTrunkFraction * height * sin(theta)
    };
    drawLine(window, source, dest, kBranchColors[order], kBranchWidths[order]);

    /* Determine how many child trees we should have. */
    int numChildren = randomInteger(kMinBranchingFactor, kMaxBranchingFactor);

    /* Recursively draw all child trees. */
    for (int i = 0; i < numChildren; i++) {
        recDrawTree(window,                                   // Draw in the same window,
                    dest,                                     // at the end of the trunk,
                    (1 - kTrunkFraction) * height,            // smaller than before,
                    theta + randomReal(kMinAngle, kMaxAngle), // rotated at a random angle, and
                    order - 1);                               // of slightly smaller order.
    }
}

void drawTree(GWindow& window, double x, double y, double height) {
    recDrawTree(window, {x, y}, height, kBaseAngle, kMaxLevel);
}

