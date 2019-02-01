/*
 * File: linkedhashset.h
 * ---------------------
 * This file exports the <code>LinkedHashSet</code> class, which
 * implements an efficient abstraction for storing sets of values.
 * 
 * @author Marty Stepp
 * @version 2018/03/10
 * - added methods front, back
 * @version 2016/09/24
 * - refactored to use collections.h utility functions
 * @version 2016/09/22
 * - added containsAll, isSupersetOf methods
 * - added support for std initializer_list usage, such as {1, 2, 3}
 *   in constructor, addAll, containsAll, isSubsetOf, isSupersetOf, removeAll,
 *   retainAll, and operators +, +=, -, -=, *, *=
 * - bug fix in hashCode function
 * - added operators <, <=, >, >=
 * @version 2016/08/04
 * - fixed operator >> to not throw errors
 * @version 2015/10/26
 * - initial version
 * @since 2015/10/26
 */

#include "private/init.h"   // ensure that Stanford C++ lib is initialized

#ifndef INTERNAL_INCLUDE
#include "private/initstudent.h"   // insert necessary included code by student
#endif // INTERNAL_INCLUDE

#ifndef _linkedhashset_h
#define _linkedhashset_h

#include <initializer_list>
#include <iostream>
#include <functional>

#define INTERNAL_INCLUDE 1
#include "collections.h"
#define INTERNAL_INCLUDE 1
#include "error.h"
#define INTERNAL_INCLUDE 1
#include "hashcode.h"
#define INTERNAL_INCLUDE 1
#include "linkedhashmap.h"
#undef INTERNAL_INCLUDE

/*
 * Class: LinkedHashSet<ValueType>
 * -------------------------------
 * Identical to a HashSet except that upon iteration using a for-each loop
 * or << / toString call, it will emit its elements in the order they were
 * originally inserted.  This is provided at a runtime and memory
 * cost due to needing to store an extra copy of the elements.
 */
template <typename ValueType>
class LinkedHashSet {
public:
    /*
     * Constructor: LinkedHashSet
     * Usage: LinkedHashSet<ValueType> set;
     * ------------------------------------
     * Initializes an empty set of the specified element type.
     */
    LinkedHashSet() = default;

    /*
     * Constructor: LinkedHashSet
     * Usage: LinkedHashSet<ValueType> set {1, 2, 3};
     * ----------------------------------------------
     * Initializes a new set that stores the given elements.
     * Note that the elements are stored in unpredictable order internally and not
     * necessarily the order in which they are written in the initializer list.
     */
    LinkedHashSet(std::initializer_list<ValueType> list);

    /*
     * Destructor: ~LinkedHashSet
     * --------------------------
     * Frees any heap storage associated with this set.
     */
    virtual ~LinkedHashSet() = default;

    /*
     * Method: add
     * Usage: set.add(value);
     * ----------------------
     * Adds an element to this set, if it was not already there.  For
     * compatibility with the STL <code>set</code> class, this method
     * is also exported as <code>insert</code>.
     */
    void add(const ValueType& value);
    
    /*
     * Method: addAll
     * Usage: set.addAll(set2);
     * ------------------------
     * Adds all elements of the given other set to this set.
     * Returns a reference to this set.
     * Identical in behavior to the += operator.
     */
    LinkedHashSet<ValueType>& addAll(const LinkedHashSet<ValueType>& set);

    /*
     * Method: back
     * Usage: ValueType value = set.back();
     * ------------------------------------
     * Returns the last value in the set in the order established by the
     * <code>foreach</code> macro.  If the set is empty, generates an error.
     */
    ValueType back() const;

    /*
     * Method: clear
     * Usage: set.clear();
     * -------------------
     * Removes all elements from this set.
     */
    void clear();
    
    /*
     * Method: contains
     * Usage: if (set.contains(value)) ...
     * -----------------------------------
     * Returns <code>true</code> if the specified value is in this set.
     */
    bool contains(const ValueType& value) const;

    /*
     * Method: containsAll
     * Usage: if (set.containsAll(set2)) ...
     * -------------------------------------
     * Returns <code>true</code> if every value from the given other set
     * is also found in this set.
     * You can also pass an initializer list such as {1, 2, 3}.
     * Equivalent in behavior to isSupersetOf.
     */
    bool containsAll(const LinkedHashSet<ValueType>& set2) const;

    /*
     * Method: equals
     * Usage: if (set.equals(set2)) ...
     * --------------------------------
     * Returns <code>true</code> if this set contains exactly the same values
     * as the given other set.
     * Identical in behavior to the == operator.
     */
    bool equals(const LinkedHashSet<ValueType>& set2) const;
    
    /*
     * Method: first
     * Usage: ValueType value = set.first();
     * -------------------------------------
     * Returns the first value in the set in the order established by the
     * <code>foreach</code> macro.  If the set is empty, <code>first</code>
     * generates an error.
     */
    ValueType first() const;

    /*
     * Method: front
     * Usage: ValueType value = set.front();
     * -------------------------------------
     * Returns the first value in the set in the order established by the
     * <code>foreach</code> macro.  If the set is empty, generates an error.
     * Equivalent to first.
     */
    ValueType front() const;

    /*
     * Method: insert
     * Usage: set.insert(value);
     * -------------------------
     * Adds an element to this set, if it was not already there.  This
     * method is exported for compatibility with the STL <code>set</code> class.
     */
    void insert(const ValueType& value);

    /*
     * Method: isEmpty
     * Usage: if (set.isEmpty()) ...
     * -----------------------------
     * Returns <code>true</code> if this set contains no elements.
     */
    bool isEmpty() const;
    
    /*
     * Method: isSubsetOf
     * Usage: if (set.isSubsetOf(set2)) ...
     * ------------------------------------
     * Implements the subset relation on sets.  It returns
     * <code>true</code> if every element of this set is
     * contained in <code>set2</code>.
     */
    bool isSubsetOf(const LinkedHashSet& set2) const;

    /*
     * Method: isSupersetOf
     * Usage: if (set.isSupersetOf(set2)) ...
     * --------------------------------------
     * Implements the superset relation on sets.  It returns
     * <code>true</code> if every element of this set is
     * contained in <code>set2</code>.
     * Note that this will be true if the sets are equal.
     * You can also pass an initializer list such as {1, 2, 3}.
     * Equivalent in behavior to containsAll.
     */
    bool isSupersetOf(const LinkedHashSet& set2) const;

    /*
     * Method: mapAll
     * Usage: set.mapAll(fn);
     * ----------------------
     * Iterates through the elements of the set and calls <code>fn(value)</code>
     * for each one.  The values are processed in ascending order, as defined
     * by the comparison function.
     */
    void mapAll(std::function<void (const ValueType &)> fn) const;
    
    /*
     * Method: remove
     * Usage: set.remove(value);
     * -------------------------
     * Removes an element from this set.  If the value was not
     * contained in the set, no error is generated and the set
     * remains unchanged.
     */
    void remove(const ValueType& value);
    
    /*
     * Method: removeAll
     * Usage: set.removeAll(set2);
     * ---------------------------
     * Removes all elements of the given other set from this set.
     * Returns a reference to this set.
     * Identical in behavior to the -= operator.
     */
    LinkedHashSet<ValueType>& removeAll(const LinkedHashSet<ValueType>& set);

    /*
     * Method: retainAll
     * Usage: set.retainAll(set2);
     * ----------------------
     * Removes all elements from this set that are not contained in the given
     * other set. Returns a reference to this set.
     * Identical in behavior to the *= operator.
     */
    LinkedHashSet<ValueType>& retainAll(const LinkedHashSet<ValueType>& set);

    /*
     * Method: size
     * Usage: count = set.size();
     * --------------------------
     * Returns the number of elements in this set.
     */
    int size() const;
    
    /*
     * Method: toString
     * Usage: string str = set.toString();
     * -----------------------------------
     * Converts the set to a printable string representation.
     */
    std::string toString() const;

    /*
     * Operator: ==
     * Usage: set1 == set2
     * -------------------
     * Returns <code>true</code> if <code>set1</code> and <code>set2</code>
     * contain the same elements.
     */
    bool operator ==(const LinkedHashSet& set2) const;

    /*
     * Operator: !=
     * Usage: set1 != set2
     * -------------------
     * Returns <code>true</code> if <code>set1</code> and <code>set2</code>
     * are different.
     */
    bool operator !=(const LinkedHashSet& set2) const;

    /*
     * Operators: <, >, <=, >=
     * Usage: if (set1 <= set2) ...
     * ...
     * ----------------------------
     * Relational operators to compare two sets.
     * The <, >, <=, >= operators require that the ValueType has a < operator
     * so that the elements can be compared pairwise.
     */
    bool operator <(const LinkedHashSet& set2) const;
    bool operator <=(const LinkedHashSet& set2) const;
    bool operator >(const LinkedHashSet& set2) const;
    bool operator >=(const LinkedHashSet& set2) const;

    /*
     * Operator: +
     * Usage: set1 + set2
     *        set1 + element
     * ---------------------
     * Returns the union of sets <code>set1</code> and <code>set2</code>, which
     * is the set of elements that appear in at least one of the two sets.  The
     * right hand set can be replaced by an element of the value type, in which
     * case the operator returns a new set formed by adding that element.
     */
    LinkedHashSet operator +(const LinkedHashSet& set2) const;
    LinkedHashSet operator +(const ValueType& element) const;

    /*
     * Operator: *
     * Usage: set1 * set2
     * ------------------
     * Returns the intersection of sets <code>set1</code> and <code>set2</code>,
     * which is the set of all elements that appear in both.
     */
    LinkedHashSet operator *(const LinkedHashSet& set2) const;

    /*
     * Operator: -
     * Usage: set1 - set2
     *        set1 - element
     * ---------------------
     * Returns the difference of sets <code>set1</code> and <code>set2</code>,
     * which is all of the elements that appear in <code>set1</code> but
     * not <code>set2</code>.  The right hand set can be replaced by an
     * element of the value type, in which case the operator returns a new
     * set formed by removing that element.
     */
    LinkedHashSet operator -(const LinkedHashSet& set2) const;
    LinkedHashSet operator -(const ValueType& element) const;

    /*
     * Operator: +=
     * Usage: set1 += set2;
     *        set1 += value;
     * ---------------------
     * Adds all of the elements from <code>set2</code> (or the single
     * specified value) to <code>set1</code>.  As a convenience, the
     * <code>LinkedHashSet</code> package also overloads the comma operator so
     * that it is possible to initialize a set like this:
     *
     *<pre>
     *    LinkedHashSet&lt;int&lt; digits;
     *    digits += 0, 1, 2, 3, 4, 5, 6, 7, 8, 9;
     *</pre>
     */
    LinkedHashSet& operator +=(const LinkedHashSet& set2);
    LinkedHashSet& operator +=(const ValueType& value);

    /*
     * Operator: *=
     * Usage: set1 *= set2;
     * --------------------
     * Removes any elements from <code>set1</code> that are not present in
     * <code>set2</code>.
     */
    LinkedHashSet& operator *=(const LinkedHashSet& set2);

    /*
     * Operator: -=
     * Usage: set1 -= set2;
     *        set1 -= value;
     * ---------------------
     * Removes the elements from <code>set2</code> (or the single
     * specified value) from <code>set1</code>.  As a convenience, the
     * <code>LinkedHashSet</code> package also overloads the comma operator so
     * that it is possible to remove multiple elements from a set
     * like this:
     *
     *<pre>
     *    digits -= 0, 2, 4, 6, 8;
     *</pre>
     *
     * which removes the values 0, 2, 4, 6, and 8 from the set
     * <code>digits</code>.
     */
    LinkedHashSet& operator -=(const LinkedHashSet& set2);
    LinkedHashSet& operator -=(const ValueType& value);

    /*
     * Additional LinkedHashSet operations
     * -----------------------------------
     * In addition to the methods listed in this interface, the LinkedHashSet
     * class supports the following operations:
     *
     *   - Stream I/O using the << and >> operators
     *   - Deep copying for the copy constructor and assignment operator
     *   - Iteration using the range-based for statement and STL iterators
     *
     * The iteration forms process the LinkedHashSet in the order of insertion.
     */

    /* Private section */

    /**********************************************************************/
    /* Note: Everything below this point in the file is logically part    */
    /* of the implementation and should not be of interest to clients.    */
    /**********************************************************************/

private:
    LinkedHashMap<ValueType, bool> map;  /* Map used to store the element     */
    bool removeFlag = false;             /* Flag to differentiate += and -=   */

public:
    /*
     * Hidden features
     * ---------------
     * The remainder of this file consists of the code required to
     * support the comma operator, deep copying, and iteration.
     * Including these methods in the public interface would make
     * that interface more difficult to understand for the average client.
     */
    LinkedHashSet& operator ,(const ValueType& value) {
        if (this->removeFlag) {
            this->remove(value);
        } else {
            this->add(value);
        }
        return *this;
    }

    using const_iterator = typename LinkedHashMap<ValueType, bool>::const_iterator;
    using iterator = const_iterator;

    const_iterator begin() const;
    const_iterator end() const;
};

template <typename ValueType>
LinkedHashSet<ValueType>::LinkedHashSet(std::initializer_list<ValueType> list) {
    for (const auto& entry: list) {
        add(entry);
    }
}

template <typename ValueType>
void LinkedHashSet<ValueType>::add(const ValueType& value) {
    map.put(value, true);
}

template <typename ValueType>
LinkedHashSet<ValueType>& LinkedHashSet<ValueType>::addAll(const LinkedHashSet& set2) {
    for (ValueType value : set2) {
        add(value);
    }
    return *this;
}

template <typename ValueType>
ValueType LinkedHashSet<ValueType>::back() const {
    if (isEmpty()) {
        error("LinkedHashSet::back: set is empty");
    }
    return map.back();
}

template <typename ValueType>
void LinkedHashSet<ValueType>::clear() {
    map.clear();
}

template <typename ValueType>
bool LinkedHashSet<ValueType>::contains(const ValueType& value) const {
    return map.containsKey(value);
}

template <typename ValueType>
bool LinkedHashSet<ValueType>::containsAll(const LinkedHashSet<ValueType>& set2) const {
    for (const ValueType& value : set2) {
        if (!contains(value)) {
            return false;
        }
    }
    return true;
}

template <typename ValueType>
bool LinkedHashSet<ValueType>::equals(const LinkedHashSet<ValueType>& set2) const {
    // optimization: if literally same set, stop
    if (this == &set2) {
        return true;
    }

    if (size() != set2.size()) {
        return false;
    }

    return isSubsetOf(set2) && set2.isSubsetOf(*this);
}

template <typename ValueType>
ValueType LinkedHashSet<ValueType>::first() const {
    if (isEmpty()) {
        error("LinkedHashSet::first: set is empty");
    }
    return *begin();
}

template <typename ValueType>
ValueType LinkedHashSet<ValueType>::front() const {
    if (isEmpty()) {
        error("LinkedHashSet::front: set is empty");
    }
    return map.front();
}

template <typename ValueType>
void LinkedHashSet<ValueType>::insert(const ValueType& value) {
    map.put(value, true);
}

template <typename ValueType>
bool LinkedHashSet<ValueType>::isEmpty() const {
    return map.isEmpty();
}

template <typename ValueType>
bool LinkedHashSet<ValueType>::isSubsetOf(const LinkedHashSet& set2) const {
    iterator it = begin();
    iterator end = this->end();
    while (it != end) {
        if (!set2.map.containsKey(*it)) {
            return false;
        }
        ++it;
    }
    return true;
}

template <typename ValueType>
bool LinkedHashSet<ValueType>::isSupersetOf(const LinkedHashSet& set2) const {
    return containsAll(set2);
}

template <typename ValueType>
void LinkedHashSet<ValueType>::mapAll(std::function<void (const ValueType &)> fn) const {
    map.mapAll([&](const ValueType& value, bool) {
        fn(value);
    });
}

template <typename ValueType>
void LinkedHashSet<ValueType>::remove(const ValueType& value) {
    map.remove(value);
}

template <typename ValueType>
LinkedHashSet<ValueType>& LinkedHashSet<ValueType>::removeAll(const LinkedHashSet& set2) {
    Vector<ValueType> toRemove;
    for (const ValueType& value : *this) {
        if (set2.map.containsKey(value)) {
            toRemove.add(value);
        }
    }
    for (const ValueType& value : toRemove) {
        remove(value);
    }
    return *this;
}

template <typename ValueType>
LinkedHashSet<ValueType>& LinkedHashSet<ValueType>::retainAll(const LinkedHashSet& set2) {
    Vector<ValueType> toRemove;
    for (const ValueType& value : *this) {
        if (!set2.map.containsKey(value)) {
            toRemove.add(value);
        }
    }
    for (const ValueType& value : toRemove) {
        remove(value);
    }
    return *this;
}

template <typename ValueType>
int LinkedHashSet<ValueType>::size() const {
    return map.size();
}

template <typename ValueType>
std::string LinkedHashSet<ValueType>::toString() const {
    std::ostringstream os;
    os << *this;
    return os.str();
}

/*
 * Implementation notes: set operators
 * -----------------------------------
 * The implementations for the set operators use iteration to walk
 * over the elements in one or both sets.
 */
template <typename ValueType>
bool LinkedHashSet<ValueType>::operator ==(const LinkedHashSet& set2) const {
    return equals(set2);
}

template <typename ValueType>
bool LinkedHashSet<ValueType>::operator !=(const LinkedHashSet& set2) const {
    return !equals(set2);
}

// Implementation note:
// The definitions of <, <=, >, and >= are a bit unintuitive here.
// Because Sets are considered to be "equal" if they have the same elements,
// regardless of order, the equals() method and == / != operators ignore order.
//
// Example: {1, 2, 3, 4} == {4, 3, 2, 1}  true
//
// Similarly, if you ask whether a set is <= or >= to another, this includes
// the notion of equality, so it should return true if the sets contain the same
// elements, regardless of order.
//
// Example: {1, 2, 3, 4} == {4, 3, 2, 1}  true
// Example: {1, 2, 3, 4} <= {4, 3, 2, 1}  true
// Example: {1, 2, 3, 4} >= {4, 3, 2, 1}  true
//
// If you ask whether a set is < or > to another, it is assumed that you don't
// want this to return true if they are "equal", so we must check for non-equality
// before checking the elements pairwise.
//
// Example: {1, 2, 3, 4} <  {4, 3, 2, 1}       false   (because equal)
// Example: {4, 2, 3, 1} >  {1, 3, 2, 4}       false   (because equal)
// Example: {1, 2, 3, 4} <  {4, 3, 2}          true
// Example: {1, 2, 3, 4} <= {4, 3, 2}          true
// Example: {1, 2, 3, 4} <  {4, 3, 2, 1, 0}    true
// Example: {1, 2, 3, 4} <= {4, 3, 2, 1, 0}    true
//
// This issue is unique to LinkedHashSet because Set sorts into a predictable sorted order
// and HashSet opts not to implement <, <=, >, or >= due to its unpredictable hash order.

template <typename ValueType>
bool LinkedHashSet<ValueType>::operator <(const LinkedHashSet& set2) const {
    return !equals(set2) && stanfordcpplib::collections::compare(*this, set2) < 0;
}

template <typename ValueType>
bool LinkedHashSet<ValueType>::operator <=(const LinkedHashSet& set2) const {
    return equals(set2) || stanfordcpplib::collections::compare(*this, set2) <= 0;
}

template <typename ValueType>
bool LinkedHashSet<ValueType>::operator >(const LinkedHashSet& set2) const {
    return !equals(set2) && stanfordcpplib::collections::compare(*this, set2) > 0;
}

template <typename ValueType>
bool LinkedHashSet<ValueType>::operator >=(const LinkedHashSet& set2) const {
    return equals(set2) || stanfordcpplib::collections::compare(*this, set2) >= 0;
}

template <typename ValueType>
LinkedHashSet<ValueType> LinkedHashSet<ValueType>::operator +(const LinkedHashSet& set2) const {
    LinkedHashSet<ValueType> set = *this;
    set.addAll(set2);
    return set;
}

template <typename ValueType>
LinkedHashSet<ValueType> LinkedHashSet<ValueType>::operator +(const ValueType& element) const {
    LinkedHashSet<ValueType> set = *this;
    set.add(element);
    return set;
}

template <typename ValueType>
LinkedHashSet<ValueType> LinkedHashSet<ValueType>::operator *(const LinkedHashSet& set2) const {
    LinkedHashSet<ValueType> set = *this;
    return set.retainAll(set2);
}

template <typename ValueType>
LinkedHashSet<ValueType> LinkedHashSet<ValueType>::operator -(const LinkedHashSet& set2) const {
    LinkedHashSet<ValueType> set = *this;
    return set.removeAll(set2);
}

template <typename ValueType>
LinkedHashSet<ValueType> LinkedHashSet<ValueType>::operator -(const ValueType& element) const {
    LinkedHashSet<ValueType> set = *this;
    set.remove(element);
    return set;
}

template <typename ValueType>
LinkedHashSet<ValueType>& LinkedHashSet<ValueType>::operator +=(const LinkedHashSet& set2) {
    return addAll(set2);
}

template <typename ValueType>
LinkedHashSet<ValueType>& LinkedHashSet<ValueType>::operator +=(const ValueType& value) {
    add(value);
    removeFlag = false;
    return *this;
}

template <typename ValueType>
LinkedHashSet<ValueType>& LinkedHashSet<ValueType>::operator *=(const LinkedHashSet& set2) {
    return retainAll(set2);
}

template <typename ValueType>
LinkedHashSet<ValueType>& LinkedHashSet<ValueType>::operator -=(const LinkedHashSet& set2) {
    return removeAll(set2);
}

template <typename ValueType>
LinkedHashSet<ValueType>& LinkedHashSet<ValueType>::operator -=(const ValueType& value) {
    remove(value);
    removeFlag = true;
    return *this;
}

template <typename ValueType>
std::ostream& operator <<(std::ostream& os, const LinkedHashSet<ValueType>& set) {
    return stanfordcpplib::collections::writeCollection(os, set);
}

template <typename ValueType>
std::istream& operator >>(std::istream& is, LinkedHashSet<ValueType>& set) {
    ValueType element;
    return stanfordcpplib::collections::readCollection(is, set, element, /* descriptor */ "LinkedHashSet::operator >>");
}

template <typename ValueType>
typename LinkedHashSet<ValueType>::const_iterator
LinkedHashSet<ValueType>::begin() const {
    return map.begin();
}

template <typename ValueType>
typename LinkedHashSet<ValueType>::const_iterator
LinkedHashSet<ValueType>::end() const {
    return map.end();
}

/*
 * Template hash function for hash sets.
 * Requires the element type in the LinkedHashSet to have a hashCode function.
 */
template <typename T>
int hashCode(const LinkedHashSet<T>& set) {
    return stanfordcpplib::collections::hashCodeCollection(set, /* orderMatters */ false);
}

/*
 * Function: randomElement
 * Usage: element = randomElement(set);
 * ------------------------------------
 * Returns a randomly chosen element of the given set.
 * Throws an error if the set is empty.
 */
template <typename T>
const T& randomElement(const LinkedHashSet<T>& set) {
    return stanfordcpplib::collections::randomElement(set);
}

#endif // _linkedhashset_h
