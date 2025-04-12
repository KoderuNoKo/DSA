#include <iostream> 
#include <fstream> 
#include <string> 
#include <cstring> 
#include <stack> 
#include <vector> 

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

string removeDuplicates(string S){
    /*TODO*/
    stack<char> stk;
    for (char ch : S) {
        if (!stk.empty() && ch == stk.top()) {
            stk.pop();
        }
        stk.push(ch);
    }
    string result;
    while (!stk.empty()) {
        result = stk.top() + result;
    }
    return result;
}

int baseballScore(string ops){
    /*TODO*/
    stack<int> record;
    for (char op : ops) {
        if (op == 'C') {
            record.pop();
        }
        else if (op == 'D') {
            record.push(record.top() * 2);
        }
        else if (op == '+') {
            int temp = record.top(); 
            record.pop();
            int sum = record.top() + temp;
            record.push(temp);
            record.push(sum);
        }
        else {
            record.push(op - '0');
        }
    }
    int sum = 0;
    while (!record.empty()) {
        sum += record.top();
        record.pop();
    }
    return sum;
}

bool isValidParentheses (string s){
    /*TODO*/
    stack<char> stk;
    for (char ch : s) {
        if (ch == '}' || ch == ']' || ch == ')') 
        {
            if (stk.empty()) {
                return false;
            }
            else {
                char op = stk.top();
                if ((ch == '}' && op != '{') ||
                    (ch == ']' && op != '[') ||
                    (ch == ')' && op != '(')) 
                {
                    return false;
                }
                stk.pop();
            }
        }
        else {
            stk.push(ch);
        }
    }
    return stk.empty();
}

bool canEatFood(int maze[5][5], int fx, int fy)
{
    /*TODO*/
    stack<int> stk;
    bool visited[5][5];
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            visited[i][j] = false;

    stk.push(0); // x
    stk.push(0); // y
    int move[][2] = {
        {0, 1},
        {-1, 0},
        {0, -1},
        {1, 0}
    };

    while(!stk.empty()) {
        int y = stk.top(); stk.pop();
        int x = stk.top(); stk.pop();

        if (x == fx && y == fy) {
            return true;
        }
        else {
            for (int i = 0; i < 4; i++) {
                int nextx = x + move[i][0];
                int nexty = y + move[i][1];
                if (nextx < 0 || nextx > 4 || nexty < 0 || nexty > 4 || maze[nextx][nexty] == 0 || visited[nextx][nexty]) {
                    continue;
                }
                else {
                    visited[nextx][nexty] = true;
                    stk.push(nextx);
                    stk.push(nexty);
                }
            }
        }
    }
    return false;
}

vector<int> stock_span(const vector<int>& ns) {
    // STUDENT ANSWER
    vector<int> spans(ns.size(), 0);
    stack<int> idx;

    spans[0] = 1;
    idx.push(0);

    for (size_t i = 1; i < ns.size(); i++) {
        while (!idx.empty() && ns[idx.top()] < ns[i]) {
            idx.pop();
        }
        spans[i] = idx.empty() ? (i + 1) : (i - idx.top());
        idx.push(i);
    }
    return spans;
}