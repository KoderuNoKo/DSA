int binarySearch(int arr[], int left, int right, int x)
{
    if (left > right) {
        return -1;
    }
    int mid = (left + right) / 2;
    
    cout << "We traverse on index: " << mid << endl;
    if (arr[mid] == x) {
        return mid;
    }
    
    if (x > arr[mid]) {
        return binarySearch(arr, mid + 1, right, x);
    }
    return binarySearch(arr, left, mid - 1, x);
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
    return this->count;
}

template<class T>
bool Heap<T>::isEmpty(){
    return (this->count == 0);
}

template<class T>
T Heap<T>::peek(){
    if (this->isEmpty()) {
        return -1;
    }
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
    this->reheapDown(0);
    return true;
}

template<class T>
void Heap<T>::push(T item)
{
    if (count == capacity) {
        this->ensureCapacity(capacity*2);
    }
    elements[count] = item;
    reheapUp(count);
    count++;
}

template<class T>
void Heap<T>::ensureCapacity(int minCapacity){
    if (minCapacity <= this->capacity) {
        return;
    }
    T* newElements = new T [minCapacity];
    for (int i = 0; i < capacity; i++) {
        newElements[i] = elements[i];
    }
    delete[] elements;
    elements = newElements;
    capacity = minCapacity;
    
}

int parent(const int& pos) { return (pos - 1)/2; }

template<class T>
void Heap<T>::reheapUp(int position){
    int parentIdx = parent(position);
    while (parentIdx >= 0) {
        if (elements[position] <= elements[parentIdx]) {
            break;
        }
        swap(elements[position], elements[parentIdx]);
        position = parentIdx;
        parentIdx = parent(parentIdx);
    }
}

int interpolationSearch(int arr[], int left, int right, int x)
{
    if (x < arr[left] || x > arr[right]) {
        return -1;
    }
    if (left == right) {
        if (arr[left] == x) {
            return right;
        }
        return -1;
    }
    int pos = left + (double)( ((x - arr[left])*(right - left))/(arr[right] - arr[left]) );
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

bool isLeaf(int idx, int max) { return (idx * 2 + 1) >= max; }
int parent(int idx) { return (idx - 1) / 2; }

void reheapDown(int maxHeap[], int numberOfElements, int idx)
{
    if (isLeaf(idx, numberOfElements)) {
        return;
    }
    int childidx = idx * 2 + ((maxHeap[idx * 2 + 1] > maxHeap[idx * 2 + 2]) ? 1 : 2);
    if (maxHeap[idx] < maxHeap[childidx]) {
        int temp = maxHeap[idx];
        maxHeap[idx] = maxHeap[childidx];
        maxHeap[childidx] = temp;
    }
    reheapDown(maxHeap, numberOfElements, childidx);
}

void reheapUp(int maxHeap[], int numberOfElements, int idx) 
{
    int parentIdx = parent(idx);
    while (parentIdx > 0) 
    {
        if (maxHeap[parentIdx] < maxHeap[idx]) {
            int temp = maxHeap[parentIdx];
            maxHeap[parentIdx] = maxHeap[idx];
            maxHeap[idx] = temp;
        }
        idx = parentIdx;
        parentIdx = parent(parentIdx);
    }
    if (maxHeap[parentIdx] < maxHeap[idx]) {
            int temp = maxHeap[parentIdx];
            maxHeap[parentIdx] = maxHeap[idx];
            maxHeap[idx] = temp;
    }
}

int jumpSearch(int arr[], int x, int n) {
    // TODO: print the traversed indexes and return the index of value x in array if x is found, 
    // otherwise, return -1.
    int jump = (int)(sqrt(n));
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
    
    if (i == 0) {
        return -1;
    }
    else if (jump * i >= n) {
        int j = 0;
        for (j = (i - 1) * jump + 1; j < n; j++) {
            cout << j << " ";
            if (arr[j] == x) {
                return j;
            }
        }
        cout << j;
        return -1;
    }
    
    for (int j = (i - 1) * jump + 1; (j < i * jump) && j < n; j++)
    {
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
   map<int, pair<int,int>> sumMap;
   
   for (int i = 0; i < n; i++) {
       for (int j = i + 1; j < n; j++)
       {
           int sum = arr[i] + arr[j];
           
           // check if sum is seen before
           if (sumMap.find(sum) != sumMap.end())
           {
               // sum found, check if distinct;
               pair<int, int> prevPair = sumMap[sum];
               if (prevPair.first != i && prevPair.first != j &&
                   prevPair.second != i && prevPair.second != j)
                   {
                       // distinction affirmitive, return
                       pair1 = make_pair(arr[prevPair.first], arr[prevPair.second]);
                       pair2 = make_pair(arr[i], arr[j]);
                       return true;
                   }
           }
           else {
               sumMap[sum] = make_pair(i, j);
           }
       }
   }
   return false;
}

template<class T>
int Heap<T>::getItem(T item) {
    // TODO: return the index of item in heap
    for (int i = 0; i < this->count; i++) {
        if (elements[i] == item) {
            return i;
        }
    }
    return -1;
}

template<class T>
void Heap<T>::remove(T item) {
    // TODO: remove the element with value equal to item
    int pos = getItem(item);
    if (pos < 0) {
        return;
    } 
    elements[pos] = elements[--count];
    reheapUp(pos);
    reheapDown(pos);
}

template<class T>
void Heap<T>::clear() {
    // TODO: delete all elements in heap
    // then reallocate memory as initial state
    delete[] elements;
    elements = new T[capacity];
    count = 0;
}

//Helping functions go here
static void reheapDown(T* arr, int idx,const int& size)
{
    int largest = idx;
    int left = 2 * idx + 1;
    int right = left + 1;
    
    if (left < size && arr[left] > arr[largest]) {
        largest = left;
    }
    
    if (right < size && arr[right] > arr[largest]) {
        largest = right;
    }
    
    if (largest != idx) {
        swap(arr[largest], arr[idx]);
        reheapDown(arr, largest, size);
    }
}

static void heapSort(T* start, T* end) {
    //TODO
    int size = end - start;
    
    // build heap
    for (int i = (size / 2) - 1; i >= 0; i--) {
        reheapDown(start, i, size);
    }
    
    // sort
    for (int i = size - 1; i > 0; i--) {
        swap(start[i], start[0]);
        reheapDown(start, 0, i);
    }
    
    // print
    Sorting<T>::printArray(start, end);
}

#include <vector>
#include <utility>
#include <algorithm>
class PrinterQueue
{
    // your attributes
    vector<pair<int, string>> printQueue;
public:
    // your methods

    void addNewRequest(int priority, string fileName)
    {
        // your code here
        if (printQueue.empty()) {
            printQueue.push_back(make_pair(priority, fileName));
            return;
        }
        size_t insi = 0; // idx to insert new request
        while (insi < printQueue.size())
        {
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
        cout << printQueue[0].second << "\n";
        printQueue.erase(printQueue.begin());
    }
};

int leastAfter(vector<int>& nums, int k) {
    // Create a min heap from the elements of the array
    priority_queue<int, vector<int>, greater<int>> minHeap(nums.begin(), nums.end());

    // Perform the operation k times
    for (int i = 0; i < k; ++i) {
        int smallest = minHeap.top();
        minHeap.pop();

        // Double the smallest element and push it back
        minHeap.push(smallest * 2);
    }

    // The smallest element after k operations
    return minHeap.top();
}
