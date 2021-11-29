/*
 * replace_words.cpp
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 7 Written.
 * SUBMIT ONLY THIS FILE TO GRADESCOPE.
 */

// Common #includes for convience.
// No need to use them.
// Remove any of them if you want.
#include <algorithm>
#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "replace_words.h"

using namespace std;
/*
vector<string> replace_words(const vector<string>& prefixes,
                             const vector<string>& sentence) {
  // TODO
  vector<string> newsentence;
  vector<string> pref = prefixes;
  sort(pref.begin(),pref.end());
  for(string s : sentence){
    string replace = s;
    //get replace
    for(string p : pref){
      if(replace.size() < p.size()){
        break;
      }
      if(s.substr(0,p.size()).compare(p) == 0){
        replace = p;
      }
    }
    newsentence.push_back(replace);
  }
  return newsentence;
}*/

int main(){
  vector<string> prefixes = {"cat", "ratt", "bat", "rat"};
  vector<string> sentence = {"the", "cattle", "was", "rattled", "by", "the", "battery"};
  vector<string> output = replace_words(prefixes,sentence);
  for(string s : output){
    cout << s << " ";
  }
  cout << "\n";
}


vector<string> replace_words(const vector<string>& prefixes,
                             const vector<string>& sentence) {
  // TODO
  vector<string> newsentence;
  for(string s : sentence){
    string replace = s;
    //get replace
    for(string p : prefixes){
      if(replace.size() < p.size()){
        continue;
      }
      if(s.substr(0,p.size()).compare(p) == 0){
        replace = p;
      }
    }
    newsentence.push_back(replace);
  }
  return newsentence;
}