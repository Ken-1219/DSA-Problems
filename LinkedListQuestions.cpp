#include "bits/stdc++.h"
using namespace std;

class Node
{
public:
   int data;
   Node *next;
   Node()
   {
      this->data = 0;
      next       = NULL;
   }

   Node(int data)
   {
      this->data = data;
      this->next = NULL;
   }

   Node(int data, Node *next)
   {
      this->data = data;
      this->next = next;
   }
};

/*----------------------------- Basic functions for LL --------------------------------*/


int lengthOfLL(Node *& head)
{
   int  len   = 0;
   Node *temp = head;

   while (temp != NULL)
   {
      len++;
      temp = temp->next;
   }
   return len;
}


void printLL(Node *& head)
{
   Node *temp = head;

   while (temp != NULL)
   {
      cout << temp->data << " ";
      temp = temp->next;
   }
   cout << endl << endl;
}


void insertAtEnd(Node *& head, int data)
{
   if (head == NULL)
   {
      Node *temp = new Node(data);
      head = temp;
   }
   else
   {
      Node *temp = head;

      while (temp->next != NULL)
      {
         temp = temp->next;
      }
      Node *newNode = new Node(data);
      temp->next = newNode;
   }
}


/*----------------------------Middle Of Linked List-------------------------------*/

/*
 * Given a singly ll of N nodes, we have to find the middle node, however if the no. of nodes is even, we return the second middle node.
 */
Node *findMiddle(Node *head)
{
   int len = lengthOfLL(head);
   int pos = len / 2 + 1; // for even and odd both, acc. to question

   Node *temp = head;
   int  count = 1;

   while (count != pos)
   {
      count++;
      temp = temp->next;
   }
   return temp;
}


/*----------------------------Reverse A Linked List-------------------------------*/


Node *reverseLinkedList(Node *& head)
{
   Node *prev = NULL;
   Node *curr = head;

   while (curr != NULL)
   {
      Node *temp = curr->next;
      curr->next = prev;
      prev       = curr;
      curr       = temp;
   }
   head = prev;
   return head;
}


// ------------------ Check if LL is circular or not -------------------------------

// Algorithm Used: Hare and Tortoise Algo or Floyd's loop detection algo

bool isCircular(Node *head)
{
   if (head == NULL)
   {
      return true;
   }
   if (head->next == NULL)
   {
      return false;
   }
   Node *slow = head;
   Node *fast = head;

   while (fast != NULL && slow != NULL)
   {
      fast = fast->next;
      if (fast != NULL)
      {
         fast = fast->next;
      }
      slow = slow->next;


      if (slow == fast)
      {
         if (slow == head)
         {
            return true;
         }
         return false;
      }
   }
   return false;
}


/*------------------ Reverse A Linked List In K Groups -------------------------------*/

/*You are given a linked list with n nodes,and an integer 'k' where k <=n.
 * Your task is to reverse the nodes in groups of each 'k' consecutive nodes
 * if n is not divisible by k, then the last group of nodes should remain unchanged
 *
 * Source : Code Studio : Reverse List In K Groups
 *
 *
 */
Node * kReverse(Node *head, int k)
{
   int len = lengthOfLL(head);

   if (len < k)
   {
      return head;
   }
   if (head == NULL)
   {
      return NULL;
   }

   Node *next = NULL;
   Node *curr = head;
   Node *prev = NULL;
   int  count = 0;

   while (curr != NULL && count < k)
   {
      next       = curr->next;
      curr->next = prev;
      prev       = curr;
      curr       = next;
      count++;
   }

   if (next != NULL)
   {
      head->next = kReverse(next, k);
   }

   return prev;
}


/*------------------ Detect and Remove Loop -------------------------------*/


//It will detect the loop at the starting point of loop

bool detectLoop(Node *head)   //TC: O(n)   SC: O(n)->due to map of size n
{
   map<Node *, bool> visited;
   Node              *temp = head;

   while (temp != NULL)
   {
      if (visited[temp] == true)
      {
         return true;
      }
      visited[temp] = true;
      temp          = temp->next;
   }
   return false;
}


//It will detect loop either at the starting or somewhere inside the loop

Node * floydLoopDetection(Node *head)   //TC: O(n)   SC: O(1)
{
   if (head == NULL)
   {
      return NULL;
   }

   Node *slow = head;
   Node *fast = head;
   while (slow != NULL && fast != NULL)
   {
      fast = fast->next;
      if (fast != NULL)
      {
         fast = fast->next;
      }
      slow = slow->next;
      if (slow == fast)
      {
         return slow;
      }
   }
   return NULL;
}


//To get the starting Node of loop with O(1) space complexity, we can use floydLoopDetection algo with a little modification:

/*
 * Approach:
 * When the floyd's loop detection detects a loop, slow and fast pointer meet somewhere inside the loop, so to get the starting point of loop, as soon as you get the intersection point of fast and slow pointer, set the slow pointer to head and move both slow and fast pointer(in our case, it is intersectionPoint pointer), eventually they will meet once again at the starting point.
 * For explanation of why? -> Refer Love Babbar Video
 */
Node * getStartingPointOfLoop(Node *head)
{
   if (head == NULL)
   {
      return NULL;
   }

   Node *intersectionPoint = floydLoopDetection(head);

   if (intersectionPoint == NULL)
   {
      return NULL;
   }

   Node *slow = head;
   while (slow != intersectionPoint)
   {
      slow = slow->next;
      intersectionPoint = intersectionPoint->next;
   }
   return slow;
}


void removeLoop(Node *head)
{
   if (head == NULL)
   {
      return;
   }
   Node *startOfLoop = getStartingPointOfLoop(head);

   if (startOfLoop == NULL)
   {
      return;
   }

   Node *temp = startOfLoop;
   while (temp->next != startOfLoop)
   {
      temp = temp->next;
   }
   temp->next = NULL;
}


/*------------ Remove Duplicates from Sorted LL ----------------*/

Node * removeDuplicatesInSortedLL(Node *& head)
{
   if (head == NULL)
   {
      return head;
   }
   Node *prev = head;
   Node *curr = head->next;
   while (curr != NULL)
   {
      if (curr->data == prev->data)
      {
         prev->next = curr->next;
         curr       = curr->next;
      }
      else
      {
         prev = prev->next;
         curr = curr->next;
      }
   }
   return head;
}


/*------------ Remove Duplicates from Sorted Doubly LL ----------------*/

/**************************************************************************
 * Definition of doubly linked list:
 * class Node {
 * public:
 *      int data;
 *      Node *prev;
 *      Node *next;
 *
 *      Node(int data) {
 *          this->data = data;
 *          this->prev = NULL;
 *          this->next = NULL;
 *      }
 * };
 *
 *************************************************************************/
void deleteNode(Node *curr)
{
   curr->prev->next = curr->next;
   if (curr->next != NULL)
   {
      curr->next->prev = curr->prev;
   }
   delete []curr;
}


Node * removeDuplicates(Node *head)
{
   if ((head == NULL) && (head->next == NULL))
   {
      return head;
   }

   Node *prev = head;
   Node *curr = head->next;
   while (curr != NULL)
   {
      if (curr->data == prev->data)
      {
         Node *temp = curr;
         curr = curr->next;
         deleteNode(temp);
      }
      else
      {
         prev = prev->next;
         curr = curr->next;
      }
   }
   return head;
}


/*------------------ Remove Duplicates from Unsorted LL -------------------------*/
void removeDuplicatesUnSorted(Node *head)
{
   // if ((head == NULL) && (head->next == NULL))
   // {
   //    return;
   // }

   unordered_set<int> visited;
   Node               *curr = head;
   Node               *prev = NULL;

   while (curr != NULL)
   {
      if (visited.find(curr->data) != visited.end())
      {
         prev->next = curr->next;
         delete (curr);
      }
      else
      {
         visited.insert(curr->data);
         prev = curr;
      }
      curr = prev->next;
   }
}


/*------------------ Sort linked list of 0s 1s 2s -------------------------------*/

/*
 * Problem Statement
 *
 * Given a linked list of 'N' nodes, where each node has an integer
 * value that can be 0, 1, or 2. You need to sort the linked list in non-
 * decreasing order and the return the head of the sorted list.
 *
 * Example:
 * Given linked list is 1 -> 0 -> 2 -> 1 - > 2.
 * The sorted list for the given linked list will be :
 * 0 -> 1 -> 1 -> 2 -> 2.1
 */
void addAtEnd(Node *& tail, int data)    //TC: O(n)     SC: O(1)
{
   Node *newNode = new Node(data);

   tail->next = newNode;
   tail       = newNode;
}


Node * sortList(Node *head)
{
   if ((head == NULL) || (head->next == NULL))
   {
      return head;
   }

   //creating separate lists of 0s 1s and 2s

   Node *head_zero = new Node(-1);
   Node *tail_zero = head_zero;

   Node *head_one = new Node(-1);
   Node *tail_one = head_one;

   Node *head_two = new Node(-1);
   Node *tail_two = head_two;

   Node *temp = head;

   while (temp != NULL)
   {
      if (temp->data == 0)
      {
         addAtEnd(tail_zero, 0);
      }
      if (temp->data == 1)
      {
         addAtEnd(tail_one, 1);
      }
      if (temp->data == 2)
      {
         addAtEnd(tail_two, 2);
      }
      temp = temp->next;
   }


   //merging the separate lists of 0s 1s and 2s
   if (head_one->next != NULL)
   {
      tail_zero->next = head_one->next;
      tail_one->next  = head_two->next;
      tail_two->next  = NULL;
   }
   else
   {
      tail_zero->next = head_two->next;
      tail_two->next  = NULL;
   }
   head_zero = head_zero->next;


   return head_zero;
}


/*------------------ Merge Two Sorted Linked Lists ------------------------------*/

/*
 * Problem Statement
 *
 * You are given two sorted linked lists. You have to merge them to
 * produce a combined sorted linked list. You need to return the head
 * of the final linked list.
 * Note:
 * The given linked lists may or may not be null.
 *
 * For example:
 * If the first list is: 1 -> 4 -> 5 -> NULL and the
 * second list is: 2 -› 3 -> 5 -> NULL
 * The final list would be: 1 ->2->3->4->5->5-> NULL
 */
Node * mergeTwoSortedLists(Node *first, Node *second)
{
   if (first == NULL)
   {
      return second;
   }
   if (second == NULL)
   {
      return first;
   }

   //this will point to the head of the sorted list
   Node *head = NULL;

   //creating pointers for first and second lists
   Node *list1 = first;
   Node *list2 = second;
   Node *prev  = NULL;

   while (list1 != NULL && list2 != NULL)
   {
      if (list1->data <= list2->data)
      {
         //if the first iteration occurs here, make head as first
         if (head == NULL)
         {
            head = first;
         }
         if (prev != NULL)
         {
            prev->next = list1;
         }
         prev  = list1;
         list1 = list1->next;
      }

      else
      {
         //if the first iteration occurs here, make head as second

         if (head == NULL)
         {
            head = second;
         }
         if (prev != NULL)
         {
            prev->next = list2;
         }

         prev  = list2;
         list2 = list2->next;
      }
   }

   //check which list was traversed completely first, and then point prev to the other one

   if (list1 == NULL)
   {
      prev->next = list2;
   }
   else
   {
      prev->next = list1;
   }

   return head;
}


/*------------------ Check If Palindrome or Not -------------------------------*/

/*
 *  Approach:
 *
 *  1)Find Middle of the LL
 *  2)Reverse the LL after the middle to end
 *  3)Now start one pointer from head and one just after middle and compare to check for palindrome
 *  4)Repeat 2 to get the original LL
 *
 */
Node * getMiddle(Node *head)
{
   Node *slow = head;
   Node *fast = head->next;

   while (fast != NULL && fast->next != NULL)
   {
      fast = fast->next->next;
      slow = slow->next;
   }
   return slow;
}


Node * reverseLL(Node *head)
{
   Node *curr = head;
   Node *prev = NULL;

   while (curr != NULL)
   {
      Node *next = curr->next;
      curr->next = prev;
      prev       = curr;
      curr       = next;
   }
   return prev;
}


bool isPalindrome(Node *head)
{
   //if list is empty or only one element is there, then LL is palindrom
   if ((head == NULL) || (head->next == NULL))
   {
      return true;
   }

   //find middle of LL
   Node *middle = getMiddle(head);
   // printLL(middle->next);

   //reverseLL after middle
   Node *temp = middle->next;
   middle->next = reverseLL(temp);
   // printLL(middle->next);

   //compare both halves
   Node *head1 = head;
   Node *head2 = middle->next;
   while (head2 != NULL)
   {
      if (head1->data != head2->data)
      {
         return false;
      }
      head1 = head1->next;
      head2 = head2->next;
   }

   //reverse again
   temp         = middle->next;
   middle->next = reverseLL(temp);

   //return ans
   return true;
}


/*----------- Add two numbers represented by linked lists --------------------*/

/*
 * Given two decimal numbers represented by two linked lists of size N and M respectively. The task is to return a linked list that represents the sum of these two numbers.
 *
 * For example, the number 190 will be represented by the linked list, 1->9->0->null, similarly 25 by 2->5->null. Sum of these two numbers is 190 + 25 = 215, which will be represented by 2->1->5->null. You are required to return the head of the linked list 2->1->5->null.
 *
 */


/*
 * Approach:
 * 1)Reverse the given LL
 * 2) Create a new LL that will store the sum of the two LL
 * 3)Reverse the LL that stores the sum
 */
void addAtEnd1(Node *& head, Node *& tail, int data)  //TC: O(n + m)  SC: O(max(m,n))
{
   if (head == NULL)
   {
      Node *newNode = new Node(data);
      head = newNode;
      tail = head;
      return;
   }
   Node *newNode = new Node(data);

   tail->next = newNode;
   tail       = newNode;
}


Node * reverseLL1(Node *head)
{
   Node *curr = head;
   Node *prev = NULL;

   while (curr != NULL)
   {
      Node *next = curr->next;
      curr->next = prev;
      prev       = curr;
      curr       = next;
   }
   return prev;
}


Node * addTwoLists(Node *first, Node *second)
{
   first  = reverseLL1(first);
   second = reverseLL1(second);

   Node *head = NULL;
   Node *tail = NULL;
   int  carry = 0;
   int  sum   = 0;


   while (first != NULL || second != NULL || carry != 0)
   {
      int val1 = 0;
      if (first != NULL)
      {
         val1 = first->data;
      }

      int val2 = 0;
      if (second != NULL)
      {
         val2 = second->data;
      }

      sum = val1 + val2 + carry;
      int rem = sum % 10;
      carry = sum / 10;

      addAtEnd1(head, tail, rem);

      if (first != NULL)
      {
         first = first->next;
      }

      if (second != NULL)
      {
         second = second->next;
      }
   }

   head = reverseLL1(head);

   return head;
}


/*-------------------------------------------------------------*/

/*
 *
 * Two other questions are in a separate files: cloneLL and mergeSortLL
 */

/*-------------------------------------------------------------*/



int main()
{
   //main program here
}
