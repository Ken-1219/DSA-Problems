#include "bits/stdc++.h"
using namespace std;

class Node
{
public:
   int data;
   Node *next;

   Node(int data)
   {
      this->data = data;
      this->next = NULL;
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


/*-------------------- Merge Sort in Linked List  --------------------------------*/

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


/*-------------------------------------------------------------*/
Node * merge(Node *left, Node *right)
{
   if (left == NULL)
   {
      return right;
   }
   if (right == NULL)
   {
      return left;
   }


   Node *ans  = new Node(-1);
   Node *temp = ans;

   //merge two sorted linked lists
   while (left != NULL && right != NULL)
   {
      if (left->data < right->data)
      {
         temp->next = left;
         temp       = left;
         left       = left->next;
      }
      else
      {
         temp->next = right;
         temp       = right;
         right      = right->next;
      }
   }

   while (left != NULL)
   {
      temp->next = left;
      temp       = left;
      left       = left->next;
   }

   while (right != NULL)
   {
      temp->next = right;
      temp       = right;
      right      = right->next;
   }
   ans = ans->next;
   return ans;
}


/*-------------------------------------------------------------*/


/*
 * Time Complexity: O(NlogN)
 * Space Complexity: O(logN)
 */
Node * mergeSort(Node *head)
{
   //base case
   if ((head == NULL) || (head->next == NULL))
   {
      return head;
   }

   //break ll in two parts left and right
   Node *mid = getMiddle(head);

   Node *left  = head;
   Node *right = mid->next;
   mid->next = NULL;

   //recursive calls
   left  = mergeSort(left);
   right = mergeSort(right);

   //merge both left and right halves
   return merge(left, right);
}


/*-------------------------------------------------------------*/



int main()
{
   int n;

   cin >> n;

   Node *head = NULL;
   for (int i = 0; i < n; i++)
   {
      int x;
      cin >> x;
      insertAtEnd(head, x);
   }

   Node *ans = mergeSort(head);
   printLL(ans);
}
