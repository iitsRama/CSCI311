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
  std::shared_ptr<Node> copy = root;

  if(copy == nullptr) { return nullptr; }
  if(copy -> value == target) { return copy; }
  else
  {
    return search(copy -> right, target);
  }

  return nullptr;
}

std::shared_ptr<Node> BST::search(std::shared_ptr<Node> n, int target)
{
  std::shared_ptr<Node> copy = n;

  if(copy == nullptr) { return nullptr; }
  if(copy -> value == target) { return copy; }
  else
  {
    if(copy -> value > target)
    {
      return search(copy -> left, target);
    }
    if(copy -> value < target)
    {
      return search(copy -> right, target);
    }
  }

  return copy;
}

std::shared_ptr<Node> BST::minimum()
{
  std::shared_ptr<Node> min = search(root, INT_MIN);

  return min;
}

std::shared_ptr<Node> BST::minimum(std::shared_ptr<Node> n)
{
  std::shared_ptr<Node> min = search(n, INT_MIN);

  return min;
}

std::shared_ptr<Node> BST::maximum()
{
  std::shared_ptr<Node> max = search(root, INT_MAX);

  return max;
}

std::shared_ptr<Node> BST::maximum(std::shared_ptr<Node> n)
{
  std::shared_ptr<Node> max = search(n, INT_MAX);

  return max;
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

}

std::shared_ptr<Node> BST::deleteValue(std::shared_ptr<Node> n, int val)
{

  return nullptr;
}

bool BST::isBST(std::shared_ptr<Node> n)
{

  return false;
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
