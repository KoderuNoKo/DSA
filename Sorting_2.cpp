#ifndef SORTING_H
#define SORTING_H
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;
template <class T>
class Sorting {
private:
    static void Swap(T* i, T* j)
    {
        T temp = *i;
        *i = *j;
        *j = temp;
    }

    static T* Partition(T* start, T* end) {
        // TODO: return the pointer which points to the pivot after rearrange the array.
        T* pivot = start;
        T* left = start;
        T* right = end;
        while (left != right)
        {
            while (*(++left) < *(pivot));
            while (*(right++) < *(pivot));
            Swap(left, right);
        }
        return pivot;
    }

public:
    static void QuickSort(T* start, T* end) {
        // TODO
        // In this question, you must print out the index of pivot in subarray after everytime calling method Partition.
        if (end - start <= 0) return;
        T* pivot = Partition(start, end);
        cout << *pivot << " ";
        QuickSort(start, pivot - 1);
        QuickSort(pivot + 1, end);
    }
};
#endif /* SORTING_H */