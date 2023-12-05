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
