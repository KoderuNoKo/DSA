
//Helping functions go here
 static void heapify(T *arr, int n, int i)
{
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // left = 2*i + 1
    int right = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

    // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

static void heapSort(T* start, T* end){
    //TODO
    int n = end - start;

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(start, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(start[0], start[i]);

        // Call max heapify on the reduced heap
        heapify(start, i, 0);
    }
    //print
    Sorting<T>::printArray(start,end);
}
