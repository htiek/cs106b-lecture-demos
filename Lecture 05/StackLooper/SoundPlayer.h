#pragma once

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <string>
#include <iostream>

/* Object that plays with a sound clip and nicely disposes itself. This is not
 * meant to be used directly; use playSound() instead.
 */
class SoundPlayer: public QObject {
    Q_OBJECT

public:
    explicit SoundPlayer(const std::string& filename);

public slots:
    void handleStateChanged(QMediaPlayer::PlaybackState newState);

private:
    QMediaPlayer* player;
    QAudioOutput* output;
};

void playSound(const std::string& filename, double ms);
