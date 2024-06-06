#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "UnsortedArray.h"
#include "SortedArray.h"
#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "HashTable.h"

using namespace std;


//Μετατροπή όλων των γραμμάτων μιας λέξης σε πεζά
string convertToLower(string str)
{
  int i;
  string newString;
  for(i=0;i<str.length();i++)
  {
      if(isalpha(str[i]))
      {
        newString+=tolower(str[i]);
      }
      else if(isdigit(str[i]))
      {
          newString+=str[i];
      }
  }

  return newString;
}



//Έλεγχος του αν ένα string περιέχει μόνο αλφαριθμητικούς χαρακτήρες
bool checkIsAlnum(string &str)
{
  int i;
  string newString;
  for(i=0;i<str.length();i++)
  {
      if(isalnum(str[i]))
      {
        newString+=str[i]; /*Εξασφάλιση του ότι το string δε θα
                           περιέχει άλλους χαρακτήρες (π.χ σημεία στίξης)*/
      }
      else
      {
        break; /*Αν εντοπιστεί χαρακτήρας που δεν είναι αλφαριθμητικός
                 το string έχει ολοκληρωθεί*/
      }
  }
  if(newString.length()>0)
  {
      str=newString; /*Αν το μήκος του newString είναι μεγαλύτερο από 0
                          τότε το string αναπαριστά λέξη
                      και όχι αριθμητικό χαρακτήρα
                       ή σημείο στίξης*/
      return true;
  }
  else
  {
    return false;
  }
}



//Ενιαία δομή για την αποθήκευση των ζευγών
struct Pair
{
  string fileWord1;
  string fileWord2;
};


int main(int argc, char *argv[])
{
    //Διάβασμα δεδομένων από το αρχείο
    ifstream dataFile;
    string word1,word2,inputfile;

    if(argc>1)
    {
        inputfile=argv[1];
    }

    dataFile.open(inputfile,ios::in);
    if (!dataFile.is_open())
    {
        return 1;
    }

    clock_t time_req; //Χρόνος κατασκεύης της δομής

    /*Κατασκευή της κάθε δομής δεδομένων μέσω της
     εισαγωγής ζευγών συνεχόμενων λέξεων από το κείμενο
     και μέτρηση του χρόνου κατασκευής τους*/


    //Κατασκευή μη ταξινομημένου πίνακα
    float UAConstructionTime;
    time_req=clock();

    UnsortedArray* unsortedArray=new UnsortedArray;

    dataFile>>word1;

    while (!dataFile.eof())
    {
       while(!checkIsAlnum(word1))
       {
         word1.clear();
                            /*Εισαγωγή δεδομένων από το κείμενο μέχρι να
                             εξασφαλιστεί ότι το string αναπαριστά λέξη*/
         dataFile>>word1;
       }

       word1=convertToLower(word1);

       dataFile>>word2;

       while(!checkIsAlnum(word2))
       {
         word2.clear();
         dataFile>>word2;
       }

       word2=convertToLower(word2);

       unsortedArray->insert(word1,word2);

       word1=word2; /*Απόδοση της τιμής του word2 στο word1
                    ώστε να αποθηκεύονται τα ζεύγη συνεχόμενων λέξεων*/
    }

    UAConstructionTime=static_cast<float>(clock()-time_req)/CLOCKS_PER_SEC; /*Χρόνος κατασκεύης
                                                                              αταξινόμητου πίνακα*/

    dataFile.close();




    dataFile.open(inputfile,ios::in);
    if (!dataFile.is_open())
    {
      return 1;
    }

    //Κατασκευή ταξινομημένου πίνακα
    float SAConstructionTime;

    time_req=clock();

    SortedArray* sortedArray=new SortedArray;

    dataFile>>word1;

    while (!dataFile.eof())
    {
      while(!checkIsAlnum(word1))
       {
         word1.clear();
         dataFile>>word1;
       }

       word1=convertToLower(word1);

       dataFile>>word2;

       while(!checkIsAlnum(word2))
       {
         word2.clear();
         dataFile>>word2;
       }
       word2=convertToLower(word2);

      sortedArray->insert(word1,word2);

      word1=word2;
    }

    SAConstructionTime=static_cast<float>(clock()-time_req)/CLOCKS_PER_SEC; /*Χρόνος κατασκευής
                                                                             ταξινομημένου πίνακα*/

    dataFile.close();



    dataFile.open(inputfile,ios::in);
    if (!dataFile.is_open())
    {
      return 1;
    }

    //Κατασκευή δυαδικού δένδρου αναζήτησης
    float BSTConstructionTime;

    time_req=clock();

    BinarySearchTree* binarySearchTree=new BinarySearchTree;

    dataFile>>word1;

    while (!dataFile.eof())
    {
       while(!checkIsAlnum(word1))
       {
         word1.clear();
         dataFile>>word1;
       }

       word1=convertToLower(word1);

       dataFile>>word2;

       while(!checkIsAlnum(word2))
       {
         word2.clear();
         dataFile>>word2;
       }
       word2=convertToLower(word2);

      binarySearchTree->insert(word1,word2);

      word1=word2;
    }

    BSTConstructionTime=static_cast<float>(clock()-time_req)/CLOCKS_PER_SEC; /*Χρόνος κατασκευής
                                                                                δυαδικού δένδρου αναζήτησης*/
    dataFile.close();


    dataFile.open(inputfile,ios::in);
    if (!dataFile.is_open()) /*Tερματισμός προγράμματος σε περίπτωση
                                σφάλματος στο άνοιγμα του αρχείου*/
    {
      return 1;
    }

    //Κατασκευή ισοζυγισμένου δυαδικού δένδρου
    float AVLConstructionTime;

    time_req=clock();

    AVLTree* avlTree=new AVLTree;

    dataFile>>word1;

    while (!dataFile.eof())
    {
      while(!checkIsAlnum(word1))
       {
         word1.clear();
         dataFile>>word1;
       }

       word1=convertToLower(word1);

       dataFile>>word2;

       while(!checkIsAlnum(word2))
       {
         word2.clear();
         dataFile>>word2;
       }

       word2=convertToLower(word2);

       avlTree->insert(word1,word2);

       word1=word2;
    }

    AVLConstructionTime=static_cast<float>(clock()-time_req)/CLOCKS_PER_SEC; /*Χρόνος κατασκευής
                                                                                ισοζυγισμένου δυαδικού δένδρου*/

    dataFile.close();


    dataFile.open(inputfile,ios::in);
    if (!dataFile.is_open())
    {
      return 1;
    }
    //Κατασκευή πίνακα κατακερματισμού

    float HTConstructionTime;

    time_req=clock();

    HashTable* hashTable=new HashTable;

    dataFile>>word1;

    while (!dataFile.eof())
    {
      while(!checkIsAlnum(word1))
       {
         word1.clear();
         dataFile>>word1;
       }

       word1=convertToLower(word1);

       dataFile>>word2;

       while(!checkIsAlnum(word2))
       {
         word2.clear();
         dataFile>>word2;
       }

       word2=convertToLower(word2);

       hashTable->insert(word1,word2);

       word1=word2;
    }

    HTConstructionTime=static_cast<float>(clock()-time_req)/CLOCKS_PER_SEC; /*Χρόνος κατασκεύης
                                                                              πίνακα κατακερματισμού*/
    dataFile.close();


    // Εγγραφή των αποτελεσμάτων σε νέο αρχείο
    ofstream outputFile;
    outputFile.open("output.txt",ios::out);
    if (!outputFile.is_open())
    {
        return 1;
    }

    outputFile<<"Χρόνος κατασκευής κάθε δομής:"<<endl<<endl;
    outputFile<<"Ο χρόνος κατασκευής του αταξινόμητου πίνακα ήταν: "<<UAConstructionTime<<" δευτερόλεπτα"<<endl<<endl;
    outputFile<<"Ο χρόνος κατασκευής του ταξινομημένου πίνακα ήταν: "<<SAConstructionTime<<" δευτερόλεπτα"<<endl<<endl;
    outputFile<<"Ο χρόνος κατασκευής του δυαδικού δένδρου αναζήτησης ήταν: "<<BSTConstructionTime<<" δευτερόλεπτα"<<endl<<endl;
    outputFile<<"Ο χρόνος κατασκευής του ισοζυγισμένου δυαδικού δένδρου ήταν: "<<AVLConstructionTime<<" δευτερόλεπτα"<<endl<<endl;
    outputFile<<"Ο χρόνος κατασκευής του πίνακα κατακερματισμού ήταν: "<<HTConstructionTime<<" δευτερόλεπτα"<<endl<<endl;
    outputFile.close();




    /*Σύνολο Q για την αποθήκευση τυχαίων
    ζευγών λέξεων από το κείμενο*/
    srand(time(nullptr));
    int numPairs,pairsRead,i;
    numPairs=1000;
    Pair Q[1000];


    pairsRead=0;

    //Τυχαία επιλογή ζευγών λέξεων από τον αταξινόμητο πίνακα
    while (pairsRead<numPairs)
    {
        i=rand()%unsortedArray->getCurrentSize();
        unsortedArray->getPair(i,Q[pairsRead].fileWord1,Q[pairsRead].fileWord2);
        pairsRead++;
    }



    /*Αναζήτηση σε κάθε δομή για την εύρεση των ζευγών,
      εγγραφή του πλήθους εμφανίσεων,σύμφωνα με την εκάστοτε δομή,
      κάθε ζεύγους στο αρχείο και μέτρηση του χρόνου
      που χρειάστηκε η κάθε μία για την παραγωγή αποτελεσμάτων*/

    int times_appeared;
    outputFile.open("output.txt",ios::out|ios::app);
    if (!outputFile.is_open())
    {
        return 1;
    }
    outputFile<<"Τα αποτελέσματα κάθε δομής για τα τυχαία ζεύγη λέξεων:"<<endl;


    //Αναζήτηση στον αταξινόμητο πίνακα
    float UARunningTime;
    time_req=clock();

    outputFile<<"Πλήθος εμφανίσεων των ακόλουθων ζευγών στο κείμενο σύμφωνα με τον αταξινόμητο πίνακα:"<<endl<<endl;
    for (i=0;i<numPairs;i++)
    {
      times_appeared=unsortedArray->search(Q[i].fileWord1,Q[i].fileWord2);
      outputFile<<"To ζεύγος ("<<Q[i].fileWord1<<","<<Q[i].fileWord2<<") εμφανίζεται: "<<times_appeared<<" φορές"<<endl;
    }
    outputFile<<endl<<endl;

    UARunningTime=static_cast<float>(clock()-time_req)/CLOCKS_PER_SEC; //Χρόνος αναζήτησης στον αταξινόμητο πίνακα




    //Αναζήτηση στον ταξινομημένο πίνακα
    float SARunningTime;
    time_req=clock();

    outputFile<<"Πλήθος εμφανίσεων των ακόλουθων ζευγών στο κείμενο σύμφωνα με τον ταξινομημένο πίνακα:"<<endl<<endl;
    for (i=0;i<numPairs;i++)
    {
      times_appeared=sortedArray->search(Q[i].fileWord1,Q[i].fileWord2);
      outputFile<<"To ζεύγος ("<<Q[i].fileWord1<<","<<Q[i].fileWord2<<") εμφανίζεται: "<<times_appeared<<" φορές"<<endl;
    }
    outputFile<<endl<<endl;

    SARunningTime=static_cast<float>(clock()-time_req)/CLOCKS_PER_SEC; //Χρόνος αναζήτησης στον ταξινομημένο πίνακα




    //Αναζήτηση στο δυαδικό δένδρο
    float BSTRunningTime;
    time_req=clock();

    outputFile<<"Πλήθος εμφανίσεων των ακόλουθων ζευγών στο κείμενο σύμφωνα με το δυαδικό δένδρο αναζήτησης:"<<endl<<endl;
    for (i=0;i<numPairs;i++)
    {
      times_appeared=binarySearchTree->search(Q[i].fileWord1,Q[i].fileWord2);
      outputFile<<"To ζεύγος ("<<Q[i].fileWord1<<","<<Q[i].fileWord2<<") εμφανίζεται: "<<times_appeared<<" φορές"<<endl;
    }
    outputFile<<endl<<endl;

    BSTRunningTime=static_cast<float>(clock()-time_req)/CLOCKS_PER_SEC; //Χρόνος αναζήτησης στο δυαδικό δένδρο




    //Αναζήτηση στο ισοζυγισμένο δένδρο
    float AVLRunningTime;
    time_req=clock();

    outputFile<<"Πλήθος εμφανίσεων των ακόλουθων ζευγών στο κείμενο σύμφωνα με το ισοζυγισμένο δυαδικό δένδρο:"<<endl<<endl;
    for (i=0;i<numPairs;i++)
    {
      times_appeared=avlTree->search(Q[i].fileWord1,Q[i].fileWord2);
      outputFile<<"To ζεύγος ("<<Q[i].fileWord1<<","<<Q[i].fileWord2<<") εμφανίζεται: "<<times_appeared<<" φορές"<<endl;
    }
    outputFile<<endl<<endl;

    AVLRunningTime=static_cast<float>(clock()-time_req)/CLOCKS_PER_SEC; //Χρόνος αναζήτησης στο ισοζυγισμένο δυαδικό δένδρο




    //Αναζήτηση στον πίνακα κατακερματισμού
    float HTRunningime;
    time_req=clock();
    outputFile<<"Πλήθος εμφανίσεων των ακόλουθων ζευγών στο κείμενο σύμφωνα με τον πίνακα κατακερματισμού:"<<endl<<endl;
    for (i=0;i<numPairs;i++)
    {
        times_appeared=hashTable->search(Q[i].fileWord1,Q[i].fileWord2);
        outputFile<<"To ζεύγος ("<<Q[i].fileWord1<<","<<Q[i].fileWord2<<") εμφανίζεται: "<<times_appeared<<" φορές"<<endl;
    }

    float HTRunningTime=static_cast<float>(clock()-time_req)/CLOCKS_PER_SEC; //Χρόνος αναζήτησης στον πίνακα κατακερματισμού




    outputFile<<"Χρόνος που χρειάστηκε κάθε δομή για την αναζήτηση και την εγγραφή των αποτελεσμάτων στο αρχείο:"<<endl;
    outputFile<<"Ο συνολικός χρόνος για τον αταξινόμητο πίνακα ήταν: "<<UARunningTime<<" δευτερόλεπτα"<<endl<<endl;
    outputFile<<"Ο συνολικός χρόνος για τον ταξινομημένο πίνακα ήταν: "<<SARunningTime<<" δευτερόλεπτα"<<endl<<endl;
    outputFile<<"Ο συνολικός χρόνος για το δυαδικό δένδρο αναζήτησης ήταν: "<<BSTRunningTime<<" δευτερόλεπτα"<<endl<<endl;
    outputFile<<"Ο συνολικός χρόνος για το ισοζυγισμένο δυαδικό δένδρο ήταν: "<<AVLRunningTime<<" δευτερόλεπτα"<<endl<<endl;
    outputFile<<"Ο συνολικός χρόνος για τον πίνακα κατακερματισμού ήταν: "<<HTRunningTime<<" δευτερόλεπτα"<<endl<<endl;

    outputFile.close();


    return 0;
}
