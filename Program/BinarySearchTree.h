#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class BinarySearchTree;

class BinarySearchTreeNode
{
  private:
   string word1;
   string word2;
   unsigned int count; //Μετρητής εμφανίσεων ζεύγους
   BinarySearchTreeNode *left,*right; //Παιδιά του κόμβου
   BinarySearchTreeNode()
   {
      
   }
   BinarySearchTreeNode(string w1,string w2)
   {
    word1=w1;
    word2=w2;
    count=1;
    left=nullptr;
    right=nullptr;
   }
  
  friend BinarySearchTree;
};


class BinarySearchTree
{
  private:
    BinarySearchTreeNode *root;
    

  public:
    BinarySearchTree();
    ~BinarySearchTree();
    void insert(string w1,string w2);
    unsigned int search(string w1,string w2);
    void traverse();
};

#endif
