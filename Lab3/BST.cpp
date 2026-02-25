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
  int size = 0;
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

  return n;
}

std::shared_ptr<Node> BST::minimum()
{
  return search(root, INT_MIN);
}

std::shared_ptr<Node> BST::minimum(std::shared_ptr<Node> n)
{
  if(n = nullptr) { return nullptr; }

  while(n -> left != nullptr)
  {
    
  }
}

std::shared_ptr<Node> BST::maximum()
{
  return search(root, INT_MAX);
}

std::shared_ptr<Node> BST::maximum(std::shared_ptr<Node> n)
{
  return search(n, INT_MAX);
}

void BST::insertValue(int val)
{
  if(root == nullptr) 
  {
    root = std::shared_ptr<Node>(new Node(val)); 
  }
  else
  {
    root = insertValue(root, val);
  }
}

std::shared_ptr<Node> BST::insertValue(std::shared_ptr<Node> n, int val)
{
  if(val < n -> value)
  {
    if(n -> left != nullptr)
    {
      n -> left = insertValue(n -> left, val);
    }
    else
    {
      n -> left = std::shared_ptr<Node>(new Node(val));
    }
  }
  else if(val > n -> value)
  {
    if(n -> right != nullptr)
    {
      n -> right = insertValue(n -> right, val);
    }
    else
    {
      n -> right = std::shared_ptr<Node>(new Node(val));
    }
  }

  return n;
}

void BST::deleteValue(int val)
{
  deleteValue(root, val);
}

std::shared_ptr<Node> BST::deleteValue(std::shared_ptr<Node> n, int val)
{
  if(n == nullptr) { return nullptr; }

  std::shared_ptr<Node> destination = search(n, val);

  if(destination == nullptr) { return n; }

  if(destination -> left == nullptr && destination -> right == nullptr)
  {
    destination = nullptr;
  }
  else if(destination -> left == nullptr ^ destination -> right == nullptr)
  {
    if(destination -> left == nullptr)
    {
      destination = destination -> right;
    }
    else
    {
      destination = destination -> left;
    }
  }
  else
  {
    std::shared_ptr<Node> min = minimum(destination -> right);

    destination -> value = min -> value;

    min = nullptr;
  }

  return n;
}

bool BST::isBST(std::shared_ptr<Node> n)
{
  if(n == nullptr) { return true; }

  std::shared_ptr<Node> low = minimum(n);
  std::shared_ptr<Node> high = maximum(n);

  return isBST(n, low -> value, high -> value);
}

bool BST::isBST(std::shared_ptr<Node> n, int low, int high)
{
  if(n == nullptr) { return true; }

  if(n -> value < low || n -> value > high) { return false; }
  
  return isBST(n -> left, low, n -> value) && isBST(n -> right, n -> value, high);
}

void BST::preOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order)
{
  if(n != nullptr)
  {
    std::cout << n -> value << std::endl;
    preOrder(n -> left, order);
    preOrder(n -> right, order);
  }
}

void BST::inOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order)
{
  if(n != nullptr)
  {
    inOrder(n -> left, order);
    std::cout << n -> value << std::endl;
    inOrder(n -> right, order);
  }
}

void BST::postOrder(std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> &order)
{
  if(n != nullptr)
  {
    postOrder(n -> left, order);
    postOrder(n -> right, order);
    std::cout << n -> value << std::endl;
  }
}
