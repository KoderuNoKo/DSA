#include<iostream>
#include<stack>
#include<vector>

using namespace std;

vector<int> nextGreater(vector<int>& arr)
{
    vector<int> result(arr.size(), -1);
    stack<int> idx;
    for (int i = 0; i < arr.size(); i++) {
        while(!idx.empty() && arr[idx.top()] < arr[i]) {
            result[idx.top()] = arr[i];
            idx.pop();
        }
        idx.push(i);
    }
    return result;
}