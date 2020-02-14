#ifndef OurHashSet_Included
#define OurHashSet_Included

#include <string>
#include "vector.h"

class OurHashSet {
public:
    OurHashSet();

    bool contains(const std::string& value) const;
    void add(const std::string& value);

private:
    Vector<Vector<std::string>> buckets;
};


#endif
