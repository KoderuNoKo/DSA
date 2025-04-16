#include <iostream>
#include <string>
#include <cstring>
#include <climits>
#include <utility>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <sstream>

using namespace std;

int pairMatching(vector<int>& nums, int target) {
	// get element freq
	unordered_map<int, int> table;
	for (int num : nums) {
		table[num]++;
	}

	int count = 0;
	// find match
	for (auto& [num, freq] : table) {

		if (freq <= 0) {
			// this num is fully used
			continue;
		}

		if (num == target - num) {
			// a number is a match to itself
			count += freq / 2;
			table[num] = freq % 2;
		}
		else if (table.find(target - num) != table.end() && table[target - num] > 0) {
            // match all possible pairs
			int pairsnum = min(freq, table[target - num]);
            count += pairsnum;
            // update freq after match
            table[num] -= pairsnum;
            table[target - num] -= pairsnum;
		}
	}
    return count;
}