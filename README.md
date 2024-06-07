*The code comments are in Greek.

*Μain accepts the name of any input file via its arguments. When running the task you should pass the name of the file you want in the command line argument.

*The structures implemented in the context of this work are:
A) The Unsorted array via the UnsortedArray class.
This particular structure has the advantage of the fastest insertion time of each pair [O(1)], but also the disadvantage of the slowest estimated search time of it [O(n)].

B) The sorted array through the SortedArray class.
This particular structure has the disadvantage of the slowest insertion time of each pair (up to [O(n)]), but also the advantage of one of the fastest estimated search times [O(logn)].

C) The simple binary search tree, through the BinarySearchTree class
The estimated time to insert and search a pair in the structure is O(logn).

D) The balanced binary search tree, via the AVLTree class.

The estimated time to insert and search a pair in the structure is O(logn).

E) The open addressable hash table is implemented through the HashTable class to store word pairs and their occurrence count in the structure using polynomial hash function and linear search to avoid collisions.
The estimated insertion and search time is O(1).
