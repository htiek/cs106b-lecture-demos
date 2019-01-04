#ifndef Trees_Included
#define Trees_Included

#include "gwindow.h"

/**
 * Draws a fractal tree in the specified window and the specified coordinates.
 *
 * @param window Where to draw the tree.
 * @param x      The x coordinate of the base of the tree.
 * @param y      The y coordinate of the base of the tree.
 * @param height The rough height of the tree.
 */
void drawTree(GWindow& window, double x, double y, double height);

#endif
