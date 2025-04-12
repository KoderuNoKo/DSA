#ifndef SORTING_H
#define SORTING_H
#include <iostream>
using namespace std;
template <class T>
class Sorting {
public:
    /* Function to print an array */
    static void printArray(T* start, T* end)
    {
        long size = end - start + 1;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    static void Merge(T* left, T* middle, T* right) {
        int n1 = middle - left;
        int n2 = right - middle + 1;

        // temporary arrays to hold the subarrays
        T* leftArr = new T[n1];
        T* rightArr = new T[n2];
        for (int i = 0; i < n1; i++) {
            leftArr[i] = left[i];
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
                left[k] = leftArr[i];
                i++;
            }
            else {
                left[k] = rightArr[j];
                j++;
            }
            k++;
        }
        while (i < n1) {
            left[k] = leftArr[i];
            i++;
            k++;
        }
        while (j < n2) {
            left[k] = rightArr[j];
            j++;
            k++;
        }

        // clean temporary arrays
        delete[] leftArr;
        delete[] rightArr;

        // print process
        Sorting<T>::printArray(left, right);
    }
    static void mergeSort(T* start, T* end) {
        /*TODO*/
        if (end - start < 1) {
            return;
        }
        T* middle = start + (end - start) / 2;
        mergeSort(start, middle);
        mergeSort(middle + 1, end);
        Merge(start, middle + 1, end);
    }
};
#endif /* SORTING_H */

int main()
{
    int arr[] = { 0,2,4,3,1,4 };
    Sorting<int>::mergeSort(&arr[0], &arr[5]);
}