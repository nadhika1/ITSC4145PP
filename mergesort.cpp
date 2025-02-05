#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cstdlib>

using namespace std;

// Merge two sorted subarrays: arr[left..mid] and arr[mid+1..right]
void merge(vector<int>& arr, int left, int mid, int right) {
    int sizeLeft = mid - left + 1;
    int sizeRight = right - mid;

    // Create temporary arrays
    vector<int> leftArr(sizeLeft);
    vector<int> rightArr(sizeRight);

    // Copy data to temporary arrays
    for (int i = 0; i < sizeLeft; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < sizeRight; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    // Merge the temporary arrays back into arr[left..right]
    int i = 0; // index for leftArr
    int j = 0; // index for rightArr
    int k = left; // index for merged array

    while (i < sizeLeft && j < sizeRight) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    // Copy any remaining elements of leftArr, if there are any
    while (i < sizeLeft) {
        arr[k++] = leftArr[i++];
    }

    // Copy any remaining elements of rightArr, if there are any
    while (j < sizeRight) {
        arr[k++] = rightArr[j++];
    }
}

// Recursive merge sort: sorts the subarray arr[left..right]
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Helper function to print the contents of a vector
void printVector(const vector<int>& vec) {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    // Check for command-line argument for array size
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <array_size>" << endl;
        return 1;
    }

    // Convert the first argument to an integer for the array size
    int n = atoi(argv[1]);
    if (n <= 0) {
        cerr << "Error: array size must be a positive integer." << endl;
        return 1;
    }

    // Generate an array of 'n' random integers
    vector<int> data(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1000000); // numbers between 0 and 1,000,000

    for (int i = 0; i < n; ++i) {
        data[i] = dis(gen);
    }

    // Print the unsorted array
    cout << "Unsorted numbers:" << endl;
    printVector(data);

    // Record the start time
    auto startTime = chrono::high_resolution_clock::now();

    // Perform merge sort on the array
    mergeSort(data, 0, n - 1);

    // Record the end time
    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endTime - startTime;

    // Print the sorted array
    cout << "Sorted numbers:" << endl;
    printVector(data);

    // Print the elapsed time to sort the array
    cout << "Time taken to sort " << n << " elements: " 
         << elapsed.count() << " seconds" << endl;

    return 0;
}
