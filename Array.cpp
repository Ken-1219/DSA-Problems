#include "bits/stdc++.h"
using namespace std;

void printArray(int arr[], int n)
{
  for (int i = 0; i < n; ++i)
    {
      cout << arr[i] << " ";
    }
  cout << endl;
}


void revArray(int arr[], int n)
{
  int i = 0, j = n - 1;

  while (i < j)
    {
      swap(arr[i], arr[j]);
      i++;
      j--;
    }

  cout << "Reversed Array: " << endl;
  printArray(arr, n);
}


int arrayMax(int arr[], int n)
{
  int max_index = 0;

  for (int i = 1; i < n; ++i)
    {
      if (arr[i] > arr[max_index])
        {
          max_index = i;
        }
    }
  return max_index;
}


int arrayMin(int arr[], int n)
{
  int min_index = 0;

  for (int i = 1; i < n; ++i)
    {
      if (arr[i] < arr[min_index])
        {
          min_index = i;
        }
    }
  return min_index;
}


int sumOfArrayElements(int arr[], int n)
{
  int sum = 0;
  int i = 0;

  while (i < n)
    {
      sum = sum + arr[i];
      i++;
    }
  return sum;
}


int linearSearch(int arr[], int n, int key)
{
  for (int i = 0; i < n; ++i)
    {
      if (arr[i] == key)
        {
          cout << "Key Found at: " << i << endl;
          return i;
        }
    }
  return 0;
}


//XOR method -> only one element is unique, every other element is repeated twice
int findUnique(int *arr, int size)
{
  int unique = 0;

  for (int i = 0; i < size; ++i)
    {
      unique = unique ^ arr[i];
    }
  return unique;
}


// find Duplicates in an array -> only one element is repeated twice
// value of array element lies between [1,N-1]
int findDuplicate(vector<int>& arr)
{
  int dup = 0;

  //taking XOR to make the duplicate element 0
  for (int i = 0; i < arr.size(); ++i)
    {
      dup = dup ^ arr[i];
    }
//Taking XOR from 1 to N-1 with the dup so that all other will give a^a=0 while since XOR of that duplicate element will happen thrice this time, we will ge x^x^x = x i.e the duplicate element itself
  for (int i = 1; i < arr.size(); ++i)
    {
      dup = dup ^ i;
    }
  return dup;
}


//Swap Alternate elements in an array/vector
void swapAlternate(vector<int>& arr)
{
  for (auto it = arr.begin(); it != arr.end(); it = it + 2)
    {
      //checking if the current element is the last element in the array
      // if last, we break out of the loop
      if (it == arr.end() - 1)
        {
          break;
        }
      //else swap elements
      else
        {
          swap(*it, *(it + 1));
        }
    }
}


void printVector(vector<int>& arr)
{
  for (auto it = arr.begin(); it != arr.end(); it++)
    {
      cout << *it << " ";
    }
  cout << endl;
}


// Pair Sum -> return a vector containing pairs that sums upto a given number
//Wrong answer
vector<vector<int> > pairSum(vector<int>& arr, int s)
{
  vector<vector<int> > ans;

  sort(arr.begin(), arr.end());
  printVector(arr);
  cout << endl;
  int i = 0, j = arr.size() - 1;
  while (i <= j)
    {
      if (arr[i] + arr[j] < s)
        {
          i++;
        }
      else if (arr[i] + arr[j] > s)
        {
          j--;
        }
      else
        {
          vector<int> temp;
          temp.push_back(min(arr[i], arr[j]));
          temp.push_back(max(arr[i], arr[j]));
          ans.push_back(temp);

          if ((arr[i] + arr[j - 1] < s) && (arr[i + 1] + arr[j] < s))
            {
              i++;
            }
          else
            {
              j--;
            }
        }
    }
  sort(ans.begin(), ans.end());
  return ans;
}


int binarySearch(vector<int> arr, int key)
{
  int low = 0, high = arr.size() - 1; // setting the lower and higher index values

  while (low <= high)
    {
      int mid = low + ((high - low) / 2); //setting the middle value
      if (arr[mid] == key)
        {
          return mid; //if element found, return index
        }
      else if (arr[mid] < key)
        {
          low = mid + 1;
          //since arr[mid] is smaller then the element is in the next portion (ie from mid to high) so we increase low to mid+1
        }
      else
        {
          high = mid - 1;
        }
    }
  return -1;  //if element not found
}


//In a given array(containing duplicates and sorted), you have to find first and last occurence of a given element
/*Sample Input
   2
   6 3
   0 5 5 6 6 6
   8 2
   0 0 1 1 2 2 2 2
   Sample Output
   -1 -1 // Because 3 is not present in the given array
   4 7 // 2 starts from 4th index to 7th index

 */
int firstOccurence(vector<int>& arr, int n, int k)
{
  int first = -1;
  int start = 0, end = n - 1;

  while (start <= end)
    {
      int mid = start + (end - start) / 2;
      if (arr[mid] == k)
        {
          first = mid;
          //Since we are checking first occurence, we have to check in the left subarray
          end = mid - 1;
        }
      else if (arr[mid] < k)
        {
          start = mid + 1;
        }
      else
        {
          end = mid - 1;
        }
    }
  return first;
}

int lastOccurence(vector<int>& arr, int n, int k)
{
  int last = -1;
  int start = 0, end = n - 1;

  while (start <= end)
    {
      int mid = start + (end - start) / 2;
      if (arr[mid] == k)
        {
          last = mid;
          //Since we are checking last occurence, we have to check in the right subarray
          start = mid + 1;
        }
      else if (arr[mid] < k)
        {
          start = mid + 1;
        }
      else
        {
          end = mid - 1;
        }
    }
  return last;
}


pair<int, int> firstAndLastPosition(vector<int>& arr, int n, int k)
{
  int first = firstOccurence(arr, n, k);
  int last = lastOccurence(arr, n, k);

  return make_pair(first, last);
}


//LEETCODE Question -> Peak index in Mountain Array
int peakIndexInMountainArray(vector<int>& arr)
{
  int peakIndex = 0;
  int start = 1, end = arr.size() - 2;

  while (start <= end)
    {
      int mid = start + (end - start) / 2;
      if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1])
        {
          peakIndex = mid;
          return peakIndex;
        }
      else if ((arr[mid] < arr[mid + 1]))
        {
          start = mid + 1;
        }
      else
        {
          end = mid - 1;
        }
    }
  return 0;
}

//Pivot Index - Leetcode Question
int pivotIndex(vector<int>& nums)
{
  int sum = 0, leftSum = 0;

  //Calculate Total Sum
  for (int i = 0; i < nums.size(); ++i)
    {
      sum = sum + nums[i];
    }

  //Now traverse from left and check if leftSum == (sum - nums[i] - leftSum) -> this is rightSum
  for (int i = 0; i < nums.size(); ++i)
    {
      if (leftSum == sum - nums[i] - leftSum)
        {
          return i;
        }
      else
        {
          leftSum += nums[i];
        }
    }

  return -1;
}



int main()
{
  int t;

  cin >> t;
  while (t--)
    {
      int n;
      cin >> n;
      vector<int> arr;
      for (int i = 0; i < n; ++i)
        {
          int x; cin >> x;
          arr.push_back(x);
        }


      cout << peakIndexInMountainArray(arr) << endl;
    }

  return 0;
}
