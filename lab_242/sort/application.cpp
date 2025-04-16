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


int maxNumberOfPeople(vector<int>& rooms, vector<int>& people, int k) {
    std::sort(rooms.begin(), rooms.end());
    std::sort(people.begin(), people.end());
    
    int count = 0;
    int r = 0;
    int p = 0;
    while (r < rooms.size() && p < people.size()) {
        int diff = abs(rooms[r] - people[p]);
        if (diff <= k) {
            // suitable room found for people[p]
            count++;
            r++;
            p++;
        }
        else if (rooms[r] < people[p]) {
            // try next room
            r++;
        }
        else {
            // no suitable room, skip people[p]
            p++;
        }
    }
    return count;
}

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int _val = 0, ListNode* _next = nullptr) : val(_val), next(_next) { }
};

// You must use the nodes in the original list and must not modify ListNode's val attribute. 
// Hint: You should complete the function mergeLists first and validate it using our first testcase example

// Merge two sorted lists
ListNode* mergeLists(ListNode* a, ListNode* b) {
    // init merged list
    ListNode* merged = new ListNode();
    ListNode* walker = merged;
    
    // merge a and b into merged
    while (a && b) {
        if (a->val <= b->val) {
            walker->next = a;
            walker = a;
            a = a->next;
        }
        else {
            walker->next = b;
            walker = b;
            b = b->next;
        }
    }
    while (a) {
        walker->next = a;
        walker = a;
        a = a->next;
    }
    while (b) {
        walker->next = b;
        walker = b;
        b = b->next;
    }
    
    // clean up
    walker = merged;
    merged = merged->next;
    delete walker;
    return merged;
}

// Sort and unsorted list given its head pointer
ListNode* mergeSortList(ListNode* head) {
    if (!head || !head->next) {
        // base case: single or no element
        return head;
    }
    
    // get two half of an array
    ListNode* middle = head;
    ListNode* before_middle = nullptr;
    ListNode* tail = head;
    while (tail && tail->next) {
        before_middle = middle;
        middle = middle->next;
        tail = tail->next->next;
    }
    if (before_middle) {
        before_middle->next = nullptr;
    }
    
    // merge sort
    ListNode* first = mergeSortList(head);
    ListNode* second = mergeSortList(middle);
    head = mergeLists(first, second);
    return head;
}

string minDiffPairs(int* arr, int n){
    // STUDENT ANSWER
    std::sort(arr, arr + n);
    
    // get mindiff
    int mindiff = arr[1] - arr[0];
    for (int i = 2; i < n - 1; i++) {
        mindiff = min(mindiff, arr[i] - arr[i - 1]);
    }
    
    // filtered result
    stringstream res;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i + 1] - arr[i] == mindiff) {
            if (res.str() != "") {
                res << ", ";
            }
            res << "(" << arr[i] << ", " << arr[i + 1] << ")";
        }
    }
    return res.str();
}

struct Element 
{
    int val;
    int freq;
    int idx;    // for relative order

    Element(int val, int freq, int idx) : val(val), freq(freq), idx(idx) {}

    bool operator<(const Element &other) const {
        if (this->freq == other.freq) {
            return this->idx < other.idx;
        }
        return this->freq < other.freq;
    }
};

void sortByFrequency(int arr[], int n)
{
    if (n == 0) {
        return;
    }

    // get freq
    vector<Element> elements;
    for (int i = 1; i < n; i++) {
        elements.push_back(Element(arr[i], 1, i));
        for (int j = 0; j < i; i++)
    }

    // sort by freq
    std::sort(elements.begin(), elements.end());
}