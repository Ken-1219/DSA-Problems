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



// pre-order traversal ---> Root->Left->Right  ---> TC: O(n)  SC: O(n)

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



// in-order traversal ---> Left->Root->Right --> TC: O(n)   SC: O(n)

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



// post-order traversal ---> Left->Right->Root --> TC: O(n)   SC: O(n)

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

int maxDepth (Node* root)  //TC: O(N)  SC: O(height) || O(N) in case of skew tree
{
   if (!root) {
      return 0;
   }

   int lh = maxDepth (root->left);
   int rh = maxDepth (root->right);

   return 1 + max (lh, rh);
}


/*-------------------------------------------------------------------------------*/
/*Diameter of a Binary Tree*/
/*
 * The diameter of a tree (sometimes called the width) is the number of nodes on the longest path between two end nodes
 */

// APPROACH # 1:

int diameter (Node* root)  //TC: O(n^2) because of function call of maxDepth { O(N) }
{
   if (root == NULL) {
      return 0;
   }

   int d1 = diameter (root->left); //diameter may be only in the left subtree
   int d2 = diameter (root->right); //diameter may be only in the right subtree
   int d3 = maxDepth (root->left) + maxDepth (root->right) + 1;
   //diameter may be the combination of both.

   return max (d1, max (d2, d3));
}

// APPROACH # 2:

pair<int, int> diameterFast (Node* root)
{
   if (root == NULL) {
      return make_pair (0, 0);
   }

   // <diameter,height>
   //In one iteration I will obtain both diameter and height

   pair<int, int> left = diameterFast (root->left);
   pair<int, int> right = diameterFast (root->right);

   int d1 = left.first; //diameter may be only in the left subtree
   int d2 = right.first; //diameter may be only in the right subtree
   int d3 = left.second + right.second + 1; //diameter may be the combination of both.

   pair<int, int> ans;
   ans.first = max (d1, max (d2, d3)); //diameter
   ans.second = max (left.second, right.second) + 1; //height
   return ans;
}

int optimizedDiameter (Node* root) //TC: O(N)
{
   return diameterFast (root).first;
}


//Approach-3 :
int maxHeight (Node* root, int &diameter)
{
   if (!root) {
      return 0;
   }

   int lh = maxHeight (root->left, diameter);
   int rh = maxHeight (root->right, diameter);

   diameter = max (diameter, lh + rh);
   return 1 + max (lh, rh);
}

int diameterOfBinaryTree (Node* root)
{
   int diameter = 0;

   maxHeight (root, diameter);
   return diameter;
}


/*-------------------------------------------------------------------------------*/
/*Check for Balanced Tree*/
/*Given a binary tree, find if it is height balanced or not.
 * A tree is height balanced if difference between heights of left and right subtrees is not more than one for all nodes of tree.
 *
 * A height balanced tree
 *      1
 *    /   \
 *  10     39
 *  /
 * 5
 *
 * An unbalanced tree
 *      1
 *     /
 *   10
 *   /
 *  5
 *
 */

//Approach-1:

bool isBalanced (Node* root)  //TC : O(n^2)
{
   if (!root) {
      return true;
   }

   bool left = isBalanced (root->left); //check for left sub-tree
   bool right = isBalanced (root->right); // check for right sub-tree

   //check if the abs((height of left sub-tree)-(height of right sub-tree)) <= 1
   bool diff = abs (maxDepth (root->left) - maxDepth (root->right)) <= 1;

   if (left && right && diff) {
      return true;
   }
   return false;
}

//Approach-2

pair<bool, int> isBalancedBetter (Node* root)  //TC: O(n)  SC: O(H)
{
   if (!root) {
      return make_pair (true, 0);
   }
   pair<bool, int> p;


   pair<bool, int> left = isBalancedBetter (root->left);
   pair<bool, int> right = isBalancedBetter (root->right);

   bool leftAns = left.first;//check for left sub-tree
   bool rightAns = right.first; // check for right sub-tree
   //check if the abs((height of left sub-tree)-(height of right sub-tree)) <= 1
   bool diff = abs (left.second - right.second) <= 1;

   pair<int, int> ans;
   ans.second = max (left.second, right.second) + 1;
   if (leftAns && rightAns && diff) {
      ans.first = true;
   }
   else{
      ans.first = false;
   }
   return ans;
}

bool isBalanced1 (Node* root)
{
   return isBalancedBetter (root).first;
}


// Approach-3:
/*
 * Approach :
 *
 * Start traversing the tree recursively and do work in Post Order.
 * For each call, calculate the height of the root node, and return it to previous calls.
 * Simultaneously, in the Post Order of every node , Check for condition of balance as information of left and right subtree height is available.
 * If it is balanced , simply return height of current node and if not then return -1.
 * Whenever the sub-tree result is -1 , simply keep on returning -1.
 */

int height (Node* root)
{
   if (!root) return 0;

   int lh = height (root->left);
   if (lh == -1) {
      return -1;
   }

   int rh = height (root->right);
   if (rh == -1) {
      return -1;
   }

   if (abs (lh - rh) > 1) {
      return -1;
   }

   return 1 + max (lh, rh);
}

bool isBalanced2 (Node* root)
{
   return height (root) != -1;
}



/*-------------------------------------------------------------------------------*/
/* Determine if two binary trees are identical or not */
//Given two binary trees, the task is to find if both of them are identical or not


bool isIdentical (Node *r1, Node *r2)
{
   if (r1 == NULL && r2 == NULL) {
      return true;
   }
   if ((r1 == NULL && r2 != NULL) || (r1 != NULL && r2 == NULL)) {
      return false;
   }

   bool left = isIdentical (r1->left, r2->left);
   bool right = isIdentical (r1->right, r2->right);

   bool value = r1->data == r2->data;

   if (left && right && value) {
      return true;
   }
   return false;
}

/*-------------------------------------------------------------------------------*/
// SUM TREE

/*
 * Given a Binary Tree. Return true if, for every node X in the tree other than the leaves, its value is equal to the sum of its left subtree's value and its right subtree's value. Else return false.
 *
 * An empty tree is also a Sum Tree as the sum of an empty tree can be considered to be 0. A leaf node is also considered a Sum Tree.
 */

bool isLeaf (Node* node)
{
   if (node == NULL)
      return false;
   if (node->left == NULL && node->right == NULL)
      return true;
   return false;
}

int checkSumTree (Node *root)
{
   if (!root) {
      return 0;
   }

   int lSum = checkSumTree (root->left);
   if (lSum == -1) {
      return -1;
   }

   int rSum = checkSumTree (root->right);
   if (rSum == -1) {
      return -1;
   }

   if (isLeaf (root) || lSum + rSum == root->data) {
      return lSum + rSum + root->data;
   }
   return -1;
}

bool isSumTree (Node*root)
{
   return(checkSumTree (root) != -1);
}



/*-------------------------------------------------------------------------------*/
// ZigZag Tree Traversal
vector <int> zigZagTraversal (Node* root)  //TC: O(n)  SC: O(n)
{
   vector<int> result;

   if (!root) {
      return result;
   }

   queue<Node*> q;
   q.push (root);

   bool leftToRight = true;

   while (!q.empty ()) {
      int size = q.size ();
      vector<int> temp (size); // it will store data in L->R or R->L order

      for (int i = 0; i < size; i++) {
         Node* curr = q.front ();
         q.pop ();

         //if leftToRight is true, start from i, otherwise start from end
         int index = leftToRight ? i : size - i - 1;
         temp [index] = curr->data;

         if (curr->left != NULL) {
            q.push (curr->left);
         }
         if (curr->right != NULL) {
            q.push (curr->right);
         }
      }

      //change direction
      leftToRight = !leftToRight;

      for (int i : temp) {
         result.push_back (i);
      }
   }
   return result;
}



/*-------------------------------------------------------------------------------*/
// Boundary Traversal of Binary Tree

//Approach :
/*
 * 1) Traverse to the left, excluding the left leaf node
 * 2) Traverse all leaf nodes
 * 3) Traverse to the right in the reverse direction , excluding the right leaf node
 */


void traverseLeft (Node* root, vector<int>& ans)
{
   if (!root) {
      return;
   }

   //check if leaf node, return
   if (!root->left && !root->right) {
      return;
   }

   //store the left
   ans.push_back (root->data);

   //if left exists go to left
   if (root->left) {
      traverseLeft (root->left, ans);
   }

   //otherwise, go to right
   else{
      traverseLeft (root->right, ans);
   }
}



void traverseLeafNode (Node* root, vector<int> &ans)
{
   if (!root) {
      return;
   }

   //if leaf node, store
   if (!root->left && !root->right) {
      ans.push_back (root->data);
      return;
   }

   //else traverse to left and then to right
   traverseLeafNode (root->left, ans);
   traverseLeafNode (root->right, ans);
}


void traverseReverseRight (Node* root, vector<int> & ans)
{
   if (!root) {
      return;
   }

   //check if leaf node, return
   if (!root->left && !root->right) {
      return;
   }


   //if right exists, go to right
   if (root->right) {
      traverseReverseRight (root->right, ans);
   }
   //otherwise go to left
   else{
      traverseReverseRight (root->left, ans);
   }

   //store the root data
   ans.push_back (root->data);
}


vector <int> boundary (Node *root)    //TC: O(n)  SC: O(n)
{
   vector<int> ans;

   if (!root)
      return ans;

   //store the root node
   ans.push_back (root->data);

   //traverse left --> excluding the left leaf node
   traverseLeft (root->left, ans);

   //traverse all leaf nodes
   // --left sub tree
   traverseLeafNode (root->left, ans);

   //--right sub tree
   traverseLeafNode (root->right, ans);

   //traverse right in reverse direction
   traverseReverseRight (root->right, ans);

   return ans;
}


/*-------------------------------------------------------------------------------*/
//Vertical Order Traversal of Binary Trees

vector<int> verticalOrder (Node* root)
{
   // map structure: <HD, <levels,nodes>>
   map<int, map<int, vector<int> > >nodes;

   // queue structure : <Node, <horizontal distance (HD), level>>
   queue<pair<Node*, pair<int, int> > > q;

   vector<int> ans;

   if (!root) {
      return ans;
   }

   //now push the root into queue, for that we know the horizontal distance as well as the level at root is (0,0)
   q.push (make_pair (root, make_pair (0, 0)));

   while (!q.empty ()) {
      pair<Node*, pair<int, int> > temp = q.front ();
      Node* frontNode = temp.first;
      q.pop ();

      int hd = temp.second.first; //horizontal distance
      int lvl = temp.second.second; //levels

      //now create an entry for the map at this hd and lvl
      nodes [hd] [lvl].push_back (frontNode->data);

      if (frontNode->left) {
         q.push (make_pair (frontNode->left, make_pair (hd - 1, lvl + 1)));
      }
      if (frontNode->right) {
         q.push (make_pair (frontNode->right, make_pair (hd + 1, lvl + 1)));
      }
   }

   //obtaining ans from the map nodes
   for (auto i : nodes) {
      //i.first = hd  i.second = map<level,vector<nodes->data>
      for (auto j: i.second) {
         // j = map<level,vector<nodes->data>
         for (auto k : j.second) {
            //k denotes element of vector that is our node data
            ans.push_back (k);
         }
      }
   }
   return ans;
}
/*-------------------------------------------------------------------------------*/
//Top View of a Binary Tree

vector<int> topView (Node* root)
{
   vector<int> result;

   if (!root) {
      return result;
   }

   map<int, int> topNode; //< horizontal distance,  Node data>
   queue<pair<Node*, int> > q; //<Node, hd>

   q.push (make_pair (root, 0));

   while (!q.empty ()) {
      pair<Node*, int> temp = q.front ();
      q.pop ();

      Node* frontNode = temp.first;
      int hd = temp.second;

      //if node data of a particular hd is not present in map, then insert otherwise leave
      if (topNode.find (hd) == topNode.end ()) {
         topNode [hd] = frontNode->data;
      }

      if (frontNode->left) {
         q.push (make_pair (frontNode->left, hd - 1));
      }
      if (frontNode->right) {
         q.push (make_pair (frontNode->right, hd + 1));
      }
   }

   for (auto i : topNode) {
      result.push_back (i.second);
   }

   return result;
}

/*-------------------------------------------------------------------------------*/
//Bottom View of the Binary Tree

vector <int> bottomView (Node *root)
{
   vector<int> result;

   if (!root) {
      return result;
   }

   map<int, int> topNode; //< horizontal distance,  Node data>
   queue<pair<Node*, int> > q; //<Node, hd>

   q.push (make_pair (root, 0));

   while (!q.empty ()) {
      pair<Node*, int> temp = q.front ();
      q.pop ();

      Node* frontNode = temp.first;
      int hd = temp.second;

      // insert the data
      topNode [hd] = frontNode->data;

      if (frontNode->left) {
         q.push (make_pair (frontNode->left, hd - 1));
      }
      if (frontNode->right) {
         q.push (make_pair (frontNode->right, hd + 1));
      }
   }

   for (auto i : topNode) {
      result.push_back (i.second);
   }

   return result;
}



/*-------------------------------------------------------------------------------*/
//Left View of  binary tree

// Approach-1 : Iterative
vector<int> leftView1 (Node *root)   //TC: O(NLogN) SC: O(N)
{
   vector<int> ans;

   if (!root) {
      return ans;
   }

   queue<Node*> q;
   q.push (root);

   while (!q.empty ()) {
      int n = q.size ();
      for (int i = 0; i < n; i++) {
         Node* curr = q.front ();
         q.pop ();


         if (curr->left) {
            q.push (curr->left);
         }
         if (curr->right) {
            q.push (curr->right);
         }

         if (i == 0) {
            ans.push_back (curr->data);
         }
      }
   }
   return ans;
}


// Approach-2: Recursive (Simple and clean)  //TC: O(NLogN) SC: O(H)
void solve (Node* root, vector<int> &ans, int level)
{
   //base case
   if (root == NULL)
      return;

   //we entered into a new level
   if (level == ans.size ())
      ans.push_back (root->data);

   solve (root->left, ans, level + 1);
   solve (root->right, ans, level + 1);
}

vector<int> leftView2 (Node *root)
{
   vector<int> ans;

   solve (root, ans, 0);
   return ans;
}


/*-------------------------------------------------------------------------------*/
//Right View of the Binary Tree

// Approach-1 : Iterative
vector<int> rightView1 (Node *root)   //TC: O(NLogN) SC: O(N)
{
   vector<int> ans;

   if (!root) {
      return ans;
   }

   queue<Node*> q;
   q.push (root);

   while (!q.empty ()) {
      int n = q.size ();
      for (int i = 0; i < n; i++) {
         Node* curr = q.front ();
         q.pop ();


         if (curr->right) {
            q.push (curr->right);
         }
         if (curr->left) {
            q.push (curr->left);
         }

         if (i == 0) {
            ans.push_back (curr->data);
         }
      }
   }
   return ans;
}


// Approach-2: Recursive (Simple and clean)  //TC: O(NLogN) SC: O(H)
void solve2 (Node* root, vector<int> &ans, int level)
{
   //base case
   if (root == NULL)
      return;

   //we entered into a new level
   if (level == ans.size ())
      ans.push_back (root->data);

   solve2 (root->right, ans, level + 1);
   solve2 (root->left, ans, level + 1);
}

vector<int> rightView2 (Node *root)
{
   vector<int> ans;

   solve2 (root, ans, 0);
   return ans;
}


/*-------------------------------------------------------------------------------*/
//Sum of the Longest Bloodline of a Tree (Sum of nodes on the longest path from root to leaf node) --> GFG

/*
 * Given a binary tree of size N. Your task is to complete the function sumOfLongRootToLeafPath(), that find the sum of all nodes on the longest path from root to leaf node.
 * If two or more paths compete for the longest path, then the path having maximum sum of nodes is being considered.
 * Example 1:
 *
 * Input:
 *      4
 *     / \
 *    2   5
 *   / \ / \
 *  7  1 2  3
 *    /
 *   6
 * Output: 13
 *
 * Explanation:
 *      4
 *     / \
 *    2   5
 *   / \ / \
 *  7  1 2  3
 *    /
 *   6
 *
 * The highlighted nodes (4, 2, 1, 6) above are
 * part of the longest root to leaf path having
 * sum = (4 + 2 + 1 + 6) = 13
 *
 *
 */

void solveSum (Node* root, int sum, int &maxSum, int len, int &maxLen)
{
   //base case
   if (root == NULL) {
      if (len > maxLen) {
         maxLen = len;
         maxSum = sum;
      }
      else if (len == maxLen) {
         maxSum = max (sum, maxSum);
      }
      return;
   }

   sum += root->data;

   solveSum (root->left, sum, maxSum, len + 1, maxLen);
   solveSum (root->right, sum, maxSum, len + 1, maxLen);
}

int sumOfLongRootToLeafPath (Node *root) //TC: O(N)  SC: O(H)
{
   int sum = 0, maxSum = 0;
   int len = 0, maxLen = 0;

   solveSum (root, sum, maxSum, len, maxLen);
   return maxSum;
}


/*-------------------------------------------------------------------------------*/
// Lowest Common Ancestor in a Binary Tree
/* Given a Binary Tree with all unique values and two nodes value, n1 and n2. The task is to find the lowest common ancestor of the given two nodes. We may assume that either both n1 and n2 are present in the tree or none of them are present.
 *
 * LCA: It is the first common ancestor of both the nodes n1 and n2 from bottom of tree.
 *
 * Example 1:
 *
 * Input:
 * n1 = 2 , n2 = 3
 *     1
 *    / \
 *   2   3
 * Output: 1
 * Explanation:
 * LCA of 2 and 3 is 1.
 *
 */

Node* lca (Node* root, int n1, int n2) //TC: O(N)  SC: O(H)
{
   if (!root) {
      return NULL;
   }

   if (root->data == n1 || root->data == n2) {
      return root;
   }

   Node* leftAns = lca (root->left, n1, n2);
   Node* rightAns = lca (root->right, n1, n2);

   if (leftAns && rightAns) {
      return root;
   }
   else if (!leftAns && rightAns) {
      return rightAns;
   }
   else if (leftAns && !rightAns) {
      return leftAns;
   }
   else{
      return NULL;
   }
}

/*-------------------------------------------------------------------------------*/
//K SUM PATHS
/*Given a binary tree and an integer K. Find the number of paths in the tree which have their sum equal to K.
 * A path may start from any node and end at any node in the downward direction.
 * Example 1:
 *
 * Input:
 * Tree =
 *        1
 *      /   \
 *     2     3
 * K = 3
 * Output: 2
 * Explanation:
 * Path 1 : 1 + 2 = 3
 * Path 2 : only leaf node 3
 */
void countPaths (Node* root, int k, int currSum, unordered_map<int, int>& prefixSum, int& count)
{
   if (!root)
      return;

   // Calculate the current sum including the current node
   currSum += root->data;

   // Check if there exists a sub-path with sum (currSum - targetSum), which means the sum from that sub-path to the current node is equal to targetSum
   count += prefixSum [currSum - k];

   // Update the prefix sum hashmap
   prefixSum [currSum]++;

   // Recurse to left and right subtrees
   countPaths (root->left, k, currSum, prefixSum, count);
   countPaths (root->right, k, currSum, prefixSum, count);

   // Backtrack and remove the current sum from the hashmap
   prefixSum [currSum]--;
}

int sumK (Node* root, int k)
{
   unordered_map<int, int> prefixSum;

   prefixSum [0] = 1; // Initialize the hashmap with the prefix sum of 0
   int count = 0;
   countPaths (root, k, 0, prefixSum, count);
   return count;
}

/*-------------------------------------------------------------------------------*/
//Kth Ancestor
/*Given a binary tree of size  N, a node, and a positive integer k., Your task is to complete the function kthAncestor(), the function should return the kth ancestor of the given node in the binary tree. If there does not exist any such ancestor then return -1.
 * Note:
 * 1. It is guaranteed that the node exists in the tree.
 * 2. All the nodes of the tree have distinct values.
 */

//Approach-1: (Get the path and return the ans)
void findAncestor (Node* root, int k, int node, vector<int> &path)
{
   //base case
   if (!root) {
      return;
   }

   //push root into vector to add path
   path.push_back (root->data);
   if (path [path.size () - 1] == node) {
      return;
   }

   //left call
   findAncestor (root->left, k, node, path);

   //right call
   findAncestor (root->right, k, node, path);

   if (path [path.size () - 1] == node) {
      return;
   }

   path.pop_back ();
}


int kthAncestor (Node *root, int k, int node)  //TC: O(n)  SC: O(n)
{
   vector<int> path;

   findAncestor (root, k, node, path);

   int size = path.size ();
   int index = size - k - 1;
   if (index >= 0)
      return path [index];
   return -1;
}



//Approach-2:
Node* findAncestor1 (Node *root, int &k, int node)
{
   //base case
   if (!root) {
      return NULL;
   }

   if (root->data == node) {
      return root;
   }

   Node* left = findAncestor1 (root->left, k, node);
   Node* right = findAncestor1 (root->right, k, node);

   //after coming from left and right recursive calls
   if (left && !right) {
      k--;

      if (k <= 0) {
         //lock ans
         k = INT_MAX; //in case k is decremented again, it is to avoid losing the track of our ans
         return root; // since k==0 this is our ans
      }

      return left; //else return the current left
   }

   if (!left && right) {
      k--;

      if (k <= 0) {
         //lock ans
         k = INT_MAX; //in case k is decremented again, it is to avoid losing the track of our ans
         return root; // since k==0 this is our ans
      }

      return right; //else return the current left
   }
   return NULL;
}


int kthAncestor1 (Node *root, int k, int node)  //TC: O(n)  SC: O(H)
{
   Node* ans = findAncestor1 (root, k, node);

   if (ans == NULL || ans->data == node) {
      return -1;
   }
   else{
      return ans->data;
   }
}


/*-------------------------------------------------------------------------------*/
//Maximum sum of Non-adjacent Node

/*
 * Given a binary tree with a value associated with each node, we need to choose a subset of these nodes such that sum of chosen nodes is maximum under a constraint that no two chosen node in subset should be directly connected that is, if we have taken a node in our sum then we can’t take its any children or parents in consideration and vice versa.
 */

pair<int, int> findSum (Node* root)
{
   //base case
   if (!root) {
      return make_pair (0, 0);
   }

   pair<int, int> left = findSum (root->left);
   pair<int, int> right = findSum (root->right);

   pair<int, int> result;

   //include the root node in ans
   result.first = root->data + left.second + right.second;

   //exclude the root node in ans
   result.second = max (left.first, left.second) + max (right.first, right.second);

   return result;
}

int getMaxSum (Node *root)  //TC: O(n)  SC: O(H)
{
   pair<int, int> ans = findSum (root); //pair structure :  <include root in sum, exclude root in sum>

   return(max (ans.first, ans.second));
}




/*-------------------------------------------------------------------------------*/
// Construct BT from Inorder and Preorder
/*Given 2 Arrays of Inorder and preorder traversal. The tree can contain duplicate elements. Construct a tree and print the Postorder traversal.
 */

int findPosition (int in[], int ele, int inorderStart, int inorderEnd)
{
   for (int i = inorderStart; i <= inorderEnd; i++) {
      if (in [i] == ele) {
         return i;
      }
   }
   return -1;
}


Node* makeTree (int in[], int pre[], int n, int &index, int inorderStart, int inorderEnd)
{
   //base case
   if (index >= n || inorderStart > inorderEnd) {
      return NULL;
   }

   int ele = pre [index++]; //getting the root value
   Node* root = new Node (ele); //creating the root node

   int pos = findPosition (in, ele, inorderStart, inorderEnd); //find position of element in inorder array

   //recursive calls
   root->left = makeTree (in, pre, n, index, inorderStart, pos - 1);
   root->right = makeTree (in, pre, n, index, pos + 1, inorderEnd);

   return root;
}

Node* buildTree (int in[], int pre[], int n) //TC: O(N^2)  SC: O(N)
{
   int preOrderIndex = 0; //this will be the root of the BT as preorder is -> NLR
   Node* result = makeTree (in, pre, n, preOrderIndex, 0, n - 1);

   return result;
}


//Approach-2: Only when all elements are unique in inorder and preorder
/*Instead of finding element in inorder using iterating in findPosition function, we *can simply create a map and store the mappings of elements to its index and then *position can be found using : map[ele], where ele is the element to be found and *this will return the index of that element
 *   TC: O(N) SC: O(N)
 */

/*-------------------------------------------------------------------------------*/
//Construct Binary Tree from Inorder and Postorder

//Given inorder and postorder traversals of a Binary Tree in the arrays in[] and post[] respectively. The task is to construct the binary tree from these traversals.

int findPosition1 (int in[], int n, int inorderStart, int inorderEnd, int ele)
{
   for (int i = inorderStart; i <= inorderEnd; i++) {
      if (in [i] == ele) {
         return i;
      }
   }
   return -1;
}

Node* makeTree1 (int in[], int post[], int n, int &index, int inorderStart, int inorderEnd)
{
   if (index < 0 || inorderStart > inorderEnd) {
      return NULL;
   }

   int ele = post [index--]; //getting the element for root node
   Node* root = new Node (ele); //creating the root node
   //finding the position for root node in inorder
   int pos = findPosition1 (in, n, inorderStart, inorderEnd, ele);

   //linking the rest of the tree to the root
   root->right = makeTree1 (in, post, n, index, pos + 1, inorderEnd);
   root->left = makeTree1 (in, post, n, index, inorderStart, pos - 1);

   return root;
}


Node *buildTree1 (int in[], int post[], int n)  ////TC: O(N^2)  SC: O(N)
{
   int postOrderIndex = n - 1; //this will be the root of the BT as preorder is -> NLR
   Node* result = makeTree1 (in, post, n, postOrderIndex, 0, n - 1);

   return result;
}


/*-------------------------------------------------------------------------------*/
//Burning Tree / Minimum time to burn a tree
/*
 * Given a binary tree and a node data called target. Find the minimum time required to burn the complete binary tree if the target is set on fire. It is known that in 1 second all nodes connected to a given node get burned. That is its left child, right child, and parent.
 * Note: The tree contains unique values.
 *
 *
 * Example 1:
 *
 * Input:
 *        1
 *      /   \
 *    2      3
 *  /  \      \
 * 4    5      6
 *     / \      \
 *    7   8      9
 \
 \                 10
 \ Target Node = 8
 \ Output: 7
 \ Explanation: If leaf with the value
 \ 8 is set on fire.
 \ After 1 sec: 5 is set on fire.
 \ After 2 sec: 2, 7 are set to fire.
 \ After 3 sec: 4, 1 are set to fire.
 \ After 4 sec: 3 is set to fire.
 \ After 5 sec: 6 is set to fire.
 \ After 6 sec: 9 is set to fire.
 \ After 7 sec: 10 is set to fire.
 \ It takes 7s to burn the complete tree.
 */

// Approach:
// 1 - Create Mapping and find target Node (BFS)
// 2 - Burn the tree
// 3 - Return the answer


// Step-1 : Create Mapping of node to parent using level order traversal and find target Node
Node* createMapping (Node* root, int target, map<Node*, Node*> &nodeToParent)
{
   Node* res = NULL;

   queue<Node*> q;

   q.push (root);

   nodeToParent [root] = NULL;

   while (!q.empty ()) {
      Node* front = q.front ();
      q.pop ();

      if (front->data == target) {
         res = front;
      }

      if (front->left) {
         nodeToParent [front->left] = front;
         q.push (front->left);
      }

      if (front->right) {
         nodeToParent [front->right] = front;
         q.push (front->right);
      }
   }
   return res;
}

//Step-2: Burn The Tree
void burnTree (Node* root, map<Node*, Node*> &nodeToParent, int &ans)
{
   //create a map to store the node to visited mapping
   map<Node*, bool> visited;
   queue<Node*> q;

   q.push (root);
   visited [root] = true;

   while (!q.empty ()) {
      int size = q.size ();
      bool flag = false;

      for (int i = 0; i < size; i++) {
         //process neighbouring nodes
         Node* front = q.front ();
         q.pop ();
         //Three Cases : At a time, a node can have access to three nodes at max
         //left
         if (front->left && !visited [front->left]) {
            q.push (front->left);
            visited [front->left] = true;
            flag = true;
         }

         //right
         if (front->right && !visited [front->right]) {
            q.push (front->right);
            visited [front->right] = true;
            flag = true;
         }

         //parent
         if (nodeToParent [front] && !visited [nodeToParent [front]]) {
            q.push (nodeToParent [front]);
            visited [nodeToParent [front]] = true;
            flag = true;
         }
      }
      //if there is any change in flag, that means one second has been consumed and a node has been burnt
      if (flag) {
         ans++;
      }
   }
}



int minTime (Node* root, int target)
{
   int ans = 0;
   map<Node*, Node*> nodeToParent;
   Node* targetNode = createMapping (root, target, nodeToParent);

   burnTree (targetNode, nodeToParent, ans);
   return ans;
}



/*-------------------------------------------------------------------------------*/
//Morris Traversal
void morrisTraversal (Node* root, vector<int> &traversal)
{
   Node* curr = root;

   while (curr != NULL) {
      if (!curr->left) {
         traversal.push_back (curr->data);
         curr = curr->right;
      }
      else{
         Node* prev = curr->left;
         while (prev->right != NULL && prev->right != curr) {
            prev = prev->right;
         }

         if (!prev->right) {
            prev->right = curr;
            curr = curr->left;
         }

         else{
            prev->right = NULL;
            traversal.push_back (curr->data);
            curr = curr->right;
         }
      }
   }
}

vector<int> inorderTraversal (Node* root)  //TC: O(N)  SC: O(1);
{
   vector<int> traversal;

   morrisTraversal (root, traversal);
   return traversal;
}



/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
//Flatten a Binary Tree to a Linked List
/* Given the root of a binary tree, flatten the tree into a "linked list":
 *
 * The "linked list" should use the same Node class where the right child pointer points to the next   node in the list and the left child pointer is always null.
 * The "linked list" should be in the same order as a pre-order traversal of the binary tree.
 */

//Approach-1: Using Recursion
Node* prevNode = NULL; // global variable

void flatten1 (Node* root) // TC: O(N)  SC: O(N)
{
   if (root == NULL) {
      return;
   }

   flatten1 (root->right);
   flatten1 (root->left);

   root->right = prevNode;
   root->left = NULL;
   prevNode = root;
}


//Approach-2: Using Stack
void flatten2 (Node * root)  //TC: O(N)  SC: O(N)
{
   if (root == NULL) {
      return;
   }

   stack<Node*> st;
   st.push (root);
   while (!st.empty ()) {
      Node* curr = st.top ();
      st.pop ();
      if (curr->right) {
         st.push (curr->right);
      }
      if (curr->left) {
         st.push (curr->left);
      }

      if (!st.empty ()) {
         curr->right = st.top ();
      }
      curr->left = NULL;
   }
}


//Approach-3: Morris Traversal
void flatten3 (Node *root)   //TC: O(N)  SC: O(1)
{
   Node* curr = root;

   while (curr != NULL) {
      if (curr->left) {
         Node* prev = curr->left;
         while (prev->right != NULL) {
            prev = prev->right;
         }

         prev->right = curr->right;
         curr->right = curr->left;
         curr->left = NULL;
      }
      curr = curr->right;
   }
}



/*-------------------------------------------------------------------------------*/






/*-------------------------------------------------------------------------------*/


int main ()
{
   //        1
   //       /   \ 
   //     2       3
   //    / \     / \
   //   4   5   8   9
   //  / \
   // 7   6



   Node * root = new Node (1);

   root->left = new Node (2);
   root->right = new Node (3);
   root->left->left = new Node (4);
   root->left->right = new Node (5);
   root->left->left->right = new Node (6);
   root->left->left->left = new Node (7);
   root->right->left = new Node (8);
   root->right->right = new Node (9);

   inOrderTraversal (root);
}
