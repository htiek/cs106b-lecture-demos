#ifndef OurHashSet_Included
#define OurHashSet_Included

#include <string>
#include "vector.h"
#include "HashFunction.h"

class OurHashSet {
public:
    OurHashSet();

    bool contains(const std::string& value) const;
    void add(const std::string& value);

private:
    HashFunction<std::string>   hashFn;
    Vector<Vector<std::string>> buckets;

    int numElems;
    void rehash();
};


#endif
