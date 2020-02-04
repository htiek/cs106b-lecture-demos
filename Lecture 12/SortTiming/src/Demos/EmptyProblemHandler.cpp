#include "ProblemHandler.h"
#include "GUIUtils.h"
#include "gobjects.h"
#include <string>
using namespace std;

namespace {
    /* Graphics Constants. */
    const string kFont = "Serif-BOLDITALIC-36";
    const string kBackgroundColor = "#400040";
    const string kFontColor       = "#800080";

    const string kToDisplay = "Choose which demo to run.";
    
    /* A problem handler that just prompts the user to pick a problem to solve. This
     * gets installed whenever there's nothing else to display.
     */
    class EmptyProblemHandler: public ProblemHandler {    
    protected:
        void repaint(GWindow& window) override;
    };
}

void EmptyProblemHandler::repaint(GWindow& window) {
    /* Clear the window. */
    clearDisplay(window, kBackgroundColor);

    /* Draw some text! */
    auto text = TextRender::construct(kToDisplay, {
                                          0, 0, window.getCanvasWidth(), window.getCanvasHeight()
                                      }, kFontColor, kFont);
    text->alignCenterVertically();
    text->alignCenterHorizontally();
    text->draw(window);
}

shared_ptr<ProblemHandler> makeEmptyProblemHandler(GWindow &) {
    return make_shared<EmptyProblemHandler>();
}
