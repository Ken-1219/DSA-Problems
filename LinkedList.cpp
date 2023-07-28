#include "bits/stdc++.h"
using namespace std;

class Node {
public:

//Node Defined
int data;
Node *next;

//Creating Constructor
Node(int data)
{
  this->data = data;
  this->next = NULL;
}
};


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







void insertAtHead(Node *& head, int data)
{
  if (head == NULL)
    {
      Node *temp = new Node(data);
      head = temp;
    }
  else
    {
      Node *temp = new Node(data);
      temp->next = head;
      head = temp;
    }
}


void insertAtEnd(Node*& head, int data)
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




void insertAtPosition(Node*& head, int position, int data)
{
  int len = lengthOfLL(head);

  if (position > len + 1)
    {
      return;
    }

  if (position == 1)
    {
      insertAtHead(head, data);
      return;
    }
  Node* temp = head;
  int count = 1; //head is already counted

  while (count != position - 1)
    {
      temp = temp->next;
      count++;
    }
  Node* newNode = new Node(data);
  newNode->next = temp->next;
  temp->next = newNode;
}




void deleteAtHead(Node* &head)
{
  if (head == NULL)
    {
      return;
    }
  Node* temp = head;
  head = head->next;
  delete []temp;
}



void deleteAtEnd(Node* &head)
{
  if (lengthOfLL(head) <= 1)
    {
      deleteAtHead(head);
      return;
    }
  Node* temp = head;

  while (temp->next->next != NULL)
    {
      temp = temp->next;
    }
  Node* nodeToBeDeleted = temp->next;
  temp->next = NULL;

  nodeToBeDeleted->next = NULL;
  delete []nodeToBeDeleted;
}




void deleteAtPosition(Node* &head, int position)
{
  if (head == NULL || position <= 0)
    {
      return;
    }
  if (position == 1)
    {
      deleteAtHead(head);
      return;
    }
  int count = 1;
  Node* temp = head;

  while (count != position - 1)
    {
      temp = temp->next;
      count++;
    }
  Node* nodeToBeDeleted = temp->next;  //this node need to be freed from the memory
  temp->next = nodeToBeDeleted->next;

  //freeing the node to be deleted from the heap memory
  nodeToBeDeleted->next = NULL;
  delete []nodeToBeDeleted;
}


void deleteByValue(Node* &head, int val)
{
  //if length of LL = 0 i.e., LL doesn't exist so simply return
  if (lengthOfLL(head) == 0)
    {
      return;
    }

  //if head->data = val, we call delete at head
  if (head->data == val)
    {
      cout << "It is called" << endl;
      deleteAtHead(head);
      return;
    }

  Node* temp = head;

  while ((temp->next->data != val))
    {
      temp = temp->next;
      //if we have reached end and didn't find any node with data = val, exit
      if (temp->next == NULL)
        {
          cout << "Value not Found in LL" << endl;
          return;
        }
    }

  Node* nodeToBeDeleted = temp->next;
  temp->next = nodeToBeDeleted->next;
  nodeToBeDeleted->next = NULL;
  delete []nodeToBeDeleted;
}



int main()
{
  int n;

  cin >> n;

  Node *head = NULL;

  for (int i = 0; i < n; i++)
    {
      int x; cin >> x;
      insertAtEnd(head, x);
    }
  printLL(head);
  cout << "Length of Linked List is: " << lengthOfLL(head) << endl << endl;
}
