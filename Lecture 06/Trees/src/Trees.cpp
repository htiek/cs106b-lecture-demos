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
#include "gevents.h"
using namespace std;

const double kWindowWidth = 1000;
const double kWindowHeight = 800;

const double kMinAngle = 20;
const double kMaxAngle = 60;

const int kTreeOrder = 8;

void drawTreeRec(GWindow& window,
                 double x, double y,
                 double length,
                 double angle,
                 int order) {
    if (order == 0) return;

    GPoint endpoint = window.drawPolarLine(x, y, length / 2, angle);

    drawTreeRec(window,
                endpoint.getX(), endpoint.getY(),
                length / 2,
                angle + randomReal(kMinAngle, kMaxAngle),
                order - 1);
    drawTreeRec(window,
                endpoint.getX(), endpoint.getY(),
                length / 2,
                angle - randomReal(kMinAngle, kMaxAngle),
                order - 1);
}

void drawTree(GWindow& window, double x, double y, double length) {
    drawTreeRec(window, x, y, length, 90, kTreeOrder);
}

/* Main program */
int main() {
	GWindow window(kWindowWidth, kWindowHeight);
    window.setColor("Black");
    window.setExitOnClose(true);
    window.setTitle("Trees!");

    /* Keep drawing trees! */
    while (true) {
        window.clearCanvasPixels();
        drawTree(window, window.getWidth() / 2, window.getHeight(), window.getHeight());
        pause(2000);
    }
}






