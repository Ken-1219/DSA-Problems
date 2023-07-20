//Recursion
#include "bits/stdc++.h"
using namespace std;

/*==========================Power of 2 ========================================*/


int powerOf2(int n)
{
  if (n == 0)
    {
      return 1;
    }
  return 2 * powerOf2(n - 1);
}

/*========================== Factorial of a number ========================================*/


int factorial(int n)
{
  if (n == 0)
    {
      return 1;
    }
  return n * factorial(n - 1);
}

/*========================== Print reverse Counting======================================*/


void printReverseCounting(int n)
{
  if (n == 0)
    {
      return;
    }
  cout << n << " ";
  printReverseCounting(n - 1);
}

/*========================== Print Counting ========================================*/


void printCounting(int n)
{
  if (n == 0)
    {
      return;
    }
  printCounting(n - 1);
  cout << n << " ";
}

/*========================== Fibonacci Number ========================================*/


//returns nth fibonacci number
int fib(int n)
{
  if (n == 0)
    {
      return 0;
    }
  if (n == 1)
    {
      return 1;
    }
  return fib(n - 1) + fib(n - 2);
}


/*====================== Count Distinct Ways to climb stairs ==========================*/


//Problem statement
/*
 * You are with the number of stairs. Each time you can either climb
 * one stair or two stairs.You are at the 0th step and have to go to Nth step.
 * What are the number of in which you can go from 0th to Nth stair?
 */

/*
 * Sample Input 1 :
 * 2
 * 2
 * 3
 * Sample Output 1 :
 * 2
 * 3
 * Explanation Of Sample Input 1 :
 * In the first test case, there are only two ways to climb the stairs, i.e. {1,1} and {2}.
 *
 * In the second test case, there are three ways to climb the stairs i.e. {1,1,1} , {1,2} and {2,1}.
 *
 */

int countDistinctWays(int nStairs)
{
  if (nStairs == 0)
    {
      return 0;
    }
  if (nStairs == 1)
    {
      return 1;
    }
  if (nStairs == 2)
    {
      return 2;
    }

  return countDistinctWays(nStairs - 1) + countDistinctWays(nStairs - 2);
}


/*========================== Say Digits ========================================*/


/*
 * Say Digits -> given a number n, you have to call its digit independently
 * For eg. n = 412  --> four one two
 *      n==12345 --> one two three four five
 */
void sayDigits(int n)
{
  if (n == 0)
    return;

  static string arr[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
  int digit = n % 10;
  sayDigits(n / 10);
  cout << arr[digit] << " ";
}


/*======================== Check if Array is sorted or not ==============================*/


//Check if array is sorted
bool isSortedArray(int arr[], int n)
{
  if (n == 0 || n == 1)
    {
      return true;
    }

  if (arr[n - 1] > arr[n])
    {
      return false;
    }
  isSortedArray(arr, n - 1);
}

/*========================== Sum of Digits of An Array ====================================*/


int sumOfDigitsOfAnArray(int arr[], int n)
{
  int sum = arr[n];

  if (n < 0)
    {
      return 0;
    }
  return sum + sumOfDigitsOfAnArray(arr, n - 1);
}

/*========================== Linear Search ========================================*/


bool linearSearch(int arr[], int n, int key)
{
  if (n < 0)
    {
      return false;
    }
  if (arr[0] == key)
    {
      return true;
    }
  linearSearch(arr + 1, n - 1, key);
}

/*========================== Binary Search ========================================*/



bool binarySearch(int arr[], int start, int end, int key)
{
  if (start > end)
    {
      return false;
    }
  int mid = start + (end - start) / 2;
  if (arr[mid] == key)
    {
      return true;
    }
  else if (arr[mid] < key)
    {
      return binarySearch(arr, mid + 1, end, key);
    }
  else
    {
      return binarySearch(arr, start, mid - 1, key);
    }
}

/*========================== Peak Index in an array =====================================*/


//eg : 1 3 4 5 6 7 4 3 2 1  ---> peak index = 5 i.e 7 is peak value which is greater than the next element and its previous element.
int peakIndexInAnArray(int arr[], int n)
{
  if (arr[n - 1] > arr[n] && arr[n - 1] > arr[n - 2])
    return n - 1;

  peakIndexInAnArray(arr, n - 1);
}


/*=============== Square Root of Number rounded off to integer===================*/


//square root of a number rounded off to integer
int sqrt(int n, int start, int end)
{
  if (start > end)
    {
      return -1;
    }
  int mid = start + (end - start) / 2;
  if (mid == n / mid)
    {
      return mid;
    }
  else if (mid < n / mid)
    {
      return sqrt(n, mid + 1, end);
    }
  else
    {
      return sqrt(n, start, mid - 1);
    }
}

//****************Book Allocation Problem --> Very Important******************
//-------------similar Problem -> Painter's Partition Problem-----------------

bool isValidSolution(int arr[], int n, int m, int mid)
{
  int studentCount = 1;
  int pageSum = 0;

  for (int i = 0; i < n; i++)
    {
      if (pageSum + arr[i] <= mid)
        {
          pageSum += arr[i];
        }
      else
        {
          studentCount++;
          if (studentCount > m || arr[i] > mid)
            {
              return false;
            }
          else
            {
              pageSum = arr[i];
            }
        }
    }
  return true;
}



//here end is the sum of digits of the given array i.e., the total number of pages of books

int bookAllocationProblem(int arr[], int n, int m, int start, int end)
{
  if (n < m)
    {
      return -1;
    }
  static int ans = -1;
  if (start >= end)
    {
      return ans;
    }
  int mid = start + (end - start) / 2;
  if (isValidSolution(arr, n, m, mid))
    {
      ans = mid;
      return bookAllocationProblem(arr, n, m, start, mid - 1);
    }
  else
    {
      return bookAllocationProblem(arr, n, m, mid + 1, end);
    }
  return ans;
}
// *************************************************************************


///***************Aggressive Cows******************************(Refer Notes)
bool isPossibleSolution(int arr[], int n, int m, int mid)
{
  int cowCount = 1;
  int cowPos = arr[0];

  for (int i = 0; i < n; i++)
    {
      if (arr[i] - cowPos >= mid)
        {
          cowCount++;
          if (cowCount == m)
            {
              return true;
            }
          cowPos = arr[i];
        }
    }
  return false;
}

int aggresiveCows(int arr[], int n, int m, int start, int end)
{
  if (n < m)
    {
      return -1;
    }
  sort(arr, arr + n);   //array must be sorted in this case
  static int ans = -1;
  if (end < start)
    {
      return ans;
    }
  int mid = start + (end - start) / 2;
  if (isPossibleSolution(arr, n, m, mid))
    {
      ans = mid;
      return aggresiveCows(arr, n, m, mid + 1, end);
    }
  else
    {
      return aggresiveCows(arr, n, m, start, mid - 1);
    }
}

/*========================== To Find GCD of Two Numbers ============================*/


int gcd(int a, int b)
{
  if (a == 0)
    return b;

  if (b == 0)
    return a;

  if (a > b)
    {
      a = a - b;
    }
  else
    {
      b = b - a;
    }
  return gcd(a, b);
}

/*==========================Reverse A String ========================================*/


void stringReverse(string &str, int i, int j)
{
  if (i > j)
    {
      return;
    }
  swap(str[i++], str[j--]);
}


/*========================== Power A raised to B ========================================*/


int powerAToB(int a, int b)
{
  if (b == 0)
    {
      return 1;
    }
  if (b == 1)
    {
      return 2;
    }

  //recursive call
  int ans = powerAToB(a, b / 2);
  if (b % 2 == 0)
    {
      return ans * ans;
    }
  else
    {
      return a * ans * ans;
    }
}

/*==========================Bubble Sort Algorithm ========================================*/

//Bubble Sort Using Recursion
void bubbleSort(int arr[], int n)
{
  if (n == 0 || n == 1)
    {
      return;
    }

  for (int i = 0; i < n - 1; i++)
    {
      if (arr[i] > arr[i + 1])
        {
          swap(arr[i], arr[i + 1]);
        }
    }
  bubbleSort(arr, n - 1);
}

/*========================== Merge Sort Algorithm ========================================*/


//Merge Sort
// Striver Method of merging better than Love Babbar's --> Personal Choice
void  mergeTwoSortedArrays(int arr[], int start, int end)
{
  int mid = start + (end - start) / 2;
  vector<int> temp;
  int left = start;
  int right = mid + 1;

  while (left <= mid && right <= end)
    {
      if (arr[left] <= arr[right])
        {
          temp.push_back(arr[left++]);
        }
      else
        {
          temp.push_back(arr[right++]);
        }
    }

  while (left <= mid)
    {
      temp.push_back(arr[left++]);
    }

  while (right <= end)
    {
      temp.push_back(arr[right++]);
    }

  for (int i = start; i <= end; i++)
    {
      arr[i] = temp[i - start];
    }
}


void mergeSort(int *arr, int start, int end)
{
  //Base Case
  if (start >= end)
    {
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



/*============================ Quick Sort Algorithm ==================================== */
//Quick Sort

int pivotIndex(vector<int>& arr, int low, int high)
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



void quickSort(vector<int>& arr, int low, int high)
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




/*============================Subset of an array=================================*/



/*
 * Given an integer array nums of unique elements, return all possible
 * subsets
 * (the power set).
 *
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 *
 *
 * Example 1:
 *
 * Input: nums = [1,2,3]
 * Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 */

void findSubset(vector<int>& nums, vector<vector<int> >& ans, vector<int> output, int index)
{
  if (index >= nums.size())
    {
      ans.push_back(output);
      return;
    }

  //exclude
  findSubset(nums, ans, output, index + 1);

  //include
  output.push_back(nums[index]);
  findSubset(nums, ans, output, index + 1);
}

vector<vector<int> > subsets(vector<int>& nums)
{
  vector<vector<int> > finalAns;
  vector<int>          subset;

  findSubset(nums, finalAns, subset, 0);

  return finalAns;
}



// ---------------------------PHONE KEYPAD PROBLEM ----------------------------------------
// PHONE KEYPAD PROBLEM ->  Letter Combinations of a Phone Number -->Leetcode

/*
   Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.

   A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.
 */

void solve(string digits, vector<string>& ans, string possibleCombination, int index, vector<string> phoneKeypad)
{
  if (index >= digits.length())
    {
      ans.push_back(possibleCombination);
      return;
    }

  int number = digits[index] - '0';
  string value = phoneKeypad[number];

  for (int i = 0; i < value.length(); ++i)
    {
      possibleCombination.push_back(value[i]);
      solve(digits, ans, possibleCombination, index + 1, phoneKeypad);
      possibleCombination.pop_back();   //to make possibleCombination empty again
    }
}


vector<string> letterCombinations(string digits)
{
  vector<string> phoneKeypad = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
  vector<string> ans;
  string possibleCombination = "";

  solve(digits, ans, possibleCombination, 0, phoneKeypad);
  return ans;
}

//-------------------------Permutations------------------------------------------------
// Permutations --> LEETCODE Problem

/*
   Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.


   Example 1:

   Input: nums = [1,2,3]
   Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 */

void solve(vector<int>& nums, vector<vector<int> >& ans, int index)
{
  if (index >= nums.size())
    {
      ans.push_back(nums);
      return;
    }
  for (int i = index; i < nums.size(); i++)
    {
      swap(nums[i], nums[index]);
      solve(nums, ans, index + 1);
      //backtracking
      swap(nums[i], nums[index]);
    }
}


vector<vector<int> > permute(vector<int>& nums)
{
  vector<vector<int> > ans;

  solve(nums, ans, 0);
  return ans;
}




/*=============================Rat In A Maze Problem======================================*/





bool isSafe(int n, int newx, int newy, vector<vector<int> > &m, vector<vector<int> > visited)
{
  if ((newx >= 0 && newx < n) && ((newy >= 0 && newy < n)) && (m[newx][newy] == 1) && (visited[newx][newy] == 0))
    {
      return true;
    }
  else
    {
      return false;
    }
}
void solve(vector<vector<int> > &m, int n, vector<string> &ans, int x, int y, vector<vector<int> > visited, string path)
{
  //base case
  if ((x == n - 1) && (y == n - 1))
    {
      ans.push_back(path);
      return;
    }
  //we have reached x,y here so we update it in the visited array
  visited[x][y] = 1;

  //4 choices to move : left, right, up and down
  //Let's say it moves down:
  int newx = x + 1;
  int newy = y;
  if (isSafe(n, newx, newy, m, visited))
    {
      path.push_back('D');
      solve(m, n, ans, newx, newy, visited, path);
      path.pop_back();       //to backtrack and empty the path
    }

  //left
  newx = x;
  newy = y - 1;
  if (isSafe(n, newx, newy, m, visited))
    {
      path.push_back('L');
      solve(m, n, ans, newx, newy, visited, path);
      path.pop_back();       //to backtrack and empty the path
    }

  //up
  newx = x - 1;
  newy = y;
  if (isSafe(n, newx, newy, m, visited))
    {
      path.push_back('U');
      solve(m, n, ans, newx, newy, visited, path);
      path.pop_back();       //to backtrack and empty the path
    }

  //right
  newx = x;
  newy = y + 1;
  if (isSafe(n, newx, newy, m, visited))
    {
      path.push_back('R');
      solve(m, n, ans, newx, newy, visited, path);
      path.pop_back();       //to backtrack and empty the path
    }

  visited[x][y] = 0;
}


vector<string> findPath(vector<vector<int> > &m, int n)
{
  vector<string> ans;

  if (m[0][0] == 0)
    {
      return ans;
    }

  int srcx = 0;         //current co-ordinate of x of rat
  int srcy = 0;         //current co-ordinate of y of rat

  vector<vector<int> > visited = m;
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
        {
          visited[i][j] = 0;
        }
    }

  string path = "";
  solve(m, n, ans, srcx, srcy, visited, path);
  sort(ans.begin(), ans.end());
  return ans;
}





/*========================== main program ========================================*/


int main()
{
  int t; cin >> t;

  while (t--)
    {
      //driver code
    }
}