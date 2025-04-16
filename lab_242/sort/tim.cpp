#ifndef SORTING_H
#define SORTING_H
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;
template <class T>
class Sorting {
private:
    static void printArray(T* start, T* end)
    {
        int  size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << " ";
        cout << start[size - 1];
        cout << endl;
    }

    static void merge(T* start, T* middle, T* end)
    {
        // TODO
        int n1 = middle - start;    //? exclusive left
        int n2 = end - middle + 1;  //? inclusise right

        // temporary arrays to hold the subarrays
        T* leftArr = new T[n1];
        T* rightArr = new T[n2];
        for (int i = 0; i < n1; i++) {
            leftArr[i] = start[i];
        }
        for (int i = 0; i < n2; i++) {
            rightArr[i] = middle[i];
        }

        // merge the temporary arrays back into the original array
        int i = 0;    // index of first subarray
        int j = 0;    // index of second subarray
        int k = 0;    // index of merged array
        while (i < n1 && j < n2) {
            if (leftArr[i] <= rightArr[j]) {
                start[k] = leftArr[i];
                i++;
            }
            else {
                start[k] = rightArr[j];
                j++;
            }
            k++;
        }
        while (i < n1) {
            start[k] = leftArr[i];
            i++;
            k++;
        }
        while (j < n2) {
            start[k] = rightArr[j];
            j++;
            k++;
        }

        // clean temporary arrays
        delete[] leftArr;
        delete[] rightArr;
    }
public:
    static void InsertionSort(T* start, T* end)
    {
        // TODO
        int size = end - start + 1;     //? inclusive
        for (int i = 1; i < size; i++) {
            int j = i;
            while (j > 0 && start[j - 1] > start[j]) {
                swap(start[j - 1], start[j]);
                j--;
            }
        }
    }
    static void TimSort(T* start, T* end, int min_size)
    {
        // TODO
        // You must print out the array after using insertion sort and everytime calling method merge.
        int size = end - start;

        // sort each partition
        // int i = min_size;
        // while(true) {
        //     if (i + min_size >= size) {
        //         // last partition
        //         InsertionSort(&start[i], &start[size]);
        //         break;
        //     }
        //     InsertionSort(&start[i - min_size], &start[i - 1]);
        //     i += min_size;
        // }
        for (int i = min_size; i <= size; i += min_size) {
            InsertionSort(&start[i - min_size], &start[i - 1]);
        }
        cout << "Insertion Sort: "; printArray(start, end);
        
        // merge partitions
        int count = 1;
        for (int width = min_size; width < size; width = width*2) {
            for (int i = 0; i < size; i += 2*width) {
                int mid = min(i + width, size - 1);
                int right = min(i + 2*width - 1, size - 1);

                if (i + width < size) {
                    merge(&start[i], &start[mid], &start[right]);
                }
                cout << "Merge " << count++ << ": "; printArray(start, end);
            }
        }
    }
};
#endif /* SORTING_H */