#include "OurHashSet.h"
#include "hashcode.h" // For the hash functions
using namespace std;

const int kDefaultSize = 1; // Or really anything, really.

OurHashSet::OurHashSet() {
    Vector<Vector<string>> ourBuckets(kDefaultSize);
    HashFunction<string>   ourHashFn(kDefaultSize);

    buckets = ourBuckets;
    hashFn  = ourHashFn;
}

bool OurHashSet::contains(const string& value) const {
    /* Determine the bucket to jump into. */
    int bucket = hashFn(value);

    /* Jump to that bucket. */
    for (string elem: buckets[bucket]) {
        if (elem == value) return true;
    }

    return false;
}

void OurHashSet::add(const string& value) {
    /* Determine the bucket to jump into. */
    int bucket = hashFn(value);

    /* If this element is already present, we don't need to do anything. */
    for (string elem: buckets[bucket]) {
        if (elem == value) return;
    }

    buckets[bucket] += value;

    numElems++;
    if (numElems / buckets.size() >= 2) {
        rehash();
    }
}

void OurHashSet::rehash() {
    Vector<Vector<string>> newBuckets(buckets.size() * 2);
    HashFunction<string> newHashFn(buckets.size() * 2);

    for (int bucket = 0; bucket < buckets.size(); bucket++) {
        for (string elem: buckets[bucket]) {
            newBuckets[newHashFn(elem)] += elem;
        }
    }

    buckets = newBuckets;
    hashFn  = newHashFn;
}
