#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class AVLTree;

class AVLTreeNode
{
  private:
   string word1;
   string word2;
   unsigned int count; //Μετρητής εμφανίσεων ζεύγους
   int height;
   AVLTreeNode *left,*right; //Παιδιά του κόμβου
   AVLTreeNode()
   {
      
   }
   AVLTreeNode(string w1,string w2)
   {
    word1=w1;
    word2=w2;
    count=1;
    height=1;
    left=nullptr;
    right=nullptr;
   }
  
  friend AVLTree;
};

class AVLTree
{
  private:
   AVLTreeNode *root;
    
   int getHeight(AVLTreeNode *n);
   int getBalanceFactor(AVLTreeNode *n);
   void leftRotation(AVLTreeNode *&n);
   void rightRotation(AVLTreeNode *&n);
   

  public:
    AVLTree();
    ~AVLTree();
    void insert(string w1,string w2);
    unsigned int search(string w1,string w2);
    void traverse();
};

#endif
