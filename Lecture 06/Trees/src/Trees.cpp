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
#include "console.h"
using namespace std;









/* Constants controlling the window size. */
const double kWindowWidth = 1000;
const double kWindowHeight = 800;

/* Main program */
int main() {
	GWindow window(kWindowWidth, kWindowHeight);
    window.setColor("Black");
    window.setExitOnClose(true);
    window.setTitle("Trees!");

    /* Keep drawing trees! */
    while (true) {
        window.clearCanvasPixels();

        double x = window.getWidth()  / 2.0;
        double y = window.getHeight();
        double height = window.getHeight();

        double angle = 90.0; // Up
        int    order = 8;    // Chosen arbitrarily and capriciously!

        drawTree(window, x, y, height, angle, order);
        pause(2000);
    }
}






