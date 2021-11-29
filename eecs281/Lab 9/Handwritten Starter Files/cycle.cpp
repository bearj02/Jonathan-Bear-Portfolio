/* 
 * cycle.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 9 Written.
 * SUBMIT ONLY THIS FILE TO GRADESCOPE.
 */

// Common #includes for convience.
// No need to use them. 
// Remove any of them if you want.
#include <algorithm>
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
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "cycle.h"

using namespace std;

bool is_cycle(const vector<vector<int>> &adj_list, int next, int origin){
  if(adj_list[next][origin] == 1) return true;
  for(int i = 0; i < (int)adj_list[next].size(); ++i){
    if(adj_list[next][i] == 1){
      if(is_cycle(adj_list,i,origin)) return true;
      //if(is_cycle(adj_list,i,next)) return true;
    }
  }
  return false;
}

//Given an undirected connected graph, check if the graph contains a cycle
bool is_graph_cyclic(const vector<vector<int>> &adj_list) {
  
  
  if(adj_list.size() <= 2) return false;
  return is_cycle(adj_list,0,0);
}