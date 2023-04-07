#include <iostream>

#include "ArrayIntVector.h"

using namespace std;

int main() {
  ArrayIntVector v(5);

  cout << endl << "Calling v.push_back(x) for x=1,2,3,4,5..." << endl;
  for (int i = 1; i < 6; ++i) { v.push_back(i); }

  cout << " Solution: [ 1, 2, 3, 4, 5 ]" << endl;
  cout << "Your code: " << v << endl << endl;

  cout << "Calling v.pop_back() twice..." << endl;
  v.pop_back(); v.pop_back();
  cout << " Solution: [ 1, 2, 3 ]" << endl;
  cout << "Your code: " << v << endl << endl;

  cout << "Calling v.push_back(-1)..." << endl;
  v.push_back(-1);
  cout << " Solution: [ 1, 2, 3, -1 ]" << endl;
  cout << "Your code: " << v << endl << endl;

  cout << "Calling v.at(0) and v.at(3)..." << endl;
  cout << " Solution: v.at(0) = 1 and v.at(3) = -1" << endl;
  cout << "Your code: v.at(0) = " << v.at(0)
       << " and v.at(3) = " << v.at(3) << endl << endl;

  cout << "Emptying using while (!v.empty()) { v.pop_back(); }" << endl;
  while (!v.empty()) { v.pop_back(); }
  cout << " Solution: [ ]" << endl;
  cout << "Your code: " << v << endl << endl;

  cout << "Adding 2 one hundred times." << endl;
  for (int i = 0; i < 100; ++i) { v.push_back(2); }
  cout << " Solution: v.size() = 100 and v.at(99) = 2" << endl;
  cout << "Your code: v.size() = " << v.size()
       << " and v.at(99) = " << v.at(99) << endl;
}
