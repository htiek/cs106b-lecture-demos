#include "RandomBag.h"
#include "random.h"
#include "error.h"

void RandomBag::add(int value) {
    elems += value;
}

int RandomBag::removeRandom() {
    if (isEmpty()) {
        error("You can't remove something from nothing, silly.");
    }

    int index  = randomInteger(0, elems.size() - 1);
    int result = elems[index];
    elems.remove(index);

    return result;
}

int RandomBag::size() const {
    return elems.size();
}

bool RandomBag::isEmpty() const {
    return size() == 0;
}
