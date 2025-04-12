#ifndef SORTING_H
#define SORTING_H
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;
template <class T>
class Sorting {
private:
    static T* Partition(T* start, T* end)
    {
        // TODO: return the pointer which points to the pivot after rearrange the array.
        T pivot = *start;
        int low = 0;
        int high = end - start - 1;

        while (true) {
            // find greater on the left
            while (low <= high && start[low] <= pivot) {
                low++;
            }

            // find smaller on the right
            while (high >= low && start[high] > pivot) {
                high--;
            }

            // ptr crossed, partition finished
            if (low >= high) {
                // place pivot
                swap(start[0], start[high]);
                return start + high;
            }

            swap(start[low], start[high]);
        }
    }
public:
    static void QuickSort(T* start, T* end) {
        // TODO
        // In this question, you must print out the index of pivot in subarray after everytime calling method Partition.
        if (end - start <= 0) {
            return;
        }
        
        T* pivot = Partition(start, end);
        cout << pivot - start << " ";
        
        QuickSort(start, pivot);    // end is exclusive
        QuickSort(pivot + 1, end);
    }
};
#endif /* SORTING_H */

