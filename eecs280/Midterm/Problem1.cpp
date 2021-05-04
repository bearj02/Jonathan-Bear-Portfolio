#include <iostream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;



// REQUIRES: N > 0 && M > 0;
// MODIFIES: Nothing
// EFFECTS: Returns vector containing the first N multiples of M, starting at M.
//          I.e. {M, 2*M, … , N*M}
// Example: init_mult_M(2, 4) -> {4, 8}
vector<int> init_mult_M(int N, int M) {
    vector<int> v; 
    for(int i = 1; i < N; ++i) {
        v.push_back(M * i);
    }
    return v;
}

int main() {
    vector<int> stuff = init_mult_M(4,3);
    cout << stuff[0] << " " << stuff[1] << " " << stuff[2] << " " << stuff[3] << endl;
}