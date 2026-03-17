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
  return n -> height;
}

int getBalanceFactor(std::shared_ptr<AVLNode> n)
{
  return n -> balanceFactor;
}

void AVLTree::insertValue(int val)
{
  insertValue(root, val);
}

std::shared_ptr<AVLNode> AVLTree::insertValue(std::shared_ptr<AVLNode> n, int val)
{
  if(n == nullptr){
    n = make_shared<AVLNode>(val);
  }
  else if(val <= n -> value)
  {
    return insertValue(n -> left, val);
  }
  else if(val > n -> value)
  {
    return insertValue(n -> right, val);
  }
  return n;
}

void AVLTree::deleteValue(int val)
{
}

std::shared_ptr<AVLNode> AVLTree::deleteValue(std::shared_ptr<AVLNode> n,
                                              int val)
{
  return nullptr;
}

std::shared_ptr<AVLNode> AVLTree::rebalance(std::shared_ptr<AVLNode> n)
{
  return nullptr;
}

std::shared_ptr<AVLNode> AVLTree::rotateLeft(std::shared_ptr<AVLNode> n)
{
  return nullptr;
}

std::shared_ptr<AVLNode> AVLTree::rotateRight(std::shared_ptr<AVLNode> n)
{
  return nullptr;
}

std::shared_ptr<AVLNode> AVLTree::rotateLeftRight(std::shared_ptr<AVLNode> n)
{
  return nullptr;
}

std::shared_ptr<AVLNode> AVLTree::rotateRightLeft(std::shared_ptr<AVLNode> n)
{
  return nullptr;
}

void AVLTree::preOrder(std::shared_ptr<AVLNode> n,
                       vector<std::shared_ptr<AVLNode>> &order)
{
}

void AVLTree::inOrder(std::shared_ptr<AVLNode> n,
                      vector<std::shared_ptr<AVLNode>> &order)
{
}

void AVLTree::postOrder(std::shared_ptr<AVLNode> n,
                        vector<std::shared_ptr<AVLNode>> &order)
{
}
