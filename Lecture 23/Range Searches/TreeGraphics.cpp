#include "TreeGraphics.h"
using namespace std;

namespace {
    /* The actual graphics window. Yes, this uses global variables. No, that's
     * not a good idea in general. We did this so that the lecture code for
     * trees is as clean as possible.
     */
    static GWindow* theWindow = nullptr;

    const int kWindowWidth  = 1920;
    const int kWindowHeight = 1000;

    void initGraphics() {
        theWindow = new GWindow(kWindowWidth, kWindowHeight);
        theWindow->setTitle("Binary Search Trees");
        theWindow->setExitOnClose(true);
        theWindow->setVisible(true);
        theWindow->setAutoRepaint(false);
    }

}

GWindow& treegraphics_detail::window() {
    if (!theWindow) {
        initGraphics();
    }
    return *theWindow;
}
