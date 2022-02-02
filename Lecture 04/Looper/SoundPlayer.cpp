#include "SoundPlayer.h"
//#include "qsound.h"
#include "gthread.h"
#include <iostream>
#include <iomanip>
using namespace std;

const int kFilenameWidth = 20;

void playSound(const string& filename, double ms) {
    cout << setw(kFilenameWidth) << filename << " (" << ms << "ms)" << endl;

    /* Launch a thread in the background to play the sound. We
     * detach it so that it can continue to run and execute
     * even after the thread object we created here ceases
     * to exist.
     */
    thread mThread([filename] {
        ostringstream command;
        command << "./PlaySound.sh " << filename;
        system(command.str().c_str());
    });
    mThread.detach();
    GThread::getCurrentThread()->sleep(ms);
}
