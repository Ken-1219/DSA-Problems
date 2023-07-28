#include "bits/stdc++.h"
using namespace std;

class Node {
public:
int data;
Node* next;
Node* prev;

Node(int data)
{
  this->data = data;
  this->next = NULL;
  this->prev = NULL;
}
};


/*===========================================================================*/


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

/*===========================================================================*/




int lengthOfLL(Node* &head)
{
  int len = 0;
  Node* temp = head;

  while (temp != NULL)
    {
      len++;
      temp = temp->next;
    }
  return len;
}

/*===========================================================================*/



void printReverseLL(Node* &tail)
{
  Node* temp = tail;

  while (temp != NULL)
    {
      cout << temp->data << " ";
      temp = temp->prev;
    }
  cout << endl;
}


/*===========================================================================*/


void insertAtHead(Node* &head, Node* &tail, int data)
{
  if (head == NULL)
    {
      Node *temp = new Node(data);
      head = temp;
      tail = head;
    }
  else
    {
      Node *temp = new Node(data);
      head->prev = temp;
      temp->next = head;
      tail = head; //updating tail to point to the newly inserted node.
      head = temp;
    }
}


/*===========================================================================*/


void insertAtEnd(Node* &head, Node* &tail, int data)
{
  if (head == NULL)
    {
      Node *temp = new Node(data);
      head = temp;
      tail = head;
    }
  else
    {
      Node *newNode = new Node(data);
      Node* temp = head;
      while (temp->next != NULL)
        {
          temp = temp->next;
        }
      newNode->prev = temp;
      temp->next = newNode;
      tail = newNode;  //updating tail to point to the newly inserted node.
    }
}

/*===========================================================================*/


void insertAtPosition(Node* &head, Node* &tail, int data, int position)
{
  if ((lengthOfLL(head) + 1 < position) || (position <= 0))
    {
      return;
    }

  //insert at head using insertAtPosition -->No need to update tail
  if (position == 1)
    {
      Node* temp = head;
      Node* newNode = new Node(data);
      temp->prev = newNode;
      newNode->next = temp;
      head = newNode;
      newNode->prev = NULL;
      return;
    }


  //insert at end using insertAtPosition  --> tail to be made as the newNode
  if (position == lengthOfLL(head) + 1)
    {
      Node* temp = tail;
      Node* newNode = new Node(data);
      tail->next = newNode;
      newNode->prev = tail;
      newNode->next = NULL;
      tail = newNode;
      return;
    }


  //insertAtPosition --> No need to update tail
  int count = 1;
  Node* temp = head;

  while (count != position - 1)
    {
      count++;
      temp = temp->next;
    }
  Node* newNode = new Node(data);
  temp->next->prev = newNode;
  newNode->next = temp->next;

  temp->next = newNode;
  newNode->prev = temp;
}


/*===========================================================================*/

void deleteAtHead(Node* &head, Node* &tail)
{
  if (head == NULL || lengthOfLL(head) == 0)
    {
      return;
    }

  if (lengthOfLL(head) == 1)
    {
      head = NULL;
      tail = NULL;
      return;
    }

  //No need to update the tail
  Node* temp = head;
  head = head->next;
  head->prev = NULL;
  temp->next = NULL;
  delete []temp;
}

/*===========================================================================*/

void deleteAtEnd(Node* &head, Node* &tail)
{
  if (lengthOfLL(head) == 0)
    {
      return;
    }

  if (lengthOfLL(head) == 1)
    {
      head = NULL;
      tail = NULL;
      return;
    }

  Node* temp = tail;
  tail = temp->prev;
  tail->next = NULL;
  temp->prev = NULL;
  delete []temp;
}



/*===========================================================================*/

void deleteAtPosition(Node* &head, Node* &tail, int pos)
{
  if (head == NULL || lengthOfLL(head) == 0 || pos > lengthOfLL(head))
    {
      return;
    }
  if (pos == 1)
    {
      deleteAtHead(head, tail);
      return;
    }
  if (pos == lengthOfLL(head))
    {
      deleteAtEnd(head, tail);
      return;
    }

  Node* temp = head;
  int count = 1;
  while (count < pos - 1)
    {
      count++;
      temp = temp->next;
    }
  Node* nodeToBeDeleted = temp->next;
  nodeToBeDeleted->next->prev = temp;
  temp->next = nodeToBeDeleted->next;
  nodeToBeDeleted->next = NULL;
  nodeToBeDeleted->prev = NULL;

  delete []nodeToBeDeleted;
}


/*===========================================================================*/


int main()
{
  int n;

  cin >> n;

  Node* head = NULL;
  Node* tail = NULL;

  for (int i = 0; i < n; ++i)
    {
      int x; cin >> x;
      insertAtEnd(head, tail, x);
    }
  printLL(head);
  cout << "Length of LL is : " << lengthOfLL(head) << endl << endl;

  //---------------- delete at 1st position that is at head ---------------------
  deleteAtPosition(head, tail, 1);
  printLL(head);
  cout << "Length of LL is : " << lengthOfLL(head) << endl << endl;


  //---------------- delete at last position that is at tail --------------------
  deleteAtPosition(head, tail, lengthOfLL(head));
  printLL(head);
  cout << "Length of LL is : " << lengthOfLL(head) << endl << endl;


  //----------------- delete at any position that is in between tail and head -----------
  deleteAtPosition(head, tail, 5);
  printLL(head);
  cout << "Length of LL is : " << lengthOfLL(head) << endl << endl;


  cout << "Reverse LL is: " << endl;
  printReverseLL(tail);
}