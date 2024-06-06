#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <cmath>
#include <string>
#include <fstream>
using namespace std;

struct HashTablePair
{
  string word1;
  string word2;
  int count; //Mετρητής εμφανίσεων ζεύγους
  bool empty;
};


class HashTable
{
  private:
    unsigned int maxsize,size;
    HashTablePair *data;
  
    void rehash();
    unsigned int hashFunction(string w1,string w2);
    double getLoadFactor();

  public:
    HashTable();
    ~HashTable();
    unsigned int getMaxsize();
    unsigned int getCurrentSize();
    void insert(string w1,string w2);
    int search(string w1,string w2);
    void traverse();
};

#endif
