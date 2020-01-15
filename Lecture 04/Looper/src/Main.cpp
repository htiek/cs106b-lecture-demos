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

/* Type representing a sound clip. */
struct SoundClip {
    string filename; // Name of the file
    double length;   // How long to play it for
};

/* Given the name of a loop file, loads the clips from
 * that file into a Queue.
 */
Queue<SoundClip> loadLoop(const string& filename) {
    /* See Chapter 3 of the textbook for details. */
    ifstream input(filename);

    Queue<SoundClip> result;

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

        result.enqueue(clip);
    }

    return result;
}

int main() {
    /* We've bundled the following sample clips:
     *
     * RowYourBoat.loop: The children's song "Row Your Boat"
     * FirstCircle.loop: The intro to "The First Circle" by Pat Metheny Group
     * Solfegietto.loop: The first bars of "Solfegietto in C Minor" by C.P.E. Bach
     * Money.loop:       The bass line from "Money" by Pink Floyd
     * Pentatonic.loop:  A rising and falling pentatonic scale
     * Gnossienne4.loop: A section of "Gnossienne 4" by Erik Satie
     */
    Queue<SoundClip> loop = loadLoop("RowYourBoat.loop");

    while (true) {
        /* Play the clip that's been waiting the longest. */
        SoundClip toPlay = loop.dequeue();
        playSound(toPlay.filename, toPlay.length);

        /* Put it at the back of the line. */
        loop.enqueue(toPlay);
    }

    /* No return statement needed; the above loop is
     * infinite and we can never get here.
     */
}

