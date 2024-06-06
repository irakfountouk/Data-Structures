#ifndef UNSORTEDARRAY_H
#define UNSORTEDARRAY_H

#include <string>
#include <iostream>
using namespace std;

struct UnsortedArrayPair
{
  string word1,word2; //Απόθηκευση ζεύγους λέξεων σε ενιαία δομή
  unsigned int count;  //Μετρητής εμφανίσεων ζεύγους
      
};

class UnsortedArray 
{
  private:
   UnsortedArrayPair *data;
   unsigned int maxsize,size;
   void upsize();
  
   public:
    UnsortedArray();
    ~UnsortedArray();
    unsigned int getMaxsize();
    unsigned int getCurrentSize();
    void getPair(int i,string &w1,string &w2);
    void insert(string w1,string w2);
    unsigned int search(string w1,string w2);
    void traverse();
};

#endif  
