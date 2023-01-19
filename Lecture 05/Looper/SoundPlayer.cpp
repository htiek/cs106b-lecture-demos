#include "SoundPlayer.h"
#include "gthread.h"
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <chrono>
#include <mutex>
using namespace std;

const int kFilenameWidth = 20;

static mutex theCoutLock;

void playSound(const string& filename, double ms) {
    auto startTime = chrono::high_resolution_clock::now();

    /* Printing things is slow on macOS, so do that in a thread. */
    thread printer([=] {
        lock_guard<mutex> locker(theCoutLock);
        cout << setw(kFilenameWidth) << filename << " (" << ms << "ms)" << endl;
    });
    printer.detach();

    /* Fire off the sound player as a separate process. */
    if (fork() == 0) {
        vector<char*> args;
        string file = "sounds/" + filename;
        args.push_back("/usr/local/bin/play");
        args.push_back(strdup(file.c_str()));
        args.push_back(nullptr);

        /* Close stderr and stdout so we don't clog up the
         * display.
         */
        close(1);
        close(2);

        /* Launch! */
        execvp("/usr/local/bin/play", args.data());
    }

    /* Delay for the appropriate amount of time. */
    double delay = ms - chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - startTime).count();
    if (delay > 0) {
        GThread::getCurrentThread()->sleep(delay);
    }
}
