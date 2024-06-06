#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree()
{
    root=nullptr;
}


//Εύρεση θέσης για εισαγωγή ζεύγους μέσω επανάληψης
void BinarySearchTree::insert(string w1,string w2)
{
    if (root==nullptr)
    {                   /*Απευθείας εισαγωγή κόμβου με στοιχείο το ζεύγος
                         αν δεν υπάρχει ήδη στο δέντρο*/
        root=new (nothrow) BinarySearchTreeNode(w1,w2); 
        if(root==nullptr)
        {
          exit(1); /*Τερματισμός προγράμματος
                  σε περίπτωση αδυναμίας
                  δέσμευσης μνήμης*/
        }
        return;
        
    }

    BinarySearchTreeNode *temp=root;
    while(true)
    {
      if(w1<temp->word1 || w1==temp->word1 && w2<temp->word2)
      {
          /*Αν το ζεύγος προηγείται λεξικογραφικά του ζεύγους 
                                      στον υπό εξέταση κόμβο, εισαγωγή
                                      στο αριστερό υποδένδρο αυτού το κόμβου*/
         
         if(temp->left==nullptr) //Ελεύθερη θέση για εισαγωγή κόμβου
         {
            temp->left=new (nothrow) BinarySearchTreeNode(w1,w2);
            if(temp->left==nullptr)
            {
               exit(1);
            }
            return;
         }
         else //Ο κόμβος έχει αριστερό παιδί
         {
          temp=temp->left; //Συνέχεια αναζήτησης στο αριστερό υποδένδρο
         }
      }
      else if(w1>temp->word1 || w1==temp->word1 && w2>temp->word2)
      {
          /*Αν το ζεύγος έπεται λεξικογραφικά του ζεύγους 
            στον υπό εξέταση κόμβο, εισαγωγή
            στο δεξί υποδένδρο αυτού το κόμβου*/
        
        if(temp->right==nullptr) //Ελεύθερη θέση για εισαγωγή κόμβου
        {
          temp->right=new (nothrow) BinarySearchTreeNode(w1,w2);
          if(temp->right==nullptr)
          {
             exit(1);
          }
          return;
        }
        else //Ο κόμβος έχει δεξί παιδί
        {
          temp=temp->right; //Συνέχεια αναζήτησης στο δεξί υποδένδρο
        }
      }
      else
      {
        temp->count++; //Αύξηση του μετρητή εμφανίσεων του ζεύγους, αν υπάρχει ήδη
        return;
      }
          
    }
}



//Αναζήτηση ζεύγους στο δένδρο μέσω επανάληψης
unsigned int BinarySearchTree::search(string w1,string w2)
{
    BinarySearchTreeNode* temp=root;
    while (temp!=nullptr) 
    {
        if (w1<temp->word1 || w1==temp->word1 && w2<temp->word2) 
        {
            /*Αν το ζεύγος προηγείται λεξικογραφικά του ζεύγους 
             στον υπό εξέταση κόμβο, αναζήτηση
            στο αριστερό υποδένδρο αυτού το κόμβου*/
          temp=temp->left;
        } 
        else if (w1>temp->word1 || w1==temp->word1 && w2>temp->word2) 
        {
            /*Αν το ζεύγος έπεται λεξικογραφικά του ζεύγους 
                                              στον υπό εξέταση κόμβο, αναζήτηση
                                              στο δεξί υποδένδρο αυτού το κόμβου*/
          temp=temp->right;
        } 
        else 
        {
          return temp->count; //Το ζεύγος βρέθηκε
        }
    }
    return 0; //Το ζεύγος δε βρέθηκε
}


//Ενδοδιατεταγμένη διάσχιση δένδρου μέσω επανάληψης
void BinarySearchTree::traverse()
{
   BinarySearchTreeNode *temp=root;
   BinarySearchTreeNode *predecessor;
   
   while(temp!=nullptr)
   {
       /*Έλεγχος ύπαρξης στοιχείων στο 
        αριστερό υποδένδρο του κόμβου*/
       if(temp->left==nullptr) /*Το αριστερό υποδένδρο του κόμβου 
                                δεν έχει στοιχεία οπότε
                                προσπελαύνεται ο ίδιος*/
       {
           cout<<"Ζεύγος ("<<temp->word1<<","<<temp->word2<<") με "<<temp->count<<" εμφανίσεις στο κείμενο"<<endl<<endl; 
           temp=temp->right;
       }
       else //Το αριστερό υποδένδρο έχει στοιχεία,οπότε προσπελαύνεται
       {
          predecessor=temp->left;
          //Αναζήτηση προκατόχου
          while (predecessor->right!=nullptr && predecessor->right!=temp) 
          {
            predecessor=predecessor->right;
          }

          if (predecessor->right==nullptr) //Ο προκάτοχος βρέθηκε
          {
             predecessor->right=temp;
             temp=temp->left;
          } 
          else //Έχει ήδη γίνει επίσκεψη του προκατόχου
          {
             predecessor->right=nullptr;
             cout<<"Ζεύγος ("<<temp->word1<<","<<temp->word2<<") με "<<temp->count<<" εμφανίσεις στο κείμενο"<<endl<<endl;
             temp=temp->right; //Διάσχιση του δεξιού υποδένδρου
          }
       }
   }
}


//Καταστροφέας/Διαγραφή δένδρου μέσω ενδοδιατεταγμένης διάσχισης
BinarySearchTree::~BinarySearchTree()
{
    while (root!=nullptr) 
    {
        if (root->left==nullptr) 
        {
            BinarySearchTreeNode* temp=root->right;
            delete root;
            root=temp;
        } 
        else 
        {
            BinarySearchTreeNode* predecessor=root->left;
            while (predecessor->right!=nullptr && predecessor->right!=root) 
            {
                predecessor=predecessor->right;
            }

            if (predecessor->right==nullptr) 
            {
                predecessor->right=root;
                root=root->left;
            } 
            else 
            {
                predecessor->right=nullptr;
                BinarySearchTreeNode* temp=root->right;
                delete root;
                root=temp;
            }
        }
    }
}