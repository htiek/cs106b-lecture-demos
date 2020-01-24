/* File: Subsets.cpp
 *
 * A program to list off all subsets of a master set.
 */
#include <iostream>
#include <string>
#include "hashset.h"
#include "console.h"
using namespace std;

void listSubsetsRec(const HashSet<int>& elems,
                    const HashSet<int>& chosen) {

  if (elems.isEmpty()) {
    cout << chosen << endl;
  } else {
    int elem = elems.first();

    /* Option 1: Include this element. */
    listSubsetsRec(elems - elem, chosen + elem);

    /* Option 2: Exclude this element. */
    listSubsetsRec(elems - elem, chosen);
  }
}
void listSubsetsOf(const HashSet<int>& s) {
    listSubsetsRec(s, {});
}

HashSet<string> subsetsRec(const string& str,
                           const string& chosen) {

  if (str == "") {
    return { chosen };
  } else {
    string remaining = str.substr(1);

    /* Either include the first character, or don't. */
    return subsetsRec(remaining, chosen + str[0]) +
           subsetsRec(remaining, chosen);

  }
}

HashSet<string> subsetsOf(const string& str) {
    return subsetsRec(str, "");
}

int main() {
    listSubsetsOf({1, 2, 3});

    HashSet<string> subsets = subsetsOf("AHI");
    cout << "There are " << subsets.size() << " subsets of AHI." << endl;
    cout << "Here they are!" << endl;

    for (string subset: subsets) {
        cout << "  \"" << subset << "\"" << endl;
    }
    return 0;
}

