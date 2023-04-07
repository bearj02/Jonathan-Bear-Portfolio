#include <iostream>
#include <cassert>
#include "IntVector.h"

using namespace std;

// Default constructor.
//EFFECTS: Constructs an empty IntVector.
IntVector::IntVector() : num_elts(0) {}

//REQUIRES: this IntVector is not full
//MODIFIES: this IntVector
//EFFECTS:  Adds value to the end of this IntVector.
void IntVector::push_back(int value) {
  assert(!full()); // TASK 1 - YOUR CODE HERE
  assert(check_invariants());
  data[num_elts++] = value;
}

//REQUIRES: this IntVector is not empty
//MODIFIES: this IntVector
//EFFECTS:  Removes the last element in this IntVector.
void IntVector::pop_back() {
  assert(!empty()); // TASK 1 - YOUR CODE HERE
  assert(check_invariants());
  num_elts--;
}

//REQUIRES: 0 <= index and index < number of elements in this IntVector
//EFFECTS:  Returns (by reference) the element at the given index.
int & IntVector::at(int index) {
  assert(0 <= index && index < num_elts); // TASK 1 - YOUR CODE HERE
  assert(check_invariants());
  return data[index];
}

//REQUIRES: 0 <= index and index < number of elements in this IntVector
//EFFECTS:  Returns (by reference) the element at the given index.
const int & IntVector::at(int index) const {
  assert(0 <= index && index < num_elts); // TASK 1 - YOUR CODE HERE
  assert(check_invariants());
  return data[index];
}

//REQUIRES: 0 <= index and index < number of elements in this IntVector
//EFFECTS:  Returns (by reference) the element at the given index.
int & IntVector::operator[](int index) {
  assert(0 <= index && index < num_elts); // TASK 1 - YOUR CODE HERE
  assert(check_invariants());
  return data[index];
}

//REQUIRES: 0 <= index and index < number of elements in this IntVector
//EFFECTS:  Returns (by reference) the element at the given index.
const int & IntVector::operator[](int index) const {
  assert(0 <= index && index < num_elts); // TASK 1 - YOUR CODE HERE
  assert(check_invariants());
  return data[index];
}

//EFFECTS:  Returns the number of elements of this IntVector.
int IntVector::size() const {
  assert(check_invariants());
  return num_elts; // TASK 1 - YOUR CODE HERE
}

//EFFECTS:  Returns true if this IntVector is empty, false otherwise.
bool IntVector::empty() const {
  assert(check_invariants());
  return (num_elts == 0); // TASK 1 - YOUR CODE HERE
}

//EFFECTS:  Returns true if this IntVector is at capacity, false otherwise.
//          That is, you may add elements if and only if full() is false.
bool IntVector::full() const {
  assert(check_invariants());
  return (num_elts == CAPACITY); // TASK 1 - YOUR CODE HERE
}

//EFFECTS:  Prints to os all elements in this IntVector in the format:
//          "[ 1, 2, 3, 4, 5 ]" (Note that there is no trailing newline)
void IntVector::print(ostream &os) const {
  assert(check_invariants());
  os << "[";
  for (int i = 0; i < num_elts; i++) {
    os << " " << data[i];
    if (i < num_elts - 1) {
      os << ",";
    }
  }
  os << " ]";
}

//EFFECTS:  Returns true if the representation invariants hold.
//          For IntVector, the only invariants are 0 <= num_elts and
//          num_elts <= CAPACITY.
bool IntVector::check_invariants() const {
  return (num_elts >= 0 && num_elts <= CAPACITY); // TASK 3 - YOUR CODE HERE
}

//EFFECTS:  Prints to os all elements in the IntVector in the format:
//          "[ 1, 2, 3, 4, 5 ]" (Note that there is no trailing newline)
ostream & operator<<(ostream & os, const IntVector &v) {
  
  // TASK 1 - YOUR CODE HERE
  v.print(os);

  // Always return the stream at end of the insertion operator
  return os;
}
