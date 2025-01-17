#include "SoundPlayer.h"
#include "gthread.h"
#include "gconsolewindow.h"
#include <iostream>
#include <iomanip>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <chrono>
using namespace std;

/* The SoundPlayer type launches a new QMediaPlayer to play the sound clip,
 * then sets it up so that when the audio finishes, we clean up all the
 * relevant objects.
 */
SoundPlayer::SoundPlayer(const string& filename) {
    player = new QMediaPlayer;
    output = new QAudioOutput;
    player->setAudioOutput(output);
    player->setSource(QUrl::fromLocalFile(QString::fromStdString("sounds/" + filename)));
    connect(player, &QMediaPlayer::playbackStateChanged, this, &SoundPlayer::handleStateChanged);
    player->play();
}

/* When the sound is done, clean up all the objects we created for it. */
void SoundPlayer::handleStateChanged(QMediaPlayer::PlaybackState newState) {
    if (newState == QMediaPlayer::StoppedState) {
        player->stop();
        player->deleteLater();
        output->deleteLater();
        deleteLater();
    }
}

/* Padding for sound file names. */
const int kFilenameWidth = 20;

void playSound(const string& filename, double ms) {
    auto startTime = chrono::high_resolution_clock::now();

    /* Launch the sound. We have to run this on the Qt GUI thread so that we play
     * nice with Qt's threading model.
     */
    GThread::runOnQtGuiThread([&] {
        new SoundPlayer(filename);
    });

    /* Delay for the appropriate amount of time. Factor in that we just spent some
     * amount of time doing work to launch the sound clip so that things seem
     * smoother.
     */
    cout << setw(kFilenameWidth) << filename << " (" << ms << "ms)" << endl;
    double delay = ms - chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - startTime).count();
    if (delay > 0) {
        GThread::getCurrentThread()->sleep(delay);
    }
}
