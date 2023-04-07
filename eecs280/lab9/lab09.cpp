#include <iostream>

#include "lab09.h"

using namespace std;

// REQUIRES: n >= 1
// EFFECTS: Prints the hailstone sequence starting at n
// NOTE:    Uses tail recursion
void hailstone(int n) {
  // TASK 1 - YOUR CODE HERE
  if(n == 1){
    cout << n << " ";
  }
  else if((n % 2) == 1){
    cout << n << " ";
    hailstone(3*n+1);
  }
  else{
    cout << n << " ";
    hailstone(n/2);
  }
}

// REQUIRES: n >= 1
// EFFECTS: Prints the hailstone sequence starting at n
// NOTE:    Uses iteration
void hailstone_iter(int n) {
  // TASK 1 - YOUR CODE HERE
  while(n != 1){
    cout << n << " ";
    if(n % 2 == 1){
      n = 3*n + 1;
    }
    else{
      n = n / 2;
    }
  }
  cout << n << " ";
}

// REQUIRES: 0 <= digit <= 9, n >= 0
// EFFECTS: Returns the number of times digit appears in n
// NOTE:    Uses recursion
int count_digits(int n, int digit) {
  // TASK 2 - YOUR CODE HERE
  if(n / 10 != 0){
    if(n % 10 == digit) return 1 + count_digits(n / 10, digit);
    else return count_digits(n / 10, digit);
  }
  if(n == digit) return 1;
  else return 0;
}

// REQUIRES: 0 <= digit <= 9, n >= 0
// EFFECTS: Returns the number of times digit appears in n
// NOTE:    Uses iteration
int count_digits_iter(int n, int digit) {
  // TASK 2 - YOUR CODE HERE
  int count = 0;
  if(n == 0 && digit == 0) count++;
  while(n > 0){
    if(n % 10 == digit) count++;
    n = n / 10;
  }  
  return count;
}

// REQUIRES 0 <= digit <= 9, n >= 0
// EFFECTS: Returns count + the number of times digit appears in n
// NOTE:    Uses tail recursion
static int count_digits_helper(int n, int digit, int count) {
  if(n == digit) return ++count;
  if(n / 10 != 0){
    if(n % 10 == digit) count++;
    return count_digits_helper(n / 10, digit, count);
  }
  return count;
}

// REQUIRES: 0 <= digit <= 9, n >= 0
// EFFECTS: Returns the number of times digit appears in n
// NOTE:    Uses tail recursion
int count_digits_tail(int n, int digit) {
  return count_digits_helper(n, digit, 0);
}
