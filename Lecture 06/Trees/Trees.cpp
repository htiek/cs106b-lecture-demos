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

/* Draws a line from the position (x, y) of length 'length,'
 * in the direction given by angle. The function then returns
 * the endpoint of the line.
 */
GPoint drawPolarLine(double x, double y,
                     double length,
                     double angle);

/* Draws a tree in the given window where
 *
 *  1. The base of the tree is at (x, y),
 *  2. The height of the tree is (roughly) length,
 *  3. The tree grows at the given angle from its
 *     base, and
 *  4. The order of the tree is given by the order
 *     parameter.
 */
void drawTree(double x, double y,
              double length,
              double angle,
              int order) {
}
























/* Constants controlling the window size. */
const double kWindowWidth = 1000;
const double kWindowHeight = 700;

/* Ewww, global variables! You aren't allowed to use these.
 * We are, but just for this one demo. :-)
 */
GWindow* theWindow;

/* Graphics routines to clear the screen and redraw everything all at once. */
void clear();
void repaintWindow();

/* Level of indirection to call drawTree appropriately. */
void callDrawTree(double x, double y, double height, double angle, int order,
                  void drawTree(double, double, double, double, int)) {
    drawTree(x, y, height, angle, order);                 
}

void callDrawTree(double x, double y, double height, double angle, int order,
                  int drawTree(double, double, double, double, int)) {
    int numLinesDrawn = drawTree(x, y, height, angle, order);
    cout << "   Lines in that tree: " << numLinesDrawn << endl;                
}

/* Main program */
int main() {
    GWindow window(kWindowWidth, kWindowHeight);
    window.setColor("Black");
    window.setExitOnClose(true);
    window.setTitle("Trees!");
    theWindow = &window;

    /* Keep drawing trees! */
    while (true) {
        clear();

        /* Position the tree at the bottom of the window. */
        double treeRootX  = window.getCanvasWidth()  / 2.0;
        double treeRootY  = window.getCanvasHeight();
        double treeHeight = window.getCanvasHeight();


        /* Magic level of indirection so that we either call the void function
         * or call the int function and print the number of lines.
         */
        callDrawTree(treeRootX, treeRootY, treeHeight, 90.0, 8, drawTree);
        pause(2000);
    }
}




/* * * * * Graphics logic below this point * * * * */






/* This somewhat clunky-looking function is
 * designed to repaint the window immediately
 * so that if we step through this code in
 * the debugger, the window is responsive and
 * shows the lines we're drawing. This is basically
 * a hack around our libraries; you aren't
 * expected to understand how this works.
 */
void repaintWindow() {
    GThread::runOnQtGuiThread([] {
        theWindow->repaint();
    });
}

/* Clears the graphics contents from the window. */
void clear() {
    theWindow->clearCanvasPixels();
    repaintWindow();
}

/* This is a modified version of drawPolarLine that is
 * specifically designed to play nicely with the debugger.
 * You aren't expected to understand how this works.
 */
GPoint drawPolarLine(double x, double y,
                     double length,
                     double angle) {
    GPoint result = theWindow->drawPolarLine(x, y, length, angle);
    repaintWindow();
    return result;
}
