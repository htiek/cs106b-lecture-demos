#include "OurHashSet.h"
#include "hashcode.h" // For the hash functions
using namespace std;

const int kDefaultSize = 1; // Or really anything, really.
const double kMaxLoadFactor = 2;

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
    /* Don't add duplicate elements. */
    if (contains(value)) return;

    /* Determine the bucket to jump into. */
    int bucket = hashFn(value);
    buckets[bucket] += value;
    numElems++;

    /* If we exceed our load factor cutoff, rehash. */
    if (numElems >= kMaxLoadFactor * buckets.size()) {
        rehash();
    }
}

/* Doubles the number of buckets and redistributes elements into those buckets. */
void OurHashSet::rehash() {
    /* We need a new set of buckets and a new hash function that can range over
     * those buckets.
     */
    Vector<Vector<string>> newBuckets(buckets.size() * 2);
    HashFunction<string> newHashFn(buckets.size() * 2);

    /* Redistribute all old elements into the new buckets using the new
     * hash function.
     */
    for (int bucket = 0; bucket < buckets.size(); bucket++) {
        for (string elem: buckets[bucket]) {
            newBuckets[newHashFn(elem)] += elem;
        }
    }

    /* Replace our existing buckets and hash function with these new ones. */
    buckets = newBuckets;
    hashFn  = newHashFn;
}
