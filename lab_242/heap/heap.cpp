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
    int getItem(T item);
    void remove(T item);
    void clear();
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
bool Heap<T>::isEmpty() {
    return (this->count == 0);
}

template<class T>
T Heap<T>::peek(){
    if (this->isEmpty()) {
        return -1;
    }
    return this->elements[0];
}

template<class T>
bool Heap<T>::contains(T item){
    for (int i = 0; i < this->count; i++) {
        if (this->elements[i] == item) {
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
    this->elements[0] = this->elements[this->count - 1];
    this->count--;
    this->reheapDown(0);
    return true;
}

template<class T>
void Heap<T>::push(T item){
    // append item to list
    this->ensureCapacity(this->count + 1);
    this->elements[this->count++] = item;

    // maintain heap property
    this->reheapUp(this->count - 1);
}

template<class T>
void Heap<T>::ensureCapacity(int minCapacity){
    if (minCapacity <= this->capacity) {
        return;
    }
    T* temp = this->elements;
    this->capacity *= 2;
    this->elements = new T[this->capacity];
    for (int i = 0; i < this->count; i++) {
        this->elements[i] = temp[i];
    }
    delete temp;
}

template<class T>
void Heap<T>::reheapUp(int position){
    int parent = (position - 1)/2;
    while (position > 0 && this->elements[parent] < elements[position]) {
        std::swap(this->elements[parent], this->elements[position]);
        position = parent;
        parent = (position - 1)/2;
    }
}

void reheapDown(int maxHeap[], int numberOfElements, int index)
{
    int minIndex = index;
    int leftChild = index*2 + 1;
    int rightChild = index*2 + 2;
    
    if (leftChild < numberOfElements && maxHeap[minIndex] < maxHeap[leftChild]) {
        minIndex = leftChild;
    }
    if (rightChild < numberOfElements && maxHeap[minIndex] < maxHeap[rightChild]) {
        minIndex = rightChild;
    }
    
    if (minIndex != index) {
        swap(maxHeap[minIndex], maxHeap[index]);
        reheapDown(maxHeap, numberOfElements, minIndex);
    }
}

void reheapUp(int maxHeap[], int numberOfElements, int index)
{
    int parent = (index - 1)/2;
    while (index > 0 && maxHeap[parent] < maxHeap[index]) {
        swap(maxHeap[parent], maxHeap[index]);
        index = parent;
        parent = (parent - 1)/2;
    }
}

template<class T>
int Heap<T>::getItem(T item) {
    // TODO: return the index of item in heap
    for (int i = 0; i < this->count; i++) {
        if (this->elements[i] == item) {
            return i;
        }
    }
    return -1;
}

template<class T>
void Heap<T>::remove(T item) {
    // TODO: remove the element with value equal to item
    
    int idx = this->getItem(item);
    if (idx < 0) {
        return;
    }
    
    this->elements[idx] = this->elements[--this->count];
    
    if (idx < this->count) {
        int parentIndex = (idx - 1) / 2;
        if (idx > 0 && this->elements[idx] > this->elements[parentIndex]) {
            reheapUp(idx);
        } else {
            reheapDown(idx);
        }
    }   
}

template<class T>
void Heap<T>::clear() {
    // TODO: delete all elements in heap
    delete[] this->elements;
    //    then reallocate memory as initial state
    this->capacity = 10;
    this->count = 0;
    this->elements = new T[capacity];
}