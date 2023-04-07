#include <iostream>
#include "IntVector.h"

using namespace std;

int main() {
  IntVector v;

  cout << endl << "Calling v.push_back(x) with 1-5..." << endl;
  for (int i = 1; i < 6; ++i) {
    v.push_back(i);
  }

  cout << " Solution: [ 1, 2, 3, 4, 5 ]" << endl;
  cout << "Your code: "; v.print(cout); cout << endl << endl;

  cout << "Calling cout << v..." << endl;
  cout << " Solution: [ 1, 2, 3, 4, 5 ]" << endl;
  cout << "Your code: " << v << endl << endl;

  cout << "Calling v.pop_back() twice..." << endl;
  v.pop_back(); v.pop_back();
  cout << " Solution: [ 1, 2, 3 ]" << endl;
  cout << "Your code: "; v.print(cout); cout << endl << endl;

  cout << "Calling v.push_back(-1)..." << endl;
  v.push_back(-1);
  cout << " Solution: [ 1, 2, 3, -1 ]" << endl;
  cout << "Your code: "; v.print(cout); cout << endl << endl;

  cout << "Calling v.at(0) and v.at(3)..." << endl;
  cout << " Solution: v.at(0) = 1 and v.at(3) = -1" << endl;
  cout << "Your code: v.at(0) = " << v.at(0)
       << " and v.at(3) = " << v.at(3) << endl << endl;

  cout << "Calling v[0] and v[3]..." << endl;
  cout << " Solution: v[0] = 1 and v[3] = -1" << endl;
  cout << "Your code: v[0] = " << v[0]
       << " and v[3] = " << v[3] << endl << endl;

  cout << "Calling const versions of cv.at(0) and cv[0]..." << endl;
  const IntVector &cv = v;
  cout << " Solution: cv.at(0) = 1 and cv[3] = -1" << endl;
  cout << "Your code: cv.at(0) = " << cv.at(0)
       << " and cv[3] = " << cv[3] << endl << endl;

  cout << "Emptying using while (!v.empty()) { v.pop_back(); }" << endl;
  while (!v.empty()) { v.pop_back(); }
  cout << " Solution: [ ]" << endl;
  cout << "Your code: "; v.print(cout); cout << endl << endl;

  cout << "Filling with 2 using while (!v.full()) { v.push_back(2); }" << endl;
  while (!v.full()) { v.push_back(2); }
  cout << " Solution: v.size() = 100 and v.at(99) = 2" << endl;
  cout << "Your code: v.size() = " << v.size()
       << " and v.at(99) = " << v.at(99) << endl;

  return 0;
}
