/*
    Data Structures
    Project Hash: Cuckoo Hashing
    Author: Anthony Lupica <arl127@uakron.edu> 2022

    Header file for a hash table class using the cuckoo hashing technique

    The hash table implements a celebrity birth-year lookup. The name of a celebrity
    (and non-famous people alike) can be used as the key to quickly find their birth year.
    Ex.] std::cout << CuckooHash.search("Brad Pitt");
         --> "1963"
*/

#ifndef CUCKOOHASH_HPP_INCLUDED
#define CUCKOOHASH_HPP_INCLUDED

#include <string>

using std::string;

// list of prime numbers beginning at 11 for table sizes. Double and round up to nearest prime
const int PRIME_LIST[] = { 11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51481 };

class CuckooHash
{
    private:
       
        struct HashNode 
        {
            string name;   // key 
            int birthYear; // value 
        };

        int tableSize;           // table size (will use PRIME_LIST for rehash values)
        struct HashNode* table1; // the primary hash table 
        struct HashNode* table2; // the secondary "eviction" table 
        int tableSizeCounter;    // keeps track of which index of PRIME_LIST is in use
        int nodeCount;           // keeps track of the number of initialized nodes in the table

        int hash1(const string &key);      // hash function for table1
        int hash2(const string &key);      // hash function for table2
        bool isFourDigit(const int value); // predicate for veryifing a valid birth year         

    public: 

        CuckooHash();                                    // default constructor
        CuckooHash(const string &key, const int value);  // constructor taking an initial key and value 
        ~CuckooHash();                                   // destructor 

        void insert(const string &key, const int value); // insert method 
};

#endif // CUCKOOHASH_HPP_INCLUDED
