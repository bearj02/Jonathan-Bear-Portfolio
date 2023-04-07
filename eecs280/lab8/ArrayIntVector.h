#ifndef ARRAYINTVECTOR_H
#define ARRAYINTVECTOR_H

#include <iostream>
#include <cassert>
#include <string>

class ArrayIntVector {
  // A dynamic-array-based implementation of an int vector, which
  // provides random access to any element by an index.
  // An ArrayIntVector can hold arbitrarily many elements.

public:
  //REQUIRES: init_capacity >= 1
  //EFFECTS:  Creates an empty ArrayIntVector with the specified
  //          initial data capacity.
  ArrayIntVector(int init_capacity);

  //EFFECTS: Creates an empty ArrayIntVector with a default initial
  //         data capacity.
  ArrayIntVector() : ArrayIntVector(DEFAULT_CAPACITY) {}

  // Copy Constructor
  //EFFECTS: Constructs an ArrayIntVector with the same contents as other.
  ArrayIntVector(const ArrayIntVector& other);

  // Assignment Operator
  //MODIFIES: this ArrayIntVector
  //EFFECTS: Replace this ArrayIntVector's contents with a copy of the contents
  //         of rhs.
  ArrayIntVector& operator=(const ArrayIntVector &rhs);

  // Destructor
  ~ArrayIntVector();

  //MODIFIES: this ArrayIntVector
  //EFFECTS:  Adds value to the end of this ArrayIntVector.
  void push_back(int value);

  //REQUIRES: this ArrayIntVector is not empty
  //MODIFIES: this ArrayIntVector
  //EFFECTS:  Removes the last element in this ArrayIntVector.
  void pop_back();

  //REQUIRES: 0 <= index < number of elements in this ArrayIntVector
  //EFFECTS:  Returns (by reference) the element at the given index.
  int &at(int index);

  //REQUIRES: 0 <= index < number of elements in this ArrayIntVector
  //EFFECTS:  Returns (by reference) the element at the given index.
  const int &at(int index) const;

  //REQUIRES: 0 <= index < number of elements in this ArrayIntVector
  //EFFECTS:  Returns (by reference) the element at the given index.
  int &operator[](int index);

  //REQUIRES: 0 <= index < number of elements in this ArrayIntVector
  //EFFECTS:  Returns (by reference) the element at the given index.
  const int &operator[](int index) const;

  //EFFECTS:  Returns the number of elements in this ArrayIntVector.
  int size() const;

  //EFFECTS:  Returns true if this ArrayIntVector is empty, false otherwise.
  bool empty() const;

  //EFFECTS:  Returns the number of elements that can be held in currently
  //          allocated storage.
  int capacity() const;

  //EFFECTS:  Prints to os all elements in this ArrayIntVector in the format:
  //          "[ 1, 2, 3, 4, 5 ]" (Note that there is no trailing newline)
  void print(std::ostream &os) const;

private:
  // EFFECTS: Doubles the storage capacity of this ArrayIntVector.
  //          More precisely:
  //            1. doubles capacity
  //            2. allocates a new dynamic array with the new capacity
  //            3. copies over the elements from the old data array
  //            4. free the memory for the old data array
  //            5. sets data to point to the new array
  void grow();

  // A pointer to an (dynamically allocated) array to hold the N elements
  // stored in this vector, in the first N slots. If the number of elements
  // exceeds its current capacity, data will be reallocated.
  // INVARIANT: data != nullptr (it is a valid pointer)
  int *data;

  // The maximum number of elements data can currently hold.
  // INVARIANT: 1 <= elts_capacity
  int elts_capacity;

  // The number of elements in the ArrayIntVector.
  // INVARIANT: 0 <= num_elts <= elts_capacity
  int num_elts;

  // Default initial capacity of an ArrayIntVector.
  static const int DEFAULT_CAPACITY = 10;

  // EFFECTS: Contains asserts that fail if the representation
  //          invariants do not hold.
  void check_invariants() const {
    assert(0 <= num_elts && num_elts <= elts_capacity);
    assert(1 <= elts_capacity);
    assert(data);
  }
};

//EFFECTS:  Prints to os all elements in the ArrayIntVector in the format:
//          "[ 1, 2, 3, 4, 5 ]" (Note that there is no trailing newline)
std::ostream &operator<<(std::ostream &os, const ArrayIntVector &v);

#endif // ARRAYINTVECTOR_H
