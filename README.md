*The code comments are in Greek.

*Η main δέχεται το όνομα του όποιου αρχείου εισόδου μέσω των ορισμάτων της. Κατά την εκτέλεση της εργασίας θα πρέπει να περάσετε το όνομα του αρχείου που θέλετε στο command line argument

Μain accepts the name of any input file via its arguments. When running the task you should pass the name of the file you want in the command line argument

*The structures implemented in the context of this work are:
A) The Unsorted array via the UnsortedArray class, to store pairs of words that will be accepted by the main program and their number of occurrences in the input text in an array of type pairs, in the order that each is accepted.

This particular structure has the advantage of the fastest insertion time of each pair [O(1)], but also the disadvantage of the slowest estimated search time of it [O(n)].

B) The sorted array through the SortedArray class, to store pairs of words and their number of occurrences in the input text, in ascending order (lexicographically), with the aim of efficient searching, when the structure is called to search for pairs of words.
This particular structure has the disadvantage of the slowest insertion time of each pair (up to [O(n)]), but also the advantage of one of the fastest estimated search times [O(logn)].

C) The simple binary search tree, through the BinarySearchTree class, to store each pair of words in the structure in lexicographic order, since each pair inserted after the root will be part of either the left subtree, if it lexically precedes the pair at the root, or right, if it follows this one. The same applies to the pairs of nodes that will not be children of the root of the tree, but children of the root of a subtree. The structure guarantees that searching for pairs of words in it will complete much faster than searching in an unsorted structure, since the number of comparisons of each pair under consideration with the pairs of other nodes will be as limited as possible.

The estimated time to insert and search a pair in the structure is O(logn).

D) The balanced binary search tree, via the AVLTree class, to store each pair of words in the structure in lexicographic order, since each pair inserted after the root will be part of either the left subtree, if it lexically precedes the root pair, or right, if it follows this one. The same applies to the pairs of nodes that will not be children of the root of the tree, but children of the root of a subtree. The structure guarantees that searching for pairs of words in it will complete much faster than searching in an unsorted structure, since the number of comparisons of each pair under consideration with the pairs of other nodes will be as limited as possible. At the same time, it optimizes binary tree searching, since limiting the height difference between left and right subtrees to one unit guarantees that the nodes will be better distributed. Thus, the number of comparisons in each subtree is limited, without the time spent in one of them being significantly different from the search in the other.

The estimated time to insert and search a pair in the structure is O(logn).

E) The open addressable hash table is implemented through the HashTable class to store word pairs and their occurrence count in the structure using polynomial hash function and linear search to avoid collisions.
The estimated insertion and search time is O(1).
