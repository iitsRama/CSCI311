// Lab 3 - BST_skeleton.cpp - rename it to BST.cpp
// Author: Amar Bulic 013040249

#include<iostream>
#include <vector>
#include <limits.h>
#include "BST.h"

// ***do not change the headers***

// you solutions go here
// remember that you do not need to implement all of them
// follow the document to see which ones you need to implement

//ASSUME NO DUPLICATE VALUES

// Constructor
BST::BST()
{
  root = nullptr;
  size = 0;
}

// Destructor
BST::~BST(){}

std::shared_ptr<Node> BST::search(int target)
{
  return search(root, target);
}

// Find node containing target value, return node
std::shared_ptr<Node> BST::search(std::shared_ptr<Node> n, int target)
{
  // Base case for recursive call
  if(n == nullptr) { return nullptr; }

  if(n -> value == target) { return n; }
  // If val != target val, recursively comb through both left and right subtrees

  if(n -> value > target)
  {
    return search(n -> left, target);
  }

  if(n -> value < target)
  {
    return search(n -> right, target);
  }

  return nullptr;
}

// Find minimum value in tree
std::shared_ptr<Node> BST::minimum()
{
  return minimum(root);
}

std::shared_ptr<Node> BST::minimum(std::shared_ptr<Node> n)
{
  if(n == nullptr) { return nullptr; }

  // Follow left most path, bottom most left most child is minimum of BSTree
  while(n -> left != nullptr)
  {
    n = n -> left;
  }

  return n;
}

// Find maximum value in tree
std::shared_ptr<Node> BST::maximum()
{
  return maximum(root);
}

std::shared_ptr<Node> BST::maximum(std::shared_ptr<Node> n)
{
  if(n == nullptr) { return nullptr; }

  // Follow right most path, bottom most right most child is maximum of BSTree
  while(n -> right != nullptr)
  {
    n = n -> right;
  }

  return n;
}

// Insert desired value into tree
void BST::insertValue(int val)
{
  if(root == nullptr)
  {
    //size++;
    root = std::shared_ptr<Node>(new Node(val));
  }
  else
  {
    root = insertValue(root, val);
  }
}

std::shared_ptr<Node> BST::insertValue(std::shared_ptr<Node> n, int val)
{
  // if(val < n -> value)
  // {
  //   if(n -> left != nullptr)
  //   {
  //     n -> left = insertValue(n -> left, val);
  //   }
  //   else
  //   {
  //     n -> left = std::shared_ptr<Node>(new Node(val));
  //   }
  // }
  // else if(val > n -> value)
  // {
  //   if(n -> right != nullptr)
  //   {
  //     n -> right = insertValue(n -> right, val);
  //   }
  //   else
  //   {
  //     n -> right = std::shared_ptr<Node>(new Node(val));
  //   }
  // }

  // return n;

  // Recursive base case, when below cases child node is = nullptr, create new node with passed value
  if(n == nullptr) 
  {
    size++;
    return std::shared_ptr<Node>(new Node(val));
  }

  // If val smaller than current nodes value, move to left child node
  if(val < n -> value)
  {
    n -> left = insertValue(n -> left, val);
  }
  // If val larger than current nodes value, move to right child node
  if(val > n -> value)
  {
    n -> right = insertValue(n -> right, val);
  }

  return n;
}

//Delete target value from tree
void BST::deleteValue(int val)
{
  root = deleteValue(root, val);
}

std::shared_ptr<Node> BST::deleteValue(std::shared_ptr<Node> n, int val)
{
  // Recursive base case
  if(n == nullptr) { return nullptr; }

  if(val < n -> value)
  {
    // Recursively check left subtree for value until value found at node
    n -> left = deleteValue(n -> left, val);
  }
  else if(val > n -> value)
  {
    // Recursively check right subtree for value until value found at node
    n -> right = deleteValue(n -> right, val);
  }
  // If value found at node
  else if(val == n -> value)
  {
    // Case 1: No children at node, return nullptr : node = nullptr
    if(n -> left == nullptr && n -> right == nullptr)
    {
      size--;
      return nullptr;
    }
    // Case 2: One child at node, return that child : node = child that exists
    else if(n -> left == nullptr ^ n -> right == nullptr)
    {
      if(n -> left == nullptr)
      {
        size--;
        return n -> right;
      }
      else
      {
        size--;
        return n -> left;
      }
    }
    // Case 3: Two children at node, return minimum value of right subtree : node = subtrees minimum
    else
    {
      // Find min
      std::shared_ptr<Node> min = minimum(n -> right);

      // Set found node.value = min
      n -> value = min -> value;

      // Go back to min value node of right subtree and delete
      n -> right = deleteValue(n -> right, min -> value);
    }
  }

  return n;
}

// Check if tree is BSTree
bool BST::isBST(std::shared_ptr<Node> n)
{
  return isBST(n, INT_MIN, INT_MAX);
}

bool BST::isBST(std::shared_ptr<Node> n, int low, int high)
{
  if(n == nullptr) { return true; }

  // If root node < low value or > high value is not BSTree
  if(n -> value < low || n -> value > high) { return false; }
  
  // Comb through left and right subtrees, if all cases pass return true
  return isBST(n -> left, low, n -> value) && isBST(n -> right, n -> value, high);
}

// Push tree into vector using pre order filing:
// If left child exists, follow and push until min value node reached
// Go back one level and check for right child
// If exists: follow and push towards min node of subtree
// Repeat
void BST::preOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order)
{
  if(n != nullptr)
  {
    order.push_back(n);
    preOrder(n -> left, order);
    preOrder(n -> right, order);
  }
}

// Push tree into vector using in order filing:
// Start at min node
// Push min, push parent, go to min of right child if exists
// Repeat
void BST::inOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order)
{
  if(n != nullptr)
  {
    inOrder(n -> left, order);
    order.push_back(n);
    inOrder(n -> right, order);
  }
}

// Push tree into vector using post order filing: 
// Start at min node
// Push min, go to parent, push right if no subtree, push parent, go up to parent of parent
// If right subtree exists follow steps on subtree
void BST::postOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order)
{
  if(n != nullptr)
  {
    postOrder(n -> left, order);
    postOrder(n -> right, order);
    order.push_back(n);
  }
}
