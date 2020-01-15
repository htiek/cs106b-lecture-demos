#include "SoundPlayer.h"
#include "console.h"
#include "queue.h"
#include "sound.h"
#include "filelib.h"
#include "strlib.h"
#include "vector.h"
#include <fstream>
#include <string>
using namespace std;

struct SoundClip {
    string filename;
    double length;
};

Queue<SoundClip> loadLoop() {
    string filename = promptUserForFile("Enter loop file: ");

    Queue<SoundClip> result;

    ifstream input(filename);
    for (string line; getline(input, line); ) {
        Vector<string> parts = stringSplit(line, " ");

        SoundClip clip;
        clip.filename = parts[0];
        clip.length   = stringToReal(parts[1]);

        result.enqueue(clip);
    }

    return result;
}

int main() {
    Queue<SoundClip> loop = loadLoop();
    while (true) {
        SoundClip toPlay = loop.dequeue();
        playSound(toPlay.filename, toPlay.length);
        loop.enqueue(toPlay);
    }
    return 0;
}
