/*
 * Starter file for:
 *   F21, Midterm Exam, Question 26
 *
 * Do not try to submit this file to the autograder!
 * Upload it to Gradescope:
 *   [F21] Midterm Question 26
 *
 * Before uploading, as you "browse" for the file, check the last modified time!
 * It should be when you last saved the file.
 * Make sure you are uploading a file named question_26.cpp
 */


// You may find these short functions useful, converting between char and int.
char intToChar(int i) {
    return static_cast<char>('a' + i);
} // intToChar()

int charToInt(char i) {
    return static_cast<int>(i - 'a');
} // charToInt()

// DO NOT MODIFY ANYTHING ABOVE THIS LINE!

// You may use whatever you want, we just added some standard includes
// that might be useful for any question.  If you want to use something
// else, make sure to #include it.
// Additional includes do not add to your line count.

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>
#include<utility>

using namespace std;

struct Amino {
    string str;
    int prio;
  
    Amino(char c): str(1, c), prio(0) { }
    Amino(string s, int p): str(s), prio(p) { }
}; // DO NOT MODIFY THE STRUCT AMINO


struct AminoComp {
    bool operator()(const Amino &left, const Amino &right) const { 
        // TODO: Finish this comparator
        if(left.prio < right.prio) return false;
        else if (left.prio > right.prio) return true;
        else return left.str < right.str;
    }
};
/*
struct achar {
    char a;
    int freq;
};

struct acharComp {
    bool operator()(const achar &left, const achar &right) const {
        if(left.freq < right.freq) return false;
        else if (left.freq > right.freq) return true;
        else return left.a < right.a;
    }
};

vector<Amino> synthesize(string &sequence, vector<Amino> &aminos) {
    // TODO: Write this function
    vector<achar> achars;
    for(char a : sequence){
        bool updated = false;
        for(size_t i = 0; i < achars.size(); ++i){
            if(a == achars[i].a){
                ++(achars[i].freq);
                updated = true;
                break;
            }
        }
        if(!updated) achars.push_back(achar{a, 1});
    }
    size_t threshold = min((int)achars.size(), (int)aminos.size());
    priority_queue<Amino, vector<Amino>, AminoComp> as(aminos.begin(),aminos.end());
    aminos.clear();
    sort(achars.begin(),achars.end(),acharComp{});
    for(size_t j = 0; j < threshold; ++j){
        Amino am = as.top();
        as.pop();
        achar a = achars[j];
        am.str += a.a;
        am.prio += a.freq;
        aminos.push_back(am);
    }
    while(as.size() > 0){
        aminos.push_back(as.top());
        as.pop();
    }
    return aminos;
} // synthesize()*/

vector<Amino> synthesize(string &sequence, vector<Amino> &aminos) {
    // TODO: Write this function
    vector<Amino> achars;
    for(char a : sequence){
        bool updated = false;
        for(size_t i = 0; i < achars.size(); ++i){
            if(a == achars[i].str[0]){
                ++(achars[i].prio);
                updated = true;
                break;
            }
        }
        if(!updated) achars.push_back(Amino(string(1, a),1));
    }
    size_t threshold = min((int)achars.size(), (int)aminos.size());
    sort(aminos.begin(),aminos.end(), AminoComp{});
    sort(achars.begin(),achars.end(), AminoComp{});
    for(size_t j = 0; j < threshold; ++j){
        aminos[j].str += achars[j].str;
        aminos[j].prio += achars[j].prio;
    }
    return aminos;
} // synthesize()