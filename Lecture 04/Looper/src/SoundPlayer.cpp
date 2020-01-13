#include "SoundPlayer.h"
#include "qsound.h"
#include "gthread.h"
using namespace std;

void playSound(const string& filename, double ms) {
    GThread::runOnQtGuiThread([filename] {
        QSound::play(QString::fromStdString(filename));
    });
    GThread::getCurrentThread()->sleep(ms);
}
