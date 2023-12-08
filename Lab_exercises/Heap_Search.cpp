int binarySearch(int arr[], int left, int right, int x)
{
    if(left > right) {
        return -1;
    }
    
    int mid = (right + left) / 2;
    
    cout << "We traverse on index: " << mid << endl;
    
    if (x > arr[mid]) {
        return binarySearch(arr, mid + 1, right, x);
    }
    if (x < arr[mid]) {
        return binarySearch(arr, left, mid - 1, x);
    }
    return mid;
}

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template<class T>
class Heap {
protected:
    T* elements;
    int capacity;
    int count;
public:
    Heap()
    {
        this->capacity = 10;
        this->count = 0;
        this->elements = new T[capacity];
    }
    ~Heap()
    {
        delete[]elements;
    }
    void push(T item);
    
    bool isEmpty();
    bool contains(T item);
    T peek();
    bool pop();
    int size();
    
    void printHeap()
    {
        cout << "Max Heap [ ";
        for (int i = 0; i < count; i++)
            cout << elements[i] << " ";
        cout << "]\n";
    }
private:
    void ensureCapacity(int minCapacity);
    void reheapUp(int position);
    void reheapDown(int position);
};

template<class T>
int Heap<T>::size(){
    return count;
}

template<class T>
bool Heap<T>::isEmpty(){
    return (count == 0);
}

template<class T>
T Heap<T>::peek(){
    return elements[0];
}

template<class T>
bool Heap<T>::contains(T item){
    for (int i = 0; i < count; i++) {
        if (elements[i] == item) {
            return true;
        }
    }
    return false;
}

template<class T>
bool Heap<T>::pop(){
    if (this->isEmpty()) {
        return false;
    }
    elements[0] = elements[--count];
    reheapDown(0);
    return true;
}

template<class T>
void Heap<T>::push(T item){
    ensureCapacity(count + 1);
    elements[count] = item;
    reheapUp(count++);
}

template<class T>
void Heap<T>::ensureCapacity(int minCapacity)
{
    if (capacity < minCapacity) {
        capacity *= 2;
        
        T* newElements = new T[capacity];
        for (int i = 0; i < count; i++) {
            newElements[i] = elements[i];
        }
        
        delete[] elements;
        elements = newElements;
    }
}

int parent(int pos) { return (pos - 1) / 2; }

template<class T>
void Heap<T>::reheapUp(int position)
{
    int parentIdx = parent(position);
    
    while (parentIdx > 0) {
        if (elements[parentIdx] < elements[position]) {
            swap(elements[position], elements[parentIdx]);
        }
        position = parentIdx;
        parentIdx = parent(parentIdx);
    }
            if (elements[parentIdx] < elements[position]) {
            swap(elements[position], elements[parentIdx]);
        }
}

int interpolationSearch(int arr[], int left, int right, int x)
{
    if (x < arr[left] || x > arr[right]) {
        return -1;
    }
    
    if (left == right) {
        if (arr[right] == x) {
            return left;
        }
        return -1;
    }
    
    int pos = left + (double)((x - arr[left]) * (right - left) / (arr[right] - arr[left]));
    
    if (pos < 0) {
        return -1;
    }
    
    cout << "We traverse on index: " << pos << endl;    
    
    if (x > arr[pos]) {
        return interpolationSearch(arr, pos + 1, right, x);
    }
    if (x < arr[pos]) {
        return interpolationSearch(arr, left, pos - 1, x);
    }
    return pos;
}

void reheapDown(int maxHeap[], int numberOfElements, int idx)
{
    if (2 * idx + 1 >= numberOfElements) {
        return;
    }
    
    int child = 2 * idx + 1;
    
    if (child + 1 < numberOfElements) {
        child += (maxHeap[child] < maxHeap[child + 1]);
    }
    
    if (maxHeap[child] > maxHeap[idx]) {
        swap(maxHeap[child], maxHeap[idx]);
        reheapDown(maxHeap, numberOfElements, child);
    }
}

void reheapUp(int maxHeap[], int numberOfElements, int index)
{
    int parentIdx = (index - 1) / 2;
    while (parentIdx > 0) 
    {
        if (maxHeap[index] > maxHeap[parentIdx]) {
            swap(maxHeap[index], maxHeap[parentIdx]);
        }
        index = parentIdx;
        parentIdx = (parentIdx - 1) / 2;
    }
        if (maxHeap[index] > maxHeap[parentIdx]) {
            swap(maxHeap[index], maxHeap[parentIdx]);
        }
}

int jumpSearch(int arr[], int x, int n) 
{
    // TODO: print the traversed indexes and return the index of value x in array if x is found, 
    // otherwise, return -1.
    int jump = sqrt(n);
    int i = 0;
    for (; jump * i < n; i++)
    {
        cout << jump * i << " ";
        if (arr[jump * i] == x) {
            return jump * i;
        }
        if (arr[jump * i] > x) {
            break;
        }
    }
    
    if (i * jump >= n) 
    {
        int j = 0;
        for (j = (i - 1) * jump + 1; j < n; j++) 
        {
            cout << j << " ";
            if (arr[j] == x) {
                return j;
            }
        }
        cout << j;
        return -1;
    }
    
    int j = 0;
    for (j = (i - 1) * jump + 1; j > 0 && j < i * jump; j++) {
        cout << j << " ";
        if (arr[j] == x) {
            return j;
        }
    }
    return -1;
}

bool findPairs(int arr[], int n, pair<int,int>& pair1, pair<int, int>& pair2)
{
   // TODO: If there are two pairs satisfy the condition, assign their values to pair1, pair2 and return true.
   // Otherwise, return false.
   map<int, pair<int, int>> sumMap;
   for (int i = 0; i < n; i++) 
   {
       for (int j = i + 1; j < n; j++) 
       {
           int sum = arr[i] + arr[j];
           
           if (sumMap.find(sum) != sumMap.end()) { 
               // sum found! now check element
               pair<int, int> prevPair = sumMap[sum];
               if (prevPair.first != i && prevPair.first != j
               && prevPair.second != i && prevPair.second != j)
               {
                   // element valid, return
                   pair1 = make_pair(arr[i] , arr[j]);
                   pair2 = make_pair(arr[prevPair.first], arr[prevPair.second]);
                   return true;
               }
           }
           
           else { // new sum, add it to the map
               sumMap[sum] = make_pair(i, j);
           }
       }
   }
   return false;
}

template<class T>
int Heap<T>::getItem(T item) {
    // TODO: return the index of item in heap
    for (int i = 0; i < count; i++) {
        if (elements[i] == item) {
            return i;
        }
    }
    return -1;
}

template<class T>
void Heap<T>::remove(T item) {
    // TODO: remove the element with value equal to item
    int target = getItem(item);
    if (target < 0) {
        return;
    }
    elements[target] = elements[--count];
    reheapUp(target);
    reheapDown(target);
}

template<class T>
void Heap<T>::clear() {
    // TODO: delete all elements in heap
    //    then reallocate memory as initial state
    delete[] elements;
    elements = new T[capacity];
    count = 0;
}

//Helping functions go here
static void reheapDown(T* arr, int idx, int n)
{
    if (2 * idx + 1 >= n) {
        return;
    }
    
    int child = 2 * idx + 1;
    if (child + 1 < n) {
        child += (arr[child] < arr[child + 1]);
    }
    
    if (arr[child] > arr[idx]) {
        swap(arr[child], arr[idx]);
        reheapDown(arr, child, n);
    }
}
static void heapSort(T* start, T* end){
    //TODO
    int size = end - start;
    
    // build heap
    for (int i = (size / 2) - 1; i >= 0; i--) {
        reheapDown(start, i, size);
    }
    
    // sort
    for (int i = size - 1; i > 0; i--) {
        swap(start[0], start[i]);   // max elements go to i
        reheapDown(start, 0, i);    // reheap the remainings
    }
    
    Sorting<T>::printArray(start,end);
}

#include <vector>
#include <algorithm>
#include <utility>
class PrinterQueue
{
    // your attributes
    vector<pair<int, string>> printQueue;
public:
    // your methods

    void addNewRequest(int priority, string fileName)
    {
        // your code here
        size_t insi = 0;       // pos to insert
        while (insi < printQueue.size()) {
            if (printQueue[insi].first < priority) {
                break;
            }
            insi++;
        }
        printQueue.insert(printQueue.begin() + insi, make_pair(priority, fileName));
    }

    void print()
    {
        // your code here
        // After some logic code, you have to print fileName with endline 
        if (printQueue.empty()) {
            cout << "No file to print\n";
            return;
        }
        cout << printQueue[0].second << endl;
        printQueue.erase(printQueue.begin());
    }
};

int leastAfter(vector<int>& nums, int k) {
    // STUDENT ANSWER
    
    // create a min heap
    priority_queue<int, vector<int>, greater<int>> heap(nums.begin(), nums.end());
    
    // perform operation k times
    for (int i = 0; i < k; i++)
    {
        int smallest = heap.top();
        heap.pop();
        heap.push(smallest * 2);
    }
    
    return heap.top();
}
