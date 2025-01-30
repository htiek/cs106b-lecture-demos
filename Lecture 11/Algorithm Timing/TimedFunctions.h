#ifndef TimedFunctions_Included
#define TimedFunctions_Included

#include <functional>
#include <vector>
#include <string>
#include <chrono>

/* Timing-specific functions and types. */
namespace Timing {
    /**
     * A type representing a stopwatch. This is used to time the costs of various
     * operations.
     */
    class Timer {
    public:
      void start() {
        current = std::chrono::high_resolution_clock::now();
      }

      void stop() {
        total += std::chrono::high_resolution_clock::now() - current;
      }

      double elapsed() const {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(total).count();
      }

    private:
      std::chrono::high_resolution_clock::duration total =
        std::chrono::high_resolution_clock::duration::zero();
      std::chrono::high_resolution_clock::time_point current;
    };

    /* All the information needed to run a time test. */
    struct TimeTest {
        std::function<void (size_t n, size_t k, Timer& timer)> callback; // Given n, k, and a timer, do work.
        std::vector<size_t> ns, ks;                                      // Values of n and k
        std::string name;                                                // What we're testing
    };

    /* Utility functions for generating linear and exponential ranges. */
    std::vector<size_t> linRange(size_t low, size_t high, size_t step);
    std::vector<size_t> expRange(size_t low, size_t high, double step);

    /* Constructor type: Given a GWindow, build a problem handler. */
    using Constructor = std::function<TimeTest()>;

    /* An entry in the top-level GUI control bar. */
    struct Option {
        std::string name;
        Constructor constructor;
    };

    /* Macro to make it easier to define a constructor. This combines a forward declaration
     * with a call to the function name.
     */
    #define TIME_TEST(name, constructor) {              \
        name, [] () {                                   \
            Timing::TimeTest constructor();             \
            return constructor();                       \
        }                                               \
    }
}

    /* Edit this list to control what tests exist. */
const std::vector<Timing::Option> _kTimingOptions = {
    TIME_TEST("averageOf",       makeAverageOfTest),
    TIME_TEST("printStars",      makePrintStarsTest),
    TIME_TEST("hmmThatsStrange", makeHmmThatsStrangeTest),
    TIME_TEST("flipFlop",        makeFlipFlopTest),
    TIME_TEST("pando",           makePandoTest),
    TIME_TEST("beni",            makeBeniTest),
    TIME_TEST("printNumbers",    makePrintNumbersTest),
    TIME_TEST("printNumbers 2",  makePrintNumbers2Test),
    TIME_TEST("printTrigrams_v1",  makePrintTrigramsV1Test),
    TIME_TEST("printTrigrams_v2",  makePrintTrigramsV2Test),
};

#endif
