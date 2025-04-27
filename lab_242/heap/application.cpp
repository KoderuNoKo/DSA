//* --------------| Heap Sort |-------------- *//
#define SEPARATOR "#<ab@17943918#@>#"
#ifndef SORTING_H
#define SORTING_H
#include <iostream>
#include <queue>
using namespace std;
template <class T>
class Sorting {
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        long size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }
    
    //Helping functions go here
    static void reheapDown(T* start, T* end, int index)
    {
        int numberOfElements = end - start;
        int minIndex = index;
        int leftChild = index*2 + 1;
        int rightChild = index*2 + 2;
        
        if (leftChild < numberOfElements && start[minIndex] > start[leftChild]) {
            minIndex = leftChild;
        }
        if (rightChild < numberOfElements && start[minIndex] > start[rightChild]) {
            minIndex = rightChild;
        }
        
        if (minIndex != index) {
            swap(start[minIndex], start[index]);
            Sorting::reheapDown(start, end, minIndex);
        }
    }

    static void reheapUp(T* start, T* end, int index)
    {
        int parent = (index - 1)/2;
        while (index > 0 && start[parent] > start[index]) {
            swap(start[parent], start[index]);
            index = parent;
            parent = (parent - 1)/2;
        }
    }

    static void heapSort(T* start, T* end){
        //TODO
        // heapify
        int size = end - start;
        int nonLeaf = (size - 2)/2;
        for (int i = nonLeaf; i >= 0; i--) {
            Sorting<T>::reheapDown(start, end, i);
        }

        // build sorted array
        queue<T> result;
        while (start != end) {
            end--;
            result.push(start[0]);
            start[0] = *end;
            Sorting<T>::reheapDown(start, end, 0);
        }
        result.push(start[0]);

        for (int i = 0; i < size; i++) {
            start[i] = result.front();
            result.pop();
        }
        end = start + size;
        
        Sorting<T>::printArray(start,end);
    }
};

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

int leastAfter(vector<int>& nums, int k) {
    // STUDENT ANSWER
    std::make_heap(nums.begin(), nums.end(), std::greater<int>());

    // perform operation k times
    for (int i = 0; i < k; i++) {
        std::pop_heap(nums.begin(), nums.end(), std::greater<int>());
        nums.back() *= 2;
        std::push_heap(nums.begin(), nums.end(), std::greater<int>());
    }

    std::pop_heap(nums.begin(), nums.end(), std::greater<int>());
    return nums.back();
}

class PrinterQueue
{
    // your attributes
    map<int, queue<string>, std::greater<int>> printingQueue;
public:
    // your methods

    void addNewRequest(int priority, string fileName)
    {
        // your code here
        this->printingQueue[priority].push(fileName);
    }

    void print()
    {
        // your code here
        // After some logic code, you have to print fileName with endline

        // get highest priority available
        map<int, queue<string>, std::greater<int>>::iterator it = printingQueue.begin();
        while(it != this->printingQueue.end() && it->second.empty()) {
            ++it;
        }
        
        // print
        if (it == this->printingQueue.end()) {
            std::cout << "No file to print" << endl;
        }
        else {
            std::cout << it->second.front() << endl;
            it->second.pop();

        }
    }
};

#endif