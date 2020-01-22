/*
 * File: Trees.cpp
 * ---------------
 * A program that generates trees using recursion!
 */

#include <iostream>
#include <string>
#include "random.h"
#include "gwindow.h"
#include "gobjects.h"
#include "gthread.h"
using namespace std;

GPoint drawPolarLine(GWindow& window,
                     double x, double y,
                     double radius,
                     double angle);

/* Draws a tree at the given position, of the given height,
 * at the specified angle, and having the indicated order.
 *
 * Returns the number of lines drawn.
 */
int drawTree(GWindow& window,
             double x, double y,
             double height,
             double angle,
             int order) {
    /* Base case: A tree of order 0 consists of nothing
     * at all and has no lines.
     */
    if (order == 0) {
        return 0;
    }
    /* Recursive case: Draw two, and possibly three, trees
     * hanging off of the trunk.
     */
    else {
        /* Draw the trunk. This function returns the line's
         * endpoint so that we know where to resume.
         */
        GPoint treeTop = drawPolarLine(window, x, y, height / 2, angle);
        int numLinesDrawn = 1;

        /* Compute information about the next trees to draw. */
        double newX = treeTop.getX();
        double newY = treeTop.getY();
        double newHeight = height / 2;
        int    newOrder  = order - 1;

        /* Draw two trees, each of which hangs off at a slight
         * angle.
         *
         * As we do, update the number of lines drawn in the
         * course of drawing this tree to reflect how many
         * lines were rendered in each subtree.
         */
        numLinesDrawn += drawTree(window, newX, newY, newHeight, angle + 30, newOrder);
        numLinesDrawn += drawTree(window, newX, newY, newHeight, angle - 30, newOrder);

        /* Optionally draw one more tree. */
        if (randomChance(0.5)) {
            numLinesDrawn += drawTree(window, newX, newY, newHeight, angle, newOrder);
        }

        return numLinesDrawn;
    }
}


/* Constants controlling the window size. */
const double kWindowWidth = 1000;
const double kWindowHeight = 800;

void clear(GWindow& window);
void repaint(GWindow& window);

/* Main program */
int main() {
	GWindow window(kWindowWidth, kWindowHeight);
    window.setColor("Black");
    window.setExitOnClose(true);
    window.setTitle("Trees!");

    /* Keep drawing trees! */
    while (true) {
        clear(window);

        double treeRootX  = window.getWidth()  / 2.0;
        double treeRootY  = window.getHeight();
        double treeHeight = window.getHeight();

        int numLinesDrawn = drawTree(window,
                                     treeRootX, treeRootY,
                                     treeHeight,
                                     90.0, 8);
        cout << "Lines in this tree: " << numLinesDrawn << endl;
        pause(2000);
    }
}

/* This somewhat clunky-looking function is
 * designed to repaint the window immediately
 * so that if we step through this code in
 * the debugger, the window is responsive and
 * shows the lines we're drawing. This is basically
 * a hack around our libraries; you aren't
 * expected to understand how this works.
 */
void repaint(GWindow& window) {
    GThread::runOnQtGuiThread([&] {
        window.repaint();
    });
}

/* Clears the graphics contents from the window. */
void clear(GWindow& window) {
    window.clearCanvasPixels();
    repaint(window);
}

/* This is a modified version of drawPolarLine that is
 * specifically designed to play nicely with the debugger.
 * You aren't expected to understand how this works.
 */
GPoint drawPolarLine(GWindow& window,
                     double x, double y,
                     double radius,
                     double angle) {
    GPoint result = window.drawPolarLine(x, y, radius, angle);
    repaint(window);
    return result;
}
