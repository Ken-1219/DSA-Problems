#include "bits/stdc++.h"
using namespace std;

void printVector(vector<int>& arr) {
	for (int i = 0; i < arr.size(); ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void mergeArrays(vector<int>& arr, int start, int mid, int end) {
	vector<int> temp;

	int low = start;
	int high = mid + 1;

	while (low <= mid && high <= end) {
		if (arr[low] <= arr[high]) {
			temp.push_back(arr[low++]);
		}
		else {
			temp.push_back(arr[high++]);
		}
	}

	while (low <= mid) {
		temp.push_back(arr[low++]);
	}

	while (high <= end) {
		temp.push_back(arr[high++]);
	}

	for (int i = start; i <= end; i++) {
		arr[i] = temp[i - start];
	}
}



void mergeSort(vector<int>& arr, int start, int end) {
	if (start >= end) {
		return;
	}

	int mid = start + (end - start) / 2;

	mergeSort(arr, start, mid);
	mergeSort(arr, mid + 1, end);
	mergeArrays(arr, start, mid, end);
}


int main() {
	int n; cin >> n;
	vector<int> arr;
	for (int i = 0; i < n; ++i) {
		int x; cin >> x;
		arr.push_back(x);
	}

	mergeSort(arr, 0, n - 1);
	printVector(arr);
}