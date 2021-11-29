/* 
 * sort012.cpp 
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 5 Written.
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

#include "sort012.h"

using namespace std;

void sort012(vector<int>& nums) {
	for (int i = 1; i < (int)nums.size(); ++i) {
		int k = i;
		int j = i - 1;
		while ((nums[k] < nums[j]) && j >= 0) {
			swap(nums[k], nums[j]);
			--k;
			--j;
		}
	}
}
/*
int main() {
	vector<int> nums = { 2, 1, 0, 0, 2, 1, 2, 2, 0, 1, 1, 1, 0 };
	sort012(nums);
	for (int i = 0; i < (int)nums.size(); ++i) {
		cout << nums[i] << ", ";
	}
	cout << endl;
	return 0;
}*/
