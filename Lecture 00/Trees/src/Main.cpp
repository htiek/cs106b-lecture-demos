#include "Trees.h"
#include "gwindow.h"
#include <string>
using namespace std;

namespace {
    /* Window parameters. */
    const double kWindowWidth = 1000;
    const double kWindowHeight = 800;
    const string kWindowTitle = "Trees";
}

/* Main program */
int main() {
    GWindow window(kWindowWidth, kWindowHeight);
    window.setExitOnClose(true);
    window.setWindowTitle(kWindowTitle);

    while (true) {
        window.clearCanvasPixels();

        drawTree(window,
                 window.getWidth() / 2.0, window.getHeight(),
                 window.getHeight());

        pause(1000);
    }

    return 0;

}
