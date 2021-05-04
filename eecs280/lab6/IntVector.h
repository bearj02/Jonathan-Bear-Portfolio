#ifndef INTVECTOR_H
#define INTVECTOR_H

#include <iostream>

class IntVector {
  // Container that provides random access to any element by an index.
  // The capacity (maximum size) of an IntVector is 100 elements.

public:

  // Maximum capacity of the IntVector
  static const int CAPACITY = 100;

  // Default constructor.
  //EFFECTS: Constructs an empty IntVector.
  IntVector();

  //REQUIRES: this IntVector is not full
  //MODIFIES: this IntVector
  //EFFECTS:  Adds value to the end of this IntVector.
  void push_back(int value);

  //REQUIRES: this IntVector is not empty
  //MODIFIES: this IntVector
  //EFFECTS:  Removes the last element in this IntVector.
  void pop_back();

  //REQUIRES: 0 <= index and index < number of elements in this IntVector
  //EFFECTS:  Returns (by reference) the element at the given index.
  int & at(int index);

  //REQUIRES: 0 <= index and index < number of elements in this IntVector
  //EFFECTS:  Returns (by reference) the element at the given index.
  const int & at(int index) const;

  //REQUIRES: 0 <= index and index < number of elements in this IntVector
  //EFFECTS:  Returns (by reference) the element at the given index.
  int & operator[](int index);

  //REQUIRES: 0 <= index and index < number of elements in this IntVector
  //EFFECTS:  Returns (by reference) the element at the given index.
  const int & operator[](int index) const;

  //EFFECTS:  Returns the number of elements of this IntVector.
  int size() const;

  //EFFECTS:  Returns true if this IntVector is empty, false otherwise.
  bool empty() const;

  //EFFECTS:  Returns true if this IntVector is at capacity, false otherwise.
  bool full() const;

  //EFFECTS:  Prints to os all elements in this IntVector in the format:
  //          "[ 1, 2, 3, 4, 5 ]" (Note that there is no trailing newline)
  void print(std::ostream &os) const;

private:
  // The array to hold the N elements stored in this vector, in the first N
  // slots. The array has enough memory to hold the maximum number of elements.
  int data[CAPACITY];

  // The number of elements in the IntVector.
  // Invariants: 0 <= num_elts and num_elts <= CAPACITY
  int num_elts;

  //EFFECTS:  Returns true if the representation invariants hold.
  //          For IntVector, the only invariants are 0 <= num_elts and
  //          num_elts <= CAPACITY.
  bool check_invariants() const;
};

//EFFECTS:  Prints to os all elements in the IntVector in the format:
//          "[ 1, 2, 3, 4, 5 ]" (Note that there is no trailing newline)
std::ostream & operator<<(std::ostream &os, const IntVector &v);

#endif // INTVECTOR_H
