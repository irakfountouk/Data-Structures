#include "UnsortedArray.h"
#include <fstream>

UnsortedArray::UnsortedArray() 
{
  maxsize=100000;
  size=0;
  data=new (nothrow) UnsortedArrayPair[maxsize];
  if(data==nullptr)
  {
     exit(1); /*Τερματισμός προγράμματος
                σε περίπτωση αδυναμίας
                δέσμευσης μνήμης*/
  }
}


unsigned int UnsortedArray::getMaxsize()
{
  return maxsize; //Χωρητικότητα του πίνακα
}


unsigned int UnsortedArray::getCurrentSize()
{
  return size; //Τωρινό μέγεθος του πίνακα
}


void UnsortedArray::upsize() 
{
  unsigned int i; 
  maxsize*=2;                 /*Αύξηση χωρητικότητας του πίνακα 
                                  μέσω της δημιουργίας ενός προσωρινού και 
                                  αντιγραφής των υπάρχοντων δεδομένων σε αυτόν*/
  UnsortedArrayPair* temp=new (nothrow) UnsortedArrayPair[maxsize];
  if(temp==nullptr)
  {
     exit(1);
  }
  for (i=0;i<size;i++) 
  {
    temp[i]=data[i];
  }
    
  delete[] data;
  data=temp;
}


//Πρόσβαση σε συγκεκριμένο αποθηκευμένο ζεύγος 
void UnsortedArray::getPair(int i,string &w1,string &w2)
{
    w1=data[i].word1;
    w2=data[i].word2;
}


//Εισαγωγή νέου ζεύγους
void UnsortedArray::insert(string w1,string w2) 
{
  unsigned int i;
  bool found;
  found=false;
  
  for (i=0;i<size && found==false;i++) 
  {
    if (data[i].word1==w1 && data[i].word2==w2) 
    {
      data[i].count++;  /*Αύξηση του μετρητή εμφανίσεων 
                          αν το ζεύγος υπάρχει ήδη στον πίνακα*/
      found=true;
    }
  }
      
  if (size==maxsize) 
  {
     upsize(); //Έγκαιρη αύξηση χωρητικότητας του πίνακα
  }
  
  if(found==false)
  {
    data[size].word1=w1;  /*Το ζεύγος δε βρέθηκε στον πίνακα 
                           οπότε θα γίνει εισαγωγή του*/
    data[size].word2=w2;
    data[size].count=1;
    size++;
  }
    
}


/*Αναζήτηση ενός ζεύγους στον πίνακα 
και επιστροφή του πλήθους εμφανίσεων του*/
unsigned int UnsortedArray::search(string w1,string w2) 
{
    unsigned int i;
    for (i=0;i<size;i++) 
    {
        if (data[i].word1==w1 && data[i].word2==w2) 
        {
          return data[i].count;
        }
    }
    return 0; //Το ζεύγος δε βρέθηκε
}


//Προβολή στοιχείων του πίνακα
void UnsortedArray::traverse()
{
    unsigned int i;
    for(i=0;i<size;i++)
    {
      cout<<"Ζεύγος στην "<<i<<"η θέση: ("<<data[i].word1<<","<<data[i].word2<<") με "<<data[i].count<<" εμφανίσεις στο κείμενο"<<endl<<endl;
    }
}

UnsortedArray::~UnsortedArray() 
{
    delete[] data;
}
