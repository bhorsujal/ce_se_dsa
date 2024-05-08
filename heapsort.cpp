// Author: Sujal Bhor (21210)

#include <iostream>
#include <vector>

using namespace std;


void maxHeapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2*i + 1; // Left child
    int right = 2*i + 2; // Right child

    if (left < n && arr[left] > arr[largest])
        largest = left;

 
    if (right < n && arr[right] > arr[largest])
        largest = right;

  
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        maxHeapify(arr, n, largest);
    }
}

void minHeapify(vector<int>& arr, int n, int i) {
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;

 
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

  
    if (smallest != i) {
        swap(arr[i], arr[smallest]);

        // Recursively heapify the affected sub-tree
        minHeapify(arr, n, smallest);
    }
}

void heapSortAscending(vector<int>& arr) {
    int n = arr.size();

    // Build Max Heap
    for (int i = (n/2)-1; i >= 0; i--)
        maxHeapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
     
        swap(arr[0], arr[i]);

        maxHeapify(arr, i, 0);
    }
}

void heapSortDescending(vector<int>& arr) {
    int n = arr.size();

    // Build Min Heap
    for (int i = (n/2)-1; i >= 0; i--)
        minHeapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
     
        swap(arr[0], arr[i]);

        minHeapify(arr, i, 0);
    }
}

void printArray(const vector<int>& arr) {
    for (int i : arr)
        cout << i << " ";
    cout << endl;
}


int main() {
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    cout << "Original array: ";
    printArray(arr);

    heapSortDescending(arr);

    cout << "Sorted array: ";
    printArray(arr);
    return 0;
}
