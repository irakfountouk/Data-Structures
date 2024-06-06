#include "HashTable.h"
#include <iostream>
using namespace std;

HashTable::HashTable()
{
    unsigned int i;
    maxsize=1000;
    data=new (nothrow) HashTablePair[maxsize];
    if(data==nullptr) //Έλεγχος του αν δεσμεύτηκε επιτυχώς μνήμη για τον πίνακα
    {
        exit(1); 
    }
    size=0;
    for(i=0;i<maxsize;i++)
    {
      data[i].empty=true;
    }
}


unsigned int HashTable::getMaxsize()
{
  return maxsize; //Χωρητικότητα του πίνακα
}


unsigned int HashTable::getCurrentSize()
{
  return size; //Τωρινό μέγεθος του πίνακα
}


void HashTable::rehash()
{
    //Αύξηση χωρητικότητας του πίνακα
    unsigned int hashValue,offset,bucket,checksize,i,oldmaxsize;
    checksize=0;
    oldmaxsize=maxsize;
    maxsize*=2;
    HashTablePair *temp=new (nothrow) HashTablePair[maxsize*2];
    
    if(temp==nullptr)
    {
      exit(1);  /*Έξοδος από το πρόγραμμα σε περίπτωση αδυναμίας δέσμευσης μνήμης*/
    }
    
    
    for(i=0;i<maxsize;i++)
    {
        temp[i].empty=true;
    }
    
    
    //Αντιγραφή δεδομένων σε προσωρινό πίνακα
    for (i=0;i<oldmaxsize;i++)
    {
        offset=0;
        if (!data[i].empty)
        {   
            checksize++;
            hashValue=hashFunction(data[i].word1, data[i].word2);
            bucket=(hashValue+offset)%maxsize; //Γραμμική αναζήτηση θέσης ζεύγους στον νέο πίνακα

            while (!temp[bucket].empty)
            {
              offset++;
              bucket=(hashValue+offset)%maxsize;  
              if(bucket>maxsize) //Δε βρέθηκε θέση για εισαγωγή του ζεύγους
              {
                  exit(1);
              }
            }

            temp[bucket]=data[i];
        }
        if(checksize==size) //Όλα τα δεδομένα του πίνακα αντιγράφηκαν
        {
            break;
        }
    }
    delete[] data;
    data=temp;
}


unsigned int HashTable::hashFunction(string w1, string w2)
{
    /*Συνάρτηση κατακερματισμού για εύρεση τιμής κατακερματισμού
      με τη χρήση πολυωνυμικής μεθόδου*/
    string combined;
    unsigned int hashValue,i;
    hashValue=0;
    combined=w1+w2;
    
    for (i=0;i<combined.length();i++)
    {
        hashValue+=static_cast<unsigned int>(combined[i]-'a')*pow(33,i);
        hashValue%=maxsize;
    }
    
    return hashValue%maxsize;
}



double HashTable::getLoadFactor()
{
    return static_cast<double>(size)/maxsize; /*Υπολογισμός συντελεστή πλήρωσης,για να αποφευχθούν
                                                      συγκρούσεις σε περίπτωση 
                                                      κάλυψης όλων των υπάρχουσων θέσεων του πίνακα*/
}


//Εισαγωγή ζεύγους
void HashTable::insert(string w1,string w2)
{
    if (getLoadFactor()>=0.5)
    {
        rehash(); /*Αύξηση μεγέθους του πίνακα αν ο συντελεστής 
                   πλήρωσης είναι μεγαλύτερος του 0.5*/
    }

    unsigned int offset,bucket,hashValue;
    hashValue=hashFunction(w1,w2);
    

    for(offset=0;offset<maxsize;offset++)
    {
      bucket=(hashValue+offset)%maxsize; //Γραμμική αναζήτηση
      if (data[bucket].empty)
      {
        data[bucket].word1=w1;
        data[bucket].word2=w2;
        data[bucket].count=1;
        data[bucket].empty=false;
        size++;
        return;
      }
      else if(data[bucket].word1==w1 && data[bucket].word2==w2) //Το ζεύγος ήδη έχει αποθηκευτεί
      {
        data[bucket].count++;  
        return;
      }
    }
    
    exit(1); //Tο ζεύγος δεν κατάφερε να εισαχθεί
}

int HashTable::search(string w1,string w2)
{
    unsigned int offset,bucket,hashValue;
    hashValue=hashFunction(w1,w2);
    

     for (offset=0;offset<maxsize;offset++)
    {
        bucket=(hashValue+offset)%maxsize; //Γραμμική αναζήτηση 

        if (!data[bucket].empty)
        {
            if(data[bucket].word1==w1 && data[bucket].word2==w2)
            /* Το ζεύγος βρέθηκε
            οπότε επιστρέφεται ο αριθμός εμφανίσεών του*/
            return data[bucket].count;
        }
    }

    return 0;//Το ζεύγος δε βρέθηκε
}


//Προσπέλαση των στοιχείων του πίνακα
void HashTable::traverse()
{
    unsigned int i,checkSize;
    checkSize=0;
    for(i=0;i<maxsize;i++)
    {
        if(!data[i].empty)
        {
            cout<<"Pair ("<<data[i].word1<<","<<data[i].word2<<") is found "<<data[i].count<<" times"<<endl;
            checkSize++;
        }
        if(checkSize==size) //Προσπελάστηκαν όλα τα στοιχεία του  πίνακα
        {
            return;
        }
    }
}


HashTable::~HashTable()
{
    delete[] data;
}
