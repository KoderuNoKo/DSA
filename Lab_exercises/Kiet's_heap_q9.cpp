
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

//Helping functions go here
static int parent(const int& idx) { return (idx - 1) / 2; }

static void reheapUp(T* arr, int idx)
{
    int parentidx = parent(idx);
    while (parentidx > 0) 
    {
        if (arr[parentidx] > arr[idx]) {
            swap(arr[parentidx], arr[idx]);
        }
        idx = parentidx;
        parentidx = parent(parentidx);
    }
    if (arr[parentidx] > arr[idx]) {
        swap(arr[parentidx], arr[idx]);
    }
}

static void reheapDown(T* arr, int idx,const int& size)
{
    if (2 * idx + 1 >= size) {
        return;
    }
    
    int childidx = 0;
    if (2 * idx + 2 >= size) {
        childidx = 2 * idx + 1;
    }
    else {
        childidx = 2 * idx + ( (arr[2 * idx + 1] < arr[2 * idx + 2]) ? 1 : 2 );
    }
    
    if (arr[idx] > arr[childidx]) {
        swap(arr[idx], arr[childidx]);
    }
    reheapDown(arr, childidx, size);
}

static void heapSort(T* start, T* end) {
    //TODO
    int size = end - start;
    if (size <= 1) {
        return;
    }
    
    // build the heap
    for (int i = size - 1; i >= 0; i--) {
        reheapUp(start, i);
    }
    // sort
    for (int i = 1; i < size; i++) {
        reheapDown(start + i, 0, size - i);
    }
    Sorting<T>::printArray(start,end);
}
