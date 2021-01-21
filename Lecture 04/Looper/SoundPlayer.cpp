#include "SoundPlayer.h"
#include "qsound.h"
#include "gthread.h"
#include <iostream>
#include <iomanip>
using namespace std;

const int kFilenameWidth = 20;

void playSound(const string& filename, double ms) {
    cout << setw(kFilenameWidth) << filename << " (" << ms << "ms)" << endl;
    GThread::runOnQtGuiThread([filename] {
        QSound::play(QString::fromStdString("sounds/" + filename));
    });
    GThread::getCurrentThread()->sleep(ms);
}
