#include <iostream>

#include "ArrayIntVector.h"

using namespace std;

int main(){
  cout << "Creating vector v with capacity 5." << endl;
  ArrayIntVector * v= new ArrayIntVector(5);

  cout << endl << "Calling v->push_back(x) for x=1,2,3,4,5..." << endl;
  for (int i = 1; i < 6; ++i) { v->push_back(i); }
  cout << " Solution:  v=[ 1, 2, 3, 4, 5 ]" << endl;
  cout << "Your code:  v=" << *v << endl; cout << endl;

  cout << "Calling v->pop_back() twice..." << endl;
  v->pop_back(); v->pop_back();
  cout << " Solution:  v=[ 1, 2, 3 ]" << endl;
  cout << "Your code:  v=" << *v << endl;
  cout << endl;

  cout << "Using the copy constructor to create two copies of v" << endl;
  ArrayIntVector *v1 = new ArrayIntVector(*v);
  ArrayIntVector *v2 = new ArrayIntVector(*v);
  cout << " Solution:  v=[ 1, 2, 3 ]" << endl;
  cout << "Your code:  v=" << *v << endl;
  cout << " Solution: v1=[ 1, 2, 3 ]" << endl;
  cout << "Your code: v1=" << *v1 << endl;
  cout << " Solution: v2=[ 1, 2, 3 ]" << endl;
  cout << "Your code: v2=" << *v2 << endl;
  cout << endl;

  cout << "Calling v->pop_back()" << endl;
  v->pop_back();
  cout << " Solution:  v=[ 1, 2 ]" << endl;
  cout << "Your code:  v=" << *v << endl;
  cout << " Solution: v1=[ 1, 2, 3 ]" << endl;
  cout << "Your code: v1=" << *v1 << endl;
  cout << " Solution: v2=[ 1, 2, 3 ]" << endl;
  cout << "Your code: v2=" << *v2 << endl;
  cout << endl;

  cout << "Assigning *v2 = *v" << endl;
  *v2 = *v;
  cout << " Solution:  v=[ 1, 2 ]" << endl;
  cout << "Your code:  v=" << *v << endl;
  cout << " Solution: v1=[ 1, 2, 3 ]" << endl;
  cout << "Your code: v1=" << *v1 << endl;
  cout << " Solution: v2=[ 1, 2 ]" << endl;
  cout << "Your code: v2=" << *v2 << endl;
  cout << endl;

  cout << "Calling v1->push_back(4)" << endl;
  v1->push_back(4);
  cout << " Solution:  v=[ 1, 2 ]" << endl;
  cout << "Your code:  v=" << *v << endl;
  cout << " Solution: v1=[ 1, 2, 3, 4 ]" << endl;
  cout << "Your code: v1=" << *v1 << endl;
  cout << " Solution: v2=[ 1, 2 ]" << endl;
  cout << "Your code: v2=" << *v2 << endl;
  cout << endl;

  cout << "Calling v->pop_back()" << endl;
  v->pop_back();
  cout << " Solution:  v=[ 1 ]" << endl;
  cout << "Your code:  v=" << *v << endl;
  cout << " Solution: v1=[ 1, 2, 3, 4 ]" << endl;
  cout << "Your code: v1=" << *v1 << endl;
  cout << " Solution: v2=[ 1, 2 ]" << endl;
  cout << "Your code: v2=" << *v2 << endl;
  cout << endl;

  cout << "Deleting v" << endl;
  delete v;
  cout << " Solution: v1=[ 1, 2, 3, 4 ]" << endl;
  cout << "Your code: v1=" << *v1 << endl;
  cout << " Solution: v2=[ 1, 2 ]" << endl;
  cout << "Your code: v2=" << *v2 << endl;
  cout << endl;

  cout << "Deleting v1" << endl;
  delete v1;
  cout << " Solution: v2=[ 1, 2 ]" << endl;
  cout << "Your code: v2=" << *v2 << endl;
  cout << endl;

  cout << "Deleting v2" << endl;
  delete v2;
}
