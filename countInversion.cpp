#include "bits/stdc++.h"
using namespace std;


int merge(vector<int>& arr, int low, int mid, int high) {
    int count = 0;
    vector<int> temp;
    int left = low;
    int right = mid + 1;

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left++]);
        }
        else {
            count += mid - left + 1;
            temp.push_back(arr[right++]);
        }
    }

    while (left <= mid) {
        temp.push_back(arr[left++]);
    }

    while (right <= high) {
        temp.push_back(arr[right++]);
    }

    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }

    return count;
}


int mergeSort(vector<int> &arr, int low, int high) {
    int count = 0;
    if (low >= high) return count;

    int mid  = low + (high - low) / 2;
    count += mergeSort(arr, low, mid);
    count += mergeSort(arr, mid + 1, high);

    count += merge(arr, low, mid, high);

    return count;
}


int numberOfInversions(vector<int>&a, int n) {
    return mergeSort(a, 0, n - 1);
}


int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> arr;
        for (int i = 0; i < n; i++) {
            int x;  cin >> x;
            arr.push_back(x);
        }

        cout << numberOfInversions(arr, n) << endl;
    }
}