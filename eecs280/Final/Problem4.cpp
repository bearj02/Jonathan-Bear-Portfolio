#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

class SortedIntSet {
private:
  static const int DEFAULT_CAPACITY = 10;
  int *data;       // data is a dynamically allocated array
  int currentSize; // currentSize = elements in use
  int capacity;    // the current capacity

  // MODIFIES: capacity, data
  // EFFECTS:  Change underlying representation to use a dynamic
  //           array of 2 * capacity elements
  void grow();

public:
  SortedIntSet();
  SortedIntSet(const SortedIntSet &copy);
  SortedIntSet &operator=(const SortedIntSet &rhs);
  ~SortedIntSet();

  // REQUIRES: data is sorted in least to greatest order
  // MODIFIES: data, currentSize
  // EFFECTS:  Adds datum to data, if not an existing element 
  //           data maintains least to greatest ordering
  void insert(int datum);

  // REQUIRES: the set is not empty, data is sorted in least to greatest order
  // MODIFIES: data, currentSize
  // EFFECTS:  Deletes datum from data, if it is an existing element
  void remove(int datum);

  // REQUIRES: data is sorted in least to greatest order
  // EFFECTS:  Returns true if datum is a part of set, false otherwise
  bool contains(int datum);
};