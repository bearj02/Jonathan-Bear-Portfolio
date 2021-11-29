#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>
#include<utility>
#include "question_26.h"

using namespace std;

int main(){
    vector<Amino> aminos = {{"ah", 1}, {"bu", 3}, {"tf", 2}, {"lfd", 4}};
    string sequence = "wzzzzbb";
    vector<Amino> output = synthesize(sequence, aminos);
    for(Amino a : output){
        cout << a.str << ", " << a.prio << "; ";
    }
    cout << "\n";
    return 0;
}