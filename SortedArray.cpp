#include "SortedArray.h"
#include <fstream>

SortedArray::SortedArray() 
{
  maxsize=100000;
  size=0;
  data=new (nothrow) SortedArrayPair[maxsize];
  if(data==nullptr)
  {
     exit(1); /*Τερματισμός προγράμματος
                σε περίπτωση αδυναμίας
                δέσμευσης μνήμης*/
  }
}


unsigned int SortedArray::getMaxsize()
{
  return maxsize; //Χωρητικότητα του πίνακα
}


unsigned int SortedArray::getCurrentSize()
{
  return size; //Τωρινό μέγεθος του πίνακα
}


//Πρόσβαση σε συγκεκριμένο αποθηκευμένο ζεύγος 
void SortedArray::getPair(int i,string &w1,string &w2)
{
    w1=data[i].word1;
    w2=data[i].word2;
}


void SortedArray::upsize() 
{
    unsigned int i;
    maxsize*=2;
    SortedArrayPair* temp=new (nothrow) SortedArrayPair[maxsize];  /*Αύξηση χωρητικότητας του πίνακα 
                                                                    μέσω της δημιουργίας ενός προσωρινού και 
                                                        αντιγραφής των υπάρχοντων δεδομένων σε αυτόν*/
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


//Εισαγωγή νέου ζεύγους
void SortedArray::insert(string w1,string w2) 
{
    int pos;
    pos=-1;
    
    if(size>0)
    {
      pos=searchPositionOfPair(w1,w2);  
    }
    
    
    if(pos>-1) //Το ζεύγος υπάρχει στον πίνακα
    {
        data[pos].count++;
        return;
    }
    else
    {
        int i,newpos;
        bool newposFound;
        i=size-1;
        newposFound=false; //Έλεγχος του αν το ζεύγος εισήχθη
        
        
       /*Προσπελαση του πίνακα και μετακίνση των στοιχείων 
       των οποίων τουλάχιστον μία από τις w1 ή w2
       μπορεί να προηγείται λεξικογραφικά,
       για να εισαχθεί το νέο ζεύγος άμεσα
       στη σωστή θέση*/
       while(i>=0 && newposFound==false)
       {
         if(data[i].word1>w1||data[i].word1==w1 && data[i].word2>w2)
         {
           data[i+1]=data[i];
           i--;
         }
         else
         {
           newposFound=true;
         }
       }
       data[i+1].word1=w1; //Εισαγωγή του ζεύγους αν δεν υπάρχει ήδη στον πίνακα 
       data[i+1].word2=w2;
       data[i+1].count=1;
       size++;
    }
    

    if (size==maxsize) 
    {
        upsize();
    }
}



/*Αναζήτηση ενός ζεύγους στον πίνακα και 
  επιστροφή του πλήθους εμφανίσεών του 
  με τη μέθοδο της δυαδικής αναζήτησης*/
unsigned int SortedArray::search(string w1,string w2) 
{
    int start,mid,end;
    start=0;
    end=size-1;

    while (start<=end) 
    {
        mid=(start+end)/2;
        if (data[mid].word1==w1 && data[mid].word2==w2) 
        {
          return data[mid].count;
        } 
        else if (data[mid].word1<w1||(data[mid].word1==w1 && data[mid].word2<w2)) 
        {
          start=mid+1;
        } 
        else 
        {
          end=mid-1;
        }
    }

    return 0; //Το ζεύγος δε βρέθηκε
}


/*Αναζήτηση της θέσης ενός ζεύγους στον πίνακα,
  χρήση μόνο εντός της κλάσης*/
  
int SortedArray::searchPositionOfPair(string w1,string w2)
{
    int start,mid,end;
    start=0;
    end=size-1;

    while (start<=end) 
    {
        mid=(start+end)/2;
        if (data[mid].word1==w1 && data[mid].word2==w2) 
        {
          return mid;
        } 
        else if (data[mid].word1<w1||(data[mid].word1==w1 && data[mid].word2<w2)) 
        {
          start=mid+1;
        } 
        else 
        {
          end=mid-1;
        }
    }

    return -1; //Το ζεύγος δε βρέθηκε
}

//Προβολή στοιχείων του πίνακα
void SortedArray::traverse()
{
    unsigned int i;
    for(i=0;i<size;i++)
    {
      cout<<"Ζεύγος στην "<<i<<"η θέση: ("<<data[i].word1<<","<<data[i].word2<<") με "<<data[i].count<<" εμφανίσεις στο κείμενο"<<endl<<endl;
    }
}


SortedArray::~SortedArray() 
{
    delete[] data;
}