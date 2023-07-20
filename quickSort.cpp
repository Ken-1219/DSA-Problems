#include "bits/stdc++.h"
using namespace std;

void printVector(vector<int>& arr)
{
   for (int i = 0; i < arr.size(); ++i)
   {
      cout << arr[i] << " ";
   }
   cout << endl;
}

int getPivotPosition(vector<int>& arr, int start, int end)
{
   int pivot = arr[start];

   int low = start, high = end;

   while (low < high)
   {
      while (arr[low] <= pivot && low <= end - 1)
      {
         low++;
      }
      while (arr[high] > pivot && high >= start + 1)
      {
         high--;
      }
      if (low <= high)
      {
         swap(arr[low], arr[high]);
      }
   }
   swap(arr[start], arr[high]);
   return high;
}


void quickSort(vector<int>& arr, int start, int end)
{
   if (start >= end)
      return;

   int partitionIndex = getPivotPosition(arr, start, end);
   quickSort(arr, start, partitionIndex - 1);
   quickSort(arr, partitionIndex + 1, end);
}

int main()
{
   int         n; cin >> n;
   vector<int> arr;

   for (int i = 0; i < n; ++i)
   {
      int x; cin >> x;
      arr.push_back(x);
   }

   quickSort(arr, 0, n - 1);
   printVector(arr);
}