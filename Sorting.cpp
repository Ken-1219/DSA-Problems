#include "bits/stdc++.h"
using namespace std;

void printArray(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		cout << arr[i] << "  ";
	}
	cout << endl;
}


//Bubble sort is a sorting algorithm that compares two adjacent elements and swaps them until they are in the intended order.

//Algorithm :
/*

--traverse from left and compare adjacent elements and the higher one is placed at right side.
--In this way, the largest element is moved to the rightmost end at first.
--This process is then continued to find the second largest and place it and so on until the data is sorted.

*/


void bubbleSort(int arr[], int n) {
	bool swapped;
	for (int i = 0; i < n; i++) {
		swapped = false;
		for (int j = 0; j < n; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
				swapped = true;
			}
		}
		if (swapped == false) {
			break;
		}
		printArray(arr, n);
	}
}

// Selection sort is a simple and efficient sorting algorithm that works by repeatedly selecting the smallest (or largest) element from the unsorted portion of the list and moving it to the sorted portion of the list.

//Algorithm :
/*

The algorithm repeatedly selects the smallest (or largest) element from the unsorted portion of the list and swaps it with the first element of the unsorted part. This process is repeated for the remaining unsorted portion until the entire list is sorted.


*/


void selectionSort(int arr[], int n) {
	int min_idx;
	for (int i = 0; i < n - 1; ++i) {
		min_idx = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[min_idx]) {
				swap(arr[j], arr[min_idx]);
			}
		}
		printArray(arr, n);
		cout << endl << endl << endl << endl << endl;
	}
}


// Insertion sort is a simple sorting algorithm that works similar to the way you sort playing cards in your hands. The array is virtually split into a sorted and an unsorted part. Values from the unsorted part are picked and placed at the correct position in the sorted part.

//Algorithm :
/*

To sort an array of size N in ascending order iterate over the array and compare the current element (key) to its predecessor, if the key element is smaller than its predecessor, compare it to the elements before. Move the greater elements one position up to make space for the swapped element.


*/

// void insertionSort(int arr[], int n){
// 	for(int i=0; i<n; i++)	{
// 		int j = i+1;  //checking next element
// 		int ele_idx;  //storing the index of the smaller element encountered
// 		if(arr[j]<arr[i]){
// 			ele_idx = j;
// 		}
// 		//keep swapping smaller element until it is bigger than its previous element
// 		while(arr[ele_idx]<arr[ele_idx-1]){
// 			swap(arr[ele_idx],arr[ele_idx-1]);
// 			ele_idx--;
// 		}

// 		cout<<"New array : "<<endl;
// 		printArray(arr,n);
// 	}

// }


void insertionSort(int arr[], int n) {
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}


// Merge sort is defined as a sorting algorithm that works by dividing an array into smaller subarrays, sorting each subarray, and then merging the sorted subarrays back together to form the final sorted array.
/*
	Time Complexity: O(NLogN)
	Space Complexity : O(1)
*/

//Merge Sort Using Recursion

void  mergeTwoSortedArrays(int *arr, int start, int end) {
	int mid = start + (end - start) / 2;

	// int len1 = (mid - start + 1); //length of one array
	// int len2 = (end-mid); //length of second array


	// //Declaring new arrays
	// int *first = new int[len1];
	// int *second = new int[len2];

	// //Copying Values to the new arrays that will be sorted later
	// //Copying to array 1
	// int mainArrayIndex = start;
	// for(int i=0; i<len1; i++){
	//     first[i] = arr[mainArrayIndex++];
	// }

	// //Copying to array2
	// mainArrayIndex = mid+1;
	// for(int i=0; i<len2; i++){
	//     second[i] = arr[mainArrayIndex++];
	// }


	// //finally merge the new arrays
	// int index1 = 0; //starting index of array1
	// int index2 = 0; //starting index of array2
	// mainArrayIndex = start;

	// while(index1<len1 && index2<len2){
	//     if(first[index1]<second[index2]){
	//         arr[mainArrayIndex++] = first[index1++];
	//     }
	//     else{
	//         arr[mainArrayIndex++] = second[index2++];
	//     }
	// }

	// while (index1 < len1){
	//     arr[mainArrayIndex++] = first[index1++];
	// }

	// while(index2 < len2){
	//     arr[mainArrayIndex++] = second[index2++];
	// }

	// delete []first;
	// delete []second;

	/*----------------------------------------------------------------*/
	//Second Approach:  (Better)
	vector<int> temp;
	int left = start;
	int right = mid + 1;

	while (left <= mid && right <= end) {
		if (arr[left] <= arr[right]) {
			temp.push_back(arr[left++]);
		}
		else {
			temp.push_back(arr[right++]);
		}
	}

	while (left <= mid) {
		temp.push_back(arr[left++]);
	}

	while (right <= end) {
		temp.push_back(arr[right++]);
	}

	for (int i = start; i <= end; i++) {
		arr[i] = temp[i - start];
	}
}




void mergeSort(int *arr, int start, int end) {
	//Base Case
	if (start >= end) {
		return;
	}

	int mid = start + (end - start) / 2;
	//sort left array
	mergeSort(arr, start, mid);

	//sort right array;
	mergeSort(arr, mid + 1, end);

	//Merge Two Sorted Arrays
	mergeTwoSortedArrays(arr, start, end);
}



//Quick Sort ---> Divide and Conquer Algorithm
/* 
	Time Complexity: O(NLogN)
	Space Complexity : O(1)
*/



int pivotIndex(int* arr, int low, int high)
{
    int pivot = arr[low];

    int i = low, j = high;

    while (i < j)
    {
        while (arr[i] <= pivot && i <= high - 1)
        {
            i++;
        }

        while (arr[j] > pivot && j >= low + 1)
        {
            j--;
        }
        if (i <= j)
        {
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[j], arr[low]);
    return j;
}



void quickSort(int* arr, int low, int high)
{
    if (low >= high)
        return;

    //selecting and putting the pivot at its correct place and returning its position
    int partitionIndex = pivotIndex(arr, low, high);

    //solving left part
    quickSort(arr, low, partitionIndex - 1);
    //solving right part
    quickSort(arr, partitionIndex + 1, high);
}



int main() {
	int n; cin >> n;
	int arr[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	quickSort(arr, 0, n - 1);

	printArray(arr, n);

}