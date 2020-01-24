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

void drawSquare(GWindow& window,
                double x, double y,
                double size);

void drawSierpinskiCarpet(GWindow& window,
                          double x, double y,
                          double size,
                          int order) {
    if (order == 0) {
        drawSquare(window, x, y, size);
    } else {
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (row != 1 || col != 1) {
                    double newX = x + col * size / 3;
                    double newY = y + row * size / 3;

                    drawSierpinskiCarpet(window,
                                         newX, newY,
                                         size / 3,
                                         order - 1);
                }
            }
        }
    }
}


/* Constants controlling the window size. */
const double kWindowWidth  = 1000;
const double kWindowHeight = 800;

/* Margin from window sides to content area. */
const double kMargin = 40;

/* Colors! */
const string kBackgroundColor = "white";
const string kRectangleColor  = "#400080";

/* Maximum order to draw. */
const double kMaxOrder = 5;

void clear(GWindow& window);
void repaint(GWindow& window);

/* Main program */
int main() {
    GWindow window(kWindowWidth, kWindowHeight);
    window.setExitOnClose(true);

    while (true) {
        for (int order = 0; order <= kMaxOrder; order++) {
            clear(window);
            window.setTitle("Sierpinski Carpet of Order " + to_string(order));

            /* Determine the width and height of the square to draw. */
            double width  = window.getCanvasWidth()  - 2 * kMargin;
            double height = window.getCanvasHeight() - 2 * kMargin;
            double size = min(width, height);

            /* Determine position. */
            double x = (window.getCanvasWidth()  - size) / 2.0;
            double y = (window.getCanvasHeight() - size) / 2.0;

            drawSierpinskiCarpet(window, x, y, size, order);
            pause(2000);
        }
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
    window.setColor(kBackgroundColor);
    window.fillRect(0, 0, window.getCanvasWidth(), window.getCanvasHeight());
    repaint(window);
}

void drawSquare(GWindow& window,
                double x, double y,
                double size) {
    window.setColor(kRectangleColor);
    window.fillRect(x, y, size, size);
    repaint(window);
}
