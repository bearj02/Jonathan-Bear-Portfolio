/* 
 * join_ropes.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 4 Written.
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

#include "join_ropes.h"

using namespace std;

int join_ropes(const vector<int>& rope_lengths) {
  // TODO
  //assert(false);
  //return 0;
	priority_queue<int, vector<int>, greater<int>> ropes;
	for (auto n : rope_lengths) {
		ropes.push(n);
	}
	int cost = 0;
	while (ropes.size() > 1) {
		int a = ropes.top();
		ropes.pop();
		int b = ropes.top();
		ropes.pop();
		int c = a + b;
		//cout << "Joining " << a << " and " << b << " to get " << c << "\n";
		cost += c;
		ropes.push(c);
	}
	return cost;
}
