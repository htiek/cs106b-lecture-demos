#pragma once

#include "TreeDrawing/TreeDrawing.h"

namespace treegraphics_detail {
    GWindow& window();
}

template <typename NodeType> void drawTree(const NodeType* tree) {
    auto drawing = makeDrawingOf(tree, value);
    drawing.draw(treegraphics_detail::window());
    treegraphics_detail::window().repaint();
}
