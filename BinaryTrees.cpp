#include "bits/stdc++.h"
using namespace std;


// Node of a tree
class Node {
public:
int data;
Node * left;
Node * right;

Node(int data)
{
   this->data = data;
   this->left = NULL;
   this->right = NULL;
}
};



/*-------------------------------------------------------------------------------*/



// pre-order traversal ---> Root->Left->Right  ---> TC: O(n)  SC: O(h)  (height)

void preOrderTraversal (Node * root)
{
   if (root == NULL) {
      return;
   }

   cout << root->data << " "; // root
   preOrderTraversal (root->left); // left
   preOrderTraversal (root->right); // right
}


/*-------------------------------------------------------------------------------*/



// in-order traversal ---> Left->Root->Right --> TC: O(n)   SC: O(h)

void inOrderTraversal (Node * root)
{
   if (root == NULL) {
      return;
   }

   inOrderTraversal (root->left); // left
   cout << root->data << " "; // root
   inOrderTraversal (root->right); // right
}


/*-------------------------------------------------------------------------------*/



// post-order traversal ---> Left->Right->Root --> TC: O(n)   SC: O(h)

void postOrderTraversal (Node * root)
{
   if (root == NULL) {
      return;
   }

   postOrderTraversal (root->left); // left
   postOrderTraversal (root->right); // right
   cout << root->data << " "; // root
}


/*-------------------------------------------------------------------------------*/

// level-order Traversal or BFS or Breadth First Search  --> TC: O(n)   SC: O(n)

vector<vector<int> > levelOrderTraversal (Node * root)
{
   vector<vector<int> > traversal; // it will store level-wise nodes present in the tree

   if (root == NULL) {
      return traversal;
   }
   queue<Node *> q;
   q.push (root);
   while (!q.empty ()) {
      int size = q.size ();
      vector<int> level; // it will store the nodes at a particular level
      for (int i = 0; i < size; i++) {
         Node * curr = q.front ();
         q.pop ();
         if (curr->left != NULL) {
            q.push (curr->left);
         }
         if (curr->right != NULL) {
            q.push (curr->right);
         }
         level.push_back (curr->data);
      }
      traversal.push_back (level);
   }
   return traversal;
}


/*-------------------------------------------------------------------------------*/

// Iterative PreOrderTraversal Using Stack

vector<int> preOrderIterative (Node * root)
{
   vector<int> preOrder;

   if (root == NULL) {
      return preOrder;
   }

   stack<Node *>s;
   s.push (root);
   while (!s.empty ()) {
      Node * curr = s.top ();
      s.pop ();
      preOrder.push_back (curr->data);
      // right node should be first pushed in the stack as stack is LIFO in nature
      if (curr->right != NULL) {
         s.push (curr->right);
      }
      if (curr->left != NULL) {
         s.push (curr->left);
      }
   }
   return preOrder;
}


/*-------------------------------------------------------------------------------*/


vector<int> inOrderIterative (Node * root)
{
   vector<int> inOrder;

   if (root == NULL) {
      return inOrder;
   }

   stack<Node *> s;
   Node * curr = root;
   while (true) {
      if (curr != NULL) {
         s.push (curr);
         curr = curr->left;
      }
      else {
         if (s.empty ()) {
            break;
         }
         else {
            curr = s.top ();
            s.pop ();
            inOrder.push_back (curr->data);
            curr = curr->right;
         }
      }
   }
   return inOrder;
}


/*-------------------------------------------------------------------------------*/
//Iterative PostOrder Traversal Using 2-stacks
vector<int> postOrderIterative_2Stack (Node * root)   //TC: O(n)  SC: O(2*n) = O(n)
{
   vector<int> postOrder;
   stack<Node*> s1;
   stack<Node*> s2;

   s1.push (root);
   while (!s1.empty ()) {
      Node* curr = s1.top ();
      s1.pop ();
      s2.push (curr);
      if (curr->left != NULL) {
         s1.push (curr->left);
      }
      if (curr->right != NULL) {
         s1.push (curr->right);
      }
   }

   while (!s2.empty ()) {
      Node* node = s2.top ();
      s2.pop ();
      postOrder.push_back (node->data);
   }
   return postOrder;
}



/*-------------------------------------------------------------------------------*/

//Iterative PostOrder Traversal Using 1-stack
vector<int> postOrderIterative_1Stack (Node * root)   //TC: O(n)  SC: O(n)
{
   vector<int> postOrder;

   if (root == NULL) {
      return postOrder;
   }

   stack<Node* > s;
   Node* curr = root;

   while (curr != NULL || !s.empty ()) {
      if (curr != NULL) {
         s.push (curr);
         curr = curr->left;
      }
      else{
         Node* prevNode = s.top ()->right;
         if (prevNode != NULL) {
            curr = prevNode;
         }
         else{
            prevNode = s.top ();
            s.pop ();
            postOrder.push_back (prevNode->data);
            while (!s.empty () && prevNode == s.top ()->right) {
               prevNode = s.top ();
               s.pop ();
               postOrder.push_back (prevNode->data);
            }
         }
      }
   }
   return postOrder;
}



/*-------------------------------------------------------------------------------*/

int main ()
{
   Node * root = new Node (1);

   root->left = new Node (2);
   root->right = new Node (3);
   root->left->left = new Node (4);
   root->left->right = new Node (5);
   root->left->left->right = new Node (6);
   root->left->left->left = new Node (7);
   root->right->left = new Node (8);
   root->right->right = new Node (9);


   vector<int>traverse = postOrderIterative_1Stack (root);
   for (int i = 0; i < traverse.size (); i++) {
      cout << traverse [i] << " ";
   }
}
