#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

long long comps = 0, swapsCount = 0;

// 1. Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            comps++;
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
            swapsCount++;
        }
    }
}

// 2. Bubble Sort (with early exit optimization)
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comps++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapsCount++;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// 3. Quick Sort (Middle Pivot)
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[(low + high) / 2];
    int i = low, j = high;
    while (i <= j) {
        while (arr[i] < pivot) { comps++; i++; }
        while (arr[j] > pivot) { comps++; j--; }
        if (i <= j) {
            swap(arr[i], arr[j]);
            swapsCount++;
            i++; j--;
        }
    }
    return i;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int idx = partition(arr, low, high);
        quickSort(arr, low, idx - 1);
        quickSort(arr, idx, high);
    }
}

// 4. Merge Sort
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> L(arr.begin() + l, arr.begin() + m + 1);
    vector<int> R(arr.begin() + m + 1, arr.begin() + r + 1);
    int i = 0, j = 0, k = l;
    while (i < L.size() && j < R.size()) {
        comps++;
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
        swapsCount++;
    }
    while (i < L.size()) { arr[k++] = L[i++]; swapsCount++; }
    while (j < R.size()) { arr[k++] = R[j++]; swapsCount++; }
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main() {
    vector<int> sizes = {5, 100};
    for (int n : sizes) {
        vector<int> sortedArr(n), revArr(n);
        for (int i = 0; i < n; i++) {
            sortedArr[i] = i + 1;
            revArr[i] = n - i;
        }
        // Example run for Bubble Sort on Reverse Sorted array
        comps = 0; swapsCount = 0;
        vector<int> temp = revArr;
        auto start = high_resolution_clock::now();
        bubbleSort(temp);
        auto end = high_resolution_clock::now();
        double time_us = duration<double, micro>(end - start).count();
        cout << "N=" << n << " | Time: " << time_us << " us | Comps: " << comps << " | Swaps: " << swapsCount << endl;
    }
    return 0;
}
