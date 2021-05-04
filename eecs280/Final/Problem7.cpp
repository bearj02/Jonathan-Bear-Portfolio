#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;



// Tail-recursive helper function for sum_multiples().
int sum_multiples_helper(int n, int multiplier, int c) {
    if(n == c){
        return n*multiplier;
    }
    return n*multiplier + sum_multiples_helper(n-1, multiplier,c);
}

// REQUIRES: n >= 0
// EFFECTS:  returns the sum of a multiple of numbers from n to 0, where 
//           the multiplier is passed in as a parameter
// EXAMPLE:  sum_multiples( 3, 7 ) returns 3*7 + 2*7 + 1*7 + 0*7 == 42
int sum_multiples(int n, int multiplier) {
  return sum_multiples_helper(n, multiplier, 0);
}

int main(){
    cout << sum_multiples(4,7) << endl;
}