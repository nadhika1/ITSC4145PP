#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cstdlib>
#include <iomanip>
#include <sstream>  // For std::stoll

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

    // Copy any remaining elements of leftArr
    while (i < sizeLeft) {
        arr[k++] = leftArr[i++];
    }

    // Copy any remaining elements of rightArr
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

    // Convert the first argument to a 64-bit integer for the array size
    long long n;
    try {
        n = stoll(argv[1]);
    } catch (...) {
        cerr << "Invalid array size: please provide a numeric value." << endl;
        return 1;
    }

    // Ensure the array size is between 1 and 1,000,000,000
    if (n <= 0 || n > 1000000000LL) {
        cerr << "Error: array size must be a positive integer up to 1000000000." << endl;
        return 1;
    }

    // Allocate the vector. Note: static_cast<size_t>(n) is used because vector size is size_t.
    vector<int> data(static_cast<size_t>(n));

    // Generate an array of 'n' random integers
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1000000); // numbers between 0 and 1,000,000

    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = dis(gen);
    }

    // (Optional) Print the unsorted array if n is small (uncomment if desired)
    // cout << "Unsorted numbers:" << endl;
    // printVector(data);

    // Record the start time
    auto startTime = chrono::high_resolution_clock::now();

    // Perform merge sort on the array
    mergeSort(data, 0, static_cast<int>(data.size()) - 1);

    // Record the end time and compute elapsed time in milliseconds
    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> elapsed = endTime - startTime;

    // (Optional) Print the sorted array if n is small (uncomment if desired)
    // cout << "Sorted numbers:" << endl;
    // printVector(data);

    // Print the elapsed time in milliseconds, rounded to two decimals
    cout << fixed << setprecision(2);
    cout << "Time taken to sort " << n << " elements: " 
         << elapsed.count() << " ms" << endl;

    return 0;
}
