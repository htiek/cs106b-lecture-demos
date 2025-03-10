#include "GUI/MiniGUI.h"
#include "TimedFunctions.h"
#include "ginteractors.h"
#include "gtimer.h"
#include "gthread.h"
#include <cstdint>
#include <string>
#include <limits>
#include <cmath>
#include <iomanip>
using namespace std;
using namespace MiniGUI;

namespace Timing {
    /* Generates numbers in linear and exponential sequences */
    vector<size_t> linRange(size_t low, size_t high, size_t step) {
        vector<size_t> result;
        for (; low <= high; low += step) {
            result.push_back(low);
        }
        return result;
    }

    vector<size_t> expRange(size_t low, size_t high, double step) {
        vector<size_t> result;
        for (; low <= high; low *= step) {
            result.push_back(low);
        }
        return result;
    }
}

namespace {
    /* Graphics constants. */
    const double kEventTimerSpeed = 1; // Fast enough for things to run smoothly, not enough to drown us
    const auto kBackgroundColor = Color::WHITE();
    const double kPadding = 20;

    /* Axis constants. */
    const auto kAxisColor = Color::fromHex(0x555555); // Davy's gray
    const MiniGUI::Font kAxisFont(FontFamily::SERIF, FontStyle::NORMAL, 8, kAxisColor);

    const size_t kMaxAxisLabels = 10;    // Max number of major tick marks on the X axis

    /* Content areas. */
    const MiniGUI::Font kHeaderFont(FontFamily::SERIF, FontStyle::BOLD_ITALIC, 50, kAxisColor);
    const double kHeaderHeight = 50;

    /* Legend area, expressed as an offset from the start of the chart area. */
    const double kLegendXOffset   = 100;
    const double kLegendYOffset   =   0;
    const double kLegendWidth     = 150;
    const double kLegendHeight    = 200;

    const MiniGUI::Font kLegendFont(FontFamily::SANS_SERIF, FontStyle::NORMAL, 12, kAxisColor);

    /* Colors to use for various values of k. */
    const vector<Color> kLineColors = {
        Color::fromHex(0xCC0000), // Rosso Corsa
        Color::fromHex(0xEE7F2D), // Princeton Orange
        Color::fromHex(0xFFC40C), // Mikado Yellow
        Color::fromHex(0x008000), // Office Green
        Color::fromHex(0x007BA7), // Cerulean
        Color::fromHex(0xB53389), // Fandango
        Color::fromHex(0x343434), // Jet
    };

    /* Problem handler that reports timing information for the different types. */
    class PerformanceGUI: public ProblemHandler {
    public:
        PerformanceGUI(GWindow& window);

        void timerFired() override;
        void actionPerformed(GObservable* source) override;

    protected:
        void repaint() override;

    private:
        /* Each timer tick steps us through the next test case. */
        GTimer timer{kEventTimerSpeed};

        /* Which test, if any, we're doing. */
        bool isActive = false;
        Timing::TimeTest currTest;

        bool firstRun;
        size_t nextN = 0, nextK = 0;    // Next values of n and k to use.
        vector<string> axisLabels{2};   // Labels to use on the x axis. Defaults to two blank strings
        size_t axisTicks = 0;           // Minor ticks to use on the x axis

        /* Test case results so far. */
        Vector<Vector<double>> results;

        /* Text field for firing off tests. */
        Temporary<GTextField> mInput;
        Temporary<GColorConsole> mConsole;

        void startTests(const Timing::TimeTest& test);
        void stepTests();

        void drawChart (GWindow& window, const GRectangle& bounds);
        void drawHeader(GWindow& window, const GRectangle& bounds);
        void drawLegend(GWindow& window, const GRectangle& bounds);
    };

    PerformanceGUI::PerformanceGUI(GWindow& window) : ProblemHandler(window) {
        mInput   = Temporary<GTextField>(new GTextField(""), window, "SOUTH");
        mConsole = Temporary<GColorConsole>(new GColorConsole(), window, "WEST");

        mConsole->setWidth(window.getCanvasWidth() / 2);
        mConsole->setHeight(window.getCanvasHeight());

        mConsole->setStyle(Color::BLACK(), GColorConsole::NORMAL, FontSize(24));
    }

    void PerformanceGUI::stepTests() {
        /* Otherwise, run the next test. */
        Timing::Timer timer;
        currTest.callback(currTest.ns[nextN], currTest.ks[nextK], timer);

        /* Store the result. */
        if (!firstRun) {
            double duration = timer.elapsed();
            results[results.size() - 1] += duration;
            GThread::runOnQtGuiThread([&] {
                *mConsole << "n = " << setw(8) << currTest.ns[nextN] << ": " << (duration / 1e6) << "ms" << endl;
            });
        }

        /* Step forward. */
        nextN++;

        /* Finished all n's? Advance k. */
        if (nextN == currTest.ns.size()) {
            nextN = 0;
            nextK++;

            /* Need a new place to store our results. */
            if (!firstRun) results.add({});

            /* Finished all k's? We're done! */
            if (nextK == currTest.ks.size()) {
                if (firstRun) {
                    nextN = nextK = 0;
                    firstRun = false;
                } else {
                    timer.stop();
                    isActive = false;
                    *mConsole << endl << endl;
                    return;
                }
            }
        }
    }

    void PerformanceGUI::timerFired() {
        /* If we don't have an active test, there's nothing to do. */
        if (!isActive) {
            timer.stop();
            return;
        }

        stepTests();

        /* Need to redraw things! */
        requestRepaint();
    }

    /* Begins a new testing session. */
    void PerformanceGUI::startTests(const Timing::TimeTest& test) {
        *mConsole << "Timing " << test.name << ":" << endl;

        currTest = test;

        /* Reset state. */
        firstRun = true;
        nextN = nextK = 0;
        results.clear();
        results.add({});

        /* Set up x-axis labels. */
        axisLabels.clear();

        /* We will never have more than kMaxAxisLabels labels on the X axis. If we
         * do, we will start introducing minor tickmarks.
         *
         * The way we're going to do this is as follows. We'll compute
         * ceil(#labels / kAxisLabels), which gives back the number of tick skips
         * to use. For example, if we want 11 labels and the max is 10, we'll compute
         * ceil(11 / 10) - 1 = 2, and have one minor tick in between each set
         * of major ticks.
         *
         * We actually compute this using the technique that (a + b - 1) / b computes
         * ceil(a / b).
         */
        axisTicks = ((test.ns.size() + kMaxAxisLabels - 1) / kMaxAxisLabels);
        size_t numMajor = (test.ns.size() + axisTicks - 1) / axisTicks;

        for (size_t i = 0; i < numMajor; i++) {
            size_t effectiveIndex = i * axisTicks; // We're skipping things, after all!

            string label;
            if (effectiveIndex == 0) {
                label = "n=" + to_string(test.ns[effectiveIndex]);
            } else if (effectiveIndex < test.ns.size()) {
                label = to_string(test.ns[effectiveIndex]);
            } else {
                label = ""; // Not needed, but helps clarify intent.
            }

            axisLabels.push_back(label);
        }

        /* The axisTicks parameter actually literally controls how many minor ticks are
         * drawn, not the skip size between major ticks. As a result, we need to subtract
         * one here in order to ensure that we draw teh right number of minor ticks.
         */
        axisTicks--;

        isActive = true;
        timer.start();
    }


    void PerformanceGUI::actionPerformed(GObservable* source) {
        if (source == mInput) {
            string command = toLowerCase(mInput->getText());

            /* See if we know this one. */
            const Timing::Option* option = nullptr;
            for (const auto& entry: _kTimingOptions) {
                if (toLowerCase(entry.name) == command) {
                    option = &entry;
                    break;
                }
            }

            if (option) {
                startTests(option->constructor());
            } else if (command == "resize") {
                mConsole->setWidth(window().getCanvasWidth() / 2);
            } else if (command == "clear") {
                mConsole->clearDisplay();
                mConsole->flush();
            } else {
                *mConsole << "Unknown function." << endl;
            }
        }
    }

    void PerformanceGUI::repaint() {
        clearDisplay(window(), kBackgroundColor);

        /* Space for the header. */
        GRectangle header = {
            kPadding, kPadding,
            window().getCanvasWidth() - 2 * kPadding,
            kHeaderHeight
        };

        double chartTop = header.y + header.height;

        /* Set up the chart. */
        GRectangle chart = {
            kPadding, chartTop,
            window().getCanvasWidth()  - 2 * kPadding,
            window().getCanvasHeight() - chartTop - kPadding
        };

        /* And the legend. */
        GRectangle legend = {
            chart.x + kLegendXOffset, chart.y + kLegendYOffset,
            kLegendWidth, kLegendHeight
        };

        drawHeader(window(), header);
        drawChart (window(), chart);
        drawLegend(window(), legend);
    }

    void PerformanceGUI::drawHeader(GWindow& window, const GRectangle& bounds) {
        auto render = TextRender::construct(currTest.name, bounds, kHeaderFont);
        render->alignCenterHorizontally();
        render->draw(window);
    }

    void PerformanceGUI::drawChart(GWindow& window, const GRectangle& bounds) {
        /* Y-axis labels will be empty. We need a minimum of two, though, so we'll make those. */
        vector<string> yLabels(2);

        /* Convert our results into line segments. */

        /* Find the maximum value across everything. */
        double maxValue = 0;
        double minValue = numeric_limits<double>::infinity();
        for (const auto& result: results) {
            for (double val: result) {
                maxValue = max(val, maxValue);
                minValue = min(val, minValue);
            }
        }

        /* Nudge the max value up a bit to avoid dividing by zero. */
        maxValue = nextafter(maxValue, numeric_limits<double>::infinity());

        /* Normalize everything by that amount. */
        vector<vector<GPoint>> lines;
        for (const auto& result: results) {
            vector<GPoint> line;
            for (int i = 0; i < result.size(); i++) {
                line.push_back({ i * 1.0 / (currTest.ns.size() - 1), (result[i] - minValue) / (maxValue - minValue) });
            }
            lines.push_back(line);
        }

        /* Draw it! */
        LineGraphRender::construct(lines, axisLabels, yLabels, axisTicks, 0, bounds, kAxisFont, kAxisFont, kLineColors, kAxisColor)->draw(window);
    }

    void PerformanceGUI::drawLegend(GWindow& window, const GRectangle& bounds) {
        /* If there is only one value of k, don't draw anything. */
        if (currTest.ks.size() <= 1) return;

        /* Otherwise, there are many values of k. Assemble labels based on the number of lines
         * we have drawn so far.
         */
        vector<string> labels;
        for (int i = 0; i < currTest.ks.size() && i < results.size(); i++) {
            labels.push_back("k = " + to_string(currTest.ks[i]));
        }

        /* Set up the legend. Don't draw it yet; we need to clear the area behind it. */
        auto legend = LegendRender::construct(labels, kLineColors, bounds, { kLegendFont.color() }, kLegendFont, kLegendFont.color());
        window.setColor(kBackgroundColor.toRGB());
        window.fillRect(legend->bounds());

        /* Now draw it. */
        legend->draw(window);
    }
}

GRAPHICS_HANDLER("Performance", GWindow& window) {
    return make_shared<PerformanceGUI>(window);
}
