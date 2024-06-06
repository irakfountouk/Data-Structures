    #ifndef SORTEDARRAY_H
    #define SORTEDARRAY_H
    
    #include <iostream>
    #include <string>
    using namespace std;
    
    struct SortedArrayPair 
    {
      string word1,word2; //Απόθηκευση ζεύγους λέξεων σε ενιαία δομή
      unsigned int count; //Μετρητής εμφανίσεων ζεύγους
    };
    
    class SortedArray 
    {
      private:
        unsigned int maxsize,size;    //Πίνακας αποθήκευσης ζευγών λέξεων σε αύξουσα σειρά 
        SortedArrayPair* data;
        void upsize();
        int searchPositionOfPair(string w1,string w2);
    
      public:
        SortedArray();
        ~SortedArray();
        unsigned int getMaxsize();
        unsigned int getCurrentSize();
        void getPair(int i,string &w1,string &w2);
        void insert(string w1,string w2);
        unsigned int search(string w1,string w2);
        void traverse();
    };
    
    #endif
