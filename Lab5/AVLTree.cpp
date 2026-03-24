// Lab 5 Skeleton - rename it to "AVLTree.cpp"

#include "AVLTree.h"
#include <iostream>
#include <limits.h>
using namespace std;

// do not change anything in the above
// implement the following methods, starting here, do not add new functions

AVLTree::AVLTree()
{
  root = nullptr;
  size = 0;
}

std::shared_ptr<AVLNode> AVLTree::getRoot()
{
  return root;
}

int AVLTree::getSize()
{
  return size;
}

std::shared_ptr<AVLNode> AVLTree::search(int val)
{
  return search(root, val);
}

std::shared_ptr<AVLNode> AVLTree::search(std::shared_ptr<AVLNode> n, int val)
{
  if(n == nullptr) { return nullptr; }
  if(n -> value == val) { return n; }

  if(val <= n -> value)
  {
    return search(n -> left, val); 
  }
  else
  {
    return search(n -> right, val);
  }

  return nullptr;
}

std::shared_ptr<AVLNode> AVLTree::minimum()
{
  return minimum(root);
}

std::shared_ptr<AVLNode> AVLTree::minimum(std::shared_ptr<AVLNode> n)
{
  if(n == nullptr) { return nullptr; }

  if(n -> left == nullptr) { return n; }
  else
  {
    return minimum(n -> left);
  }

  return nullptr;
}

std::shared_ptr<AVLNode> AVLTree::maximum()
{
  return maximum(root);
}

std::shared_ptr<AVLNode> AVLTree::maximum(std::shared_ptr<AVLNode> n)
{
  if(n == nullptr) { return nullptr; }

  if(n -> right == nullptr) { return n; }
  else
  {
    return maximum(n -> right);
  }

  return nullptr;
}

int getHeight(std::shared_ptr<AVLNode> n)
{
  if(n != nullptr)
  {
    return n -> height;
  }
  else
  {
    return -1;
  }
}

int getBalanceFactor(std::shared_ptr<AVLNode> n)
{
  return getHeight(n -> right) - getHeight(n -> left);
}

void updateHeightandBF(std::shared_ptr<AVLNode> n)
{
  if(n == nullptr) { return; }

  int left = getHeight(n -> left);
  int right = getHeight(n -> right);

  n -> height = max(left, right) + 1;

  n -> balanceFactor = right - left;
}

void AVLTree::insertValue(int val)
{
  insertValue(root, val);
}

std::shared_ptr<AVLNode> AVLTree::insertValue(std::shared_ptr<AVLNode> n, int val)
{
  if(n == nullptr)
  {
    n = make_shared<AVLNode>(val);
  }

  if(val <= n -> value)
  {
    n -> left = insertValue(n -> left, val);
  }
  else
  {
    n -> right = insertValue(n -> right, val);
  }

  updateHeightandBF(n);
  
  return rebalance(n);
}

void AVLTree::deleteValue(int val)
{
  deleteValue(root, val);
}

std::shared_ptr<AVLNode> AVLTree::deleteValue(std::shared_ptr<AVLNode> n, int val)
{
  if(val < n -> value)
  {
    n -> left = deleteValue(n -> left, val);
    updateHeightandBF(n);
  }
  else if(val > n -> value)
  {
    n -> right = deleteValue(n -> right, val);
    updateHeightandBF(n);
  }

  if(val == n -> value)
  {
    size--;
    // No children
    if(!(n -> right && n -> left))
    {
      return nullptr; 
    }
    // One child
    else if(n -> right == nullptr ^ n -> left == nullptr)
    {
      if(n -> right)
      {
        return n -> right;
      }
      else
      {
        return n -> left;
      }
    }
    // Two children
    else
    {
      std::shared_ptr<AVLNode> min = minimum(n -> right);
      n -> value = min -> value;
      n -> right = deleteValue(n -> right, min -> value);
    }
  }

  //REBALANCE
  updateHeightandBF(n);
  return rebalance(n);
}

std::shared_ptr<AVLNode> AVLTree::rebalance(std::shared_ptr<AVLNode> n)
{
  // Check for height and balance factor, if statements
  // while abs(balancefactor != 2) iterate?
  // or let balance factor calculate for all nodes so we know if root is left or right heavy?
  
  int bf = n -> balanceFactor;
  int bfLeft = 0;
  int bfRight = 0;
  if(n -> left)
  {
    bfLeft = n -> left -> balanceFactor;
  }

  if(n -> right)
  {
    bfRight = n -> right -> balanceFactor;
  }

  if(abs(bf) == 2)
  {
    if(bf < -1)
    {
      if(bfLeft <= 0)
      {
        n = rotateRight(n);
      }
      else
      {
        n = rotateLeftRight(n);
      }
    }
    
    if(bf > 1)
    {
      if(bfLeft >= 0)
      {
        n = rotateLeft(n);
      }
      else
      {
        n = rotateRightLeft(n);
      }
    }
  }

  return n;
}

std::shared_ptr<AVLNode> AVLTree::rotateLeft(std::shared_ptr<AVLNode> n)
{
  std::shared_ptr<AVLNode> x = n -> right;
  n -> right = x -> left;
  updateHeightandBF(n);
  x -> left = n;
  updateHeightandBF(x);
  return x;
}

std::shared_ptr<AVLNode> AVLTree::rotateRight(std::shared_ptr<AVLNode> n)
{
  std::shared_ptr<AVLNode> x = n -> left;
  n -> left = x -> right;
  updateHeightandBF(n);
  x -> right = n;
  updateHeightandBF(x);
  return x;
}

std::shared_ptr<AVLNode> AVLTree::rotateLeftRight(std::shared_ptr<AVLNode> n)
{
  // call rotate left on left child then rotate right
  rotateLeft(n -> left);
  rotateRight(n);
  return n;
}

std::shared_ptr<AVLNode> AVLTree::rotateRightLeft(std::shared_ptr<AVLNode> n)
{
  // call rotate right on right child, then rotate left
  rotateRight(n -> right);
  rotateLeft(n);
  return n;
}

void AVLTree::preOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>> &order)
{
  if(n != nullptr)
  {
    order.push_back(n);
    preOrder(n -> left, order);
    preOrder(n -> right, order);
  }
}

void AVLTree::inOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>> &order)
{
  if(n != nullptr)
  {
    preOrder(n -> left, order);
    order.push_back(n);
    preOrder(n -> right, order);
  }
}

void AVLTree::postOrder(std::shared_ptr<AVLNode> n, vector<std::shared_ptr<AVLNode>> &order)
{
  if(n != nullptr)
  {
    preOrder(n -> left, order);
    preOrder(n -> right, order);
    order.push_back(n);
  }
}
