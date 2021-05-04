#include "lab02.h"

#include <iostream>

using namespace std;

int main(){
  int arr1[5] = {0,1,3,3,4};

  // TASK 1
  cout << "Testing printArrayIndex:" << endl;
  cout << " Solution: 0 1 3 3 4 " << endl;
  cout << "Your code: "; printArrayIndex(arr1,5); cout << endl;

  cout << "Testing printArrayPointer:" << endl;
  cout << " Solution: 0 1 3 3 4 " << endl;
  cout << "Your code: "; printArrayPointer(arr1,5); cout << endl;

  // TASK 2
  cout << "Testing slideRight: " << endl;
  cout << " Solution: 4 0 1 3 3 " << endl;
  slideRight(arr1,5);
  cout << "Your code: "; printArrayPointer(arr1,5); cout << endl;
  
  int arr2[5] = {1,2,3,4,5};
  cout << "Testing flip:" << endl;
  cout << " Solution: 5 4 3 2 1 " << endl;
  flip(arr2,5);
  cout << "Your code: "; printArrayPointer(arr2,5); cout << endl;

  // TASK 4
  int arr3[10] = {1,3,3,4,4,4,5,7,9,9};
  cout << "Testing removeDuplicates:" << endl;
  cout << " Solution: 1 3 4 5 7 9 " << endl;
  int num = removeDuplicates(arr3,10);
  cout << "Your code: "; printArrayPointer(arr3,num); cout << endl;
}
