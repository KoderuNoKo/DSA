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

using namespace std;

int numberOfFriendGroups(vector<vector<int>>& friends) 
{
    // STUDENT ANSWER
    int numgr = 0;
    vector<bool> visited(friends.size(), false);
    list<int> buffer;

    for (int i = 0; i < friends.size(); i++) {
        // skip people connected in other groups
        if (visited[i]) {
            continue;
        }
        // new group
        int start = i;
        numgr++;
        // connect this group
        buffer.push_back(start);
        visited[start] = true;
        while (!buffer.empty()) {
            start = buffer.front();
            buffer.pop_front();
            for (int next : friends[start]) {
                if (!visited[next]) {
                    visited[next] = true;
                    buffer.push_back(next);
                }
            }
        }
    }
    return numgr;
}

