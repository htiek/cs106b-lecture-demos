#include "SoundPlayer.h"
#include "console.h"
#include "stack.h"
#include "filelib.h"
#include "strlib.h"
#include "simpio.h"
#include "vector.h"
#include <fstream>
#include <string>
using namespace std;

const string kBaseDirectory = "loops/";

/* Type representing a sound clip. */
struct SoundClip {
    string filename; // Name of the file
    double length;   // How long to play it for
};

Vector<string> musicFileOptions() {
    Vector<string> result;
    for (string file: listDirectory(kBaseDirectory)) {
        if (endsWith(file, ".loop")) {
            result += file;
        }
    }
    sort(result.begin(), result.end());
    return result;
}

void displayOptions(const Vector<string>& options) {
    for (int i = 0; i < options.size(); i++) {
        cout << i << ": " << options[i] << endl;
    }
}

string chooseMusicFile() {
    Vector<string> options = musicFileOptions();
    displayOptions(musicFileOptions());

    while (true) {
        int choice = getInteger("Your choice: ");
        if (choice >= 0 && choice < options.size()) {
            return kBaseDirectory + options[choice];
        }
    }
}

/* Given the name of a loop file, loads the clips from
 * that file into a Stack.
 */
Stack<SoundClip> loadLoop(const string& filename) {
    /* See Chapter 3 of the textbook for details. */
    ifstream input(filename);

    Stack<SoundClip> result;

    /* The idiomatic "read all the lines of this file"
     * loop in C++.
     */
    for (string line; getline(input, line); ) {
        /* Each line has the form
         *
         * Filename Duration
         *
         * We'll split on a space, taking the first item
         * as the name of the file and the second as the
         * duration.
         */
        Vector<string> pieces = stringSplit(line, " ");

        /* Parse things into a SoundClip. */
        SoundClip clip;
        clip.filename = pieces[0];
        clip.length   = stringToReal(pieces[1]);

        result.push(clip);
    }

    return result;
}

int main() {
    Stack<SoundClip> loop = loadLoop(chooseMusicFile());

    while (true) {
        SoundClip toPlay = loop.pop();
        playSound(toPlay.filename, toPlay.length);

        loop.push(toPlay);
    }
}










