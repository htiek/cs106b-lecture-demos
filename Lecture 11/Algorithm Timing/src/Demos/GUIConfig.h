/**
 * Configuration file for general GUI driver. Edit this file to change basic parameters of the
 * GUI system.
 */
#ifndef GUIConfig_Included
#define GUIConfig_Included

#include "ProblemHandler.h"
#include "gwindow.h"
#include <memory>
#include <functional>
#include <string>
#include <vector>

/* This section should remain the same regardless of what you plan to do in your GUI. */
namespace GUI {
    /* Constructor type: Given a GWindow, build a problem handler. */
    using Constructor = std::function<std::shared_ptr<ProblemHandler> (GWindow &)>;

    /* An entry in the top-level GUI control bar. */
    struct GUIOption {
        std::string name;
        Constructor constructor;
    };
}



/* Macro to make it easier to define a constructor. This combines a forward declaration
 * with a call to the function name.
 */
#define GUI_HANDLER(name, constructor) {                           \
    name, [] (GWindow& window) {                                   \
        std::shared_ptr<ProblemHandler> constructor(GWindow &);    \
        return constructor(window);                                \
    }                                                              \
}

/* Edit this list to control what shows in the GUI. */
const std::vector<GUI::GUIOption> _kGUIOptions = {
};

/* Macro to make it easier to define a default option. This combines a forward declaration
 * with a call to the function name.
 */
#define DEFAULT_HANDLER(constructor)                                   \
        new GUI::Constructor([] (GWindow& window) {                    \
            std::shared_ptr<ProblemHandler> constructor(GWindow &);    \
            return constructor(window);                                \
        })

/* Edit this to change the default handler. */
const GUI::Constructor* _kDefault = DEFAULT_HANDLER(makePerformanceGUI);

/* Edit this string to change the name of the GUI. */
const std::string _kGUITitle = "Big-O Notation";

#endif
