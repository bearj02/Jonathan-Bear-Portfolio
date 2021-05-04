#include <iostream>

#include "lab09.h"

using namespace std;

void hailstone_test(int n);
void count_digits_test(int n, int digit);

int main() {
  // Testing code
  cout << "Running tests for hailstone..." << endl;
  hailstone_test(5);
  hailstone_test(8);
  hailstone_test(14);

  cout << "Running tests for count_digits..." << endl;
  count_digits_test(2120, 2);
  count_digits_test(123, 7);
  count_digits_test(20, 0);
  count_digits_test(0, 8);
  count_digits_test(0, 0);
}

// Helper function for testing code
void hailstone_test(int n) {
  cout << "Testing hailstone(" << n << ')' << endl;
  cout << "    Recursive: "; hailstone(n);  cout << endl;
  cout << "    Iterative: "; hailstone_iter(n);  cout << endl;
}

// Helper function for testing code
void count_digits_test(int n, int digit) {
  cout << "Testing count_digits(" << n << ", " << digit << ')' << endl;
  cout << "    Recursive:      " << count_digits(n, digit) << endl;
  cout << "    Iterative:      " << count_digits_iter(n, digit) << endl;
  cout << "    Tail Recursive: " << count_digits_tail(n, digit) << endl;
}
