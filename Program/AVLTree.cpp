#include "AVLTree.h"

AVLTree::AVLTree()
{
  root=nullptr;
}


//Eπιστροφή του ύψους του κόμβου
int AVLTree::getHeight(AVLTreeNode *n)
{
    if (n!=nullptr)
    {
      return n->height;
    }
    
    return 0;
}



int AVLTree::getBalanceFactor(AVLTreeNode *n)
{
    if (n!=nullptr)
    {
      return getHeight(n->left)-getHeight(n->right);
    }
    
    return 0;
}


//Αριστερή περιστροφή
void AVLTree::leftRotation(AVLTreeNode *&n)
{
    AVLTreeNode *t1=n->right;
    AVLTreeNode *t2=t1->left;

    t1->left=n;
    n->right=t2;

    if(getHeight(n->left)>getHeight(n->right))
    {
        n->height=getHeight(n->left)+1;
    }
    else
    {
       n->height=getHeight(n->right)+1;
    }
    
    if(getHeight(t1->left)>getHeight(t1->right))
    {
      t1->height=getHeight(t1->left)+1;  
    }
    else
    {
       t1->height=getHeight(t1->right)+1; 
    }

    n=t1;
}


//Δεξιά περιστροφή
void AVLTree::rightRotation(AVLTreeNode *&n)
{
    AVLTreeNode *t1=n->left;
    AVLTreeNode *t2=t1->right;

    t1->right=n;
    n->left=t2;

   if(getHeight(n->left)>getHeight(n->right))
    {
        n->height=getHeight(n->left)+1;
    }
    else
    {
       n->height=getHeight(n->right)+1;
    }
    
    if(getHeight(t1->left)>getHeight(t1->right))
    {
      t1->height=getHeight(t1->left)+1;  
    }
    else
    {
       t1->height=getHeight(t1->right)+1; 
    }

    n=t1;
}


//Εύρεση θέσης για εισαγωγή ζεύγους 
void AVLTree::insert(string w1,string w2)
{
    if (root==nullptr)
    {                   /*Απευθείας εισαγωγή κόμβου με στοιχείο το ζεύγος
                        αν το δένρο είναι κενό*/
        root=new (nothrow) AVLTreeNode(w1,w2); 
        if(root==nullptr)
        {
          exit(1); /*Τερματισμός προγράμματος
                  σε περίπτωση αδυναμίας
                  δέσμευσης μνήμης*/
        }
        return;
    }
    
    AVLTreeNode *temp=root;
    
    while(true)
    {
      if(w1<temp->word1 || w1==temp->word1 && w2<temp->word2)
      {
         if(temp->left==nullptr)
         {
             /*Αν το ζεύγος προηγείται λεξικογραφικά του ζεύγους 
              στον υπό εξέταση κόμβο, εισαγωγή
             στο αριστερό υποδένδρο αυτού το κόμβου*/
         
            temp->left=new (nothrow) AVLTreeNode(w1,w2); //Ελεύθερη θέση για εισαγωγή κόμβου
            if(temp->left==nullptr)
            {
               exit(1);
            }
            break;
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
          temp->right=new (nothrow) AVLTreeNode(w1,w2);
          if(temp->right==nullptr)
          {
             exit(1);
          }
          break;
        }
        else //Ο κόμβος έχει δεξί παιδί
        {
          temp=temp->right; //Συνέχεια αναζήτησης στο δεξί υποδένδρο
        }
      }
      else
      {
        temp->count++; //Το ζεύγος ήδη υπάρχει
        return;
      }
          
    }

    /*Ανανέωση του ύψους εισαχθέντος κόμβου 
    και εξισορρόπηση του δένδρου
    αν έχει γίνει εισαγωγή νέου ζεύγους*/
    if(getHeight(temp->left)>getHeight(temp->right))
    {
        temp->height=getHeight(temp->left)+1;
    }
    else
    {
       temp->height=getHeight(temp->right)+1;
    }


    if (getBalanceFactor(root)>1) //To ύψος του αριστερού υποδένδρου είναι μεγαλύτερο από του δεξιού
    {
      if(w1<root->left->word1 || (w1==root->left->word1 && w2<root->left->word2))
       {
         rightRotation(root);   /*To νέο ζεύγος προηγείται λεξικογραφικά του ζεύγους 
                                    στο αριστερό παιδί του κόμβου
                                    άρα θα γίνει απλή δεξιά περιστροφή*/ 
        return;                            
       }
       else if(w1>root->left->word1 || (w1==root->left->word1 && w2>root->left->word2))
       {
          leftRotation(root->left);  /*To νέο ζεύγος έπεται λεξικογραφικά του ζεύγους 
                                            στο αριστερό παιδί του κόμβου
                                           άρα θα γίνει διπλή περιστροφή LR*/ 
          rightRotation(root);
          return;
       }
    }

    if (getBalanceFactor(root)<-1) //To ύψος του δεξιού υποδένδρου είναι μεγαλύτερο από του αριστερού
    { 
        if (w1>root->right->word1 || (w1==root->right->word1 && w2>root->right->word2))
        {
           leftRotation(root);   /*To νέο ζεύγος έπεται λεξικογραφικά του ζεύγους 
                                    στο δεξί παιδί του κόμβου
                                    άρα θα γίνει απλή αριστερή περιστροφή*/
            return;                        
        }
       else if(w1<root->right->word1 || (w1==root->right->word1 && w2<root->right->word2))
       {
         rightRotation(root->right); /*To νέο ζεύγος προηγείται λεξικογραφικά του ζεύγους 
                                            στο δεξί παιδί του κόμβου
                                           άρα θα γίνει διπλή περιστροφή RL*/ 
         leftRotation(root);
         return;
       }
    }
}


//Αναζήτηση ζεύγους στο δένδρο
unsigned int AVLTree::search(string w1,string w2)
{
    AVLTreeNode* temp=root;
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


//Ενδοδιατεταγμένη διάσχιση δένδρου
void AVLTree::traverse()
{
   AVLTreeNode *temp=root;
   AVLTreeNode *predecessor;
   
   while(temp!=nullptr)
   {
       /*Έλεγχος ύπαρξης στοιχείων στο 
        αριστερό υποδένδρο του κόμβου*/
       if(temp->left==nullptr)
                                /*Το αριστερό υποδένδρο του κόμβου 
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
AVLTree::~AVLTree()
{
  while (root!=nullptr) 
    {
        if (root->left==nullptr) 
        {
            AVLTreeNode* temp=root->right;
            delete root;
            root=temp;
        } 
        else 
        {
            AVLTreeNode* predecessor=root->left;
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
                AVLTreeNode* temp=root->right;
                delete root;
                root=temp;
            }
        }
    }
}
