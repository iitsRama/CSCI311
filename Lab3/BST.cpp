// Lab 3 - BST_skeleton.cpp - rename it to BST.cpp
// Author: *** YOUR NAME HERE ***

#include<iostream>
#include <vector>
#include <limits.h>
#include "BST.h"

// ***do not change the headers***

// you solutions go here
// remember that you do not need to implement all of them
// follow the document to see which ones you need to implement

//ASSUME NO DUPLICATE VALUES

BST::BST()
{
  root = nullptr;
  size = 0;
}

BST::~BST(){}

std::shared_ptr<Node> BST::search(int target)
{
  return search(root, target);
}

std::shared_ptr<Node> BST::search(std::shared_ptr<Node> n, int target)
{
  if(n == nullptr) { return nullptr; }

  if(n -> value == target) { return n; }
  else
  {
    if(n -> value > target)
    {
      return search(n -> left, target);
    }
    if(n -> value < target)
    {
      return search(n -> right, target);
    }
  }

  return nullptr;
}

std::shared_ptr<Node> BST::minimum()
{
  return minimum(root);
}

std::shared_ptr<Node> BST::minimum(std::shared_ptr<Node> n)
{
  if(n == nullptr) { return nullptr; }

  while(n -> left != nullptr)
  {
    n = n -> left;
  }

  return n;
}

std::shared_ptr<Node> BST::maximum()
{
  return maximum(root);
}

std::shared_ptr<Node> BST::maximum(std::shared_ptr<Node> n)
{
  if(n == nullptr) { return nullptr; }

  while(n -> right != nullptr)
  {
    n = n -> right;
  }

  return n;
}

void BST::insertValue(int val)
{
  root = insertValue(root, val);
}

std::shared_ptr<Node> BST::insertValue(std::shared_ptr<Node> n, int val)
{
  if(n == nullptr) 
  {
    size++;
    return std::shared_ptr<Node>(new Node(val));
  }

  if(val < n -> value)
  {
    n -> left = insertValue(n -> left, val);
  }
  if(val > n -> value)
  {
    n -> right = insertValue(n -> right, val);
  }

  return n;
}

void BST::deleteValue(int val)
{
  root = deleteValue(root, val);
}

std::shared_ptr<Node> BST::deleteValue(std::shared_ptr<Node> n, int val)
{
  if(n == nullptr) { return nullptr; }

  if(val < n -> value)
  {
    n -> left = deleteValue(n -> left, val);
  }
  else if(val > n -> value)
  {
    n -> right = deleteValue(n -> right, val);
  }
  else if(val == n -> value)
  {
    if(n -> left == nullptr && n -> right == nullptr)
    {
      size--;
      return nullptr;
    }
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
    else
    {
      std::shared_ptr<Node> min = minimum(n -> right);

      n -> value = min -> value;

      n -> right = deleteValue(n -> right, min -> value);
    }
  }

  return n;
}

bool BST::isBST(std::shared_ptr<Node> n)
{
  return isBST(n, INT_MIN, INT_MAX);
}

bool BST::isBST(std::shared_ptr<Node> n, int low, int high)
{
  if(n == nullptr) { return true; }

  if(n -> value <= low || n -> value >= high) { return false; }
  
  return isBST(n -> left, low, n -> value) && isBST(n -> right, n -> value, high);
}

void BST::preOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order)
{
  if(n != nullptr)
  {
    order.push_back(n);
    preOrder(n -> left, order);
    preOrder(n -> right, order);
  }
}

void BST::inOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order)
{
  if(n != nullptr)
  {
    inOrder(n -> left, order);
    order.push_back(n);
    inOrder(n -> right, order);
  }
}

void BST::postOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order)
{
  if(n != nullptr)
  {
    postOrder(n -> left, order);
    postOrder(n -> right, order);
    order.push_back(n);
  }
}
