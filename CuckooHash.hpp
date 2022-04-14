/*
    Data Structures
    Project Hash: Cuckoo Hashing
    Author: Anthony Lupica <arl127@uakron.edu> 2022

    Header file for a hash table class using the cuckoo hashing technique

    The hash table implements a "celebrity lookup." The last name of a celebrity
    is used as the key to quickly find if any entries in the table are a match.
    Ex.] std::cout << CuckooHash.search("Pitt");
         --> "Brad Pitt"
*/

#ifndef CUCKOOHASH_HPP_INCLUDED
#define CUCKOOHASH_HPP_INCLUDED

#include <string>

using std::string;

// list of prime numbers beginning at 11. Double and round up to nearest prime
const int PRIME_LIST[] = { 11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717 };

class CuckooHash
{
    private:
       
        struct Celebrity 
        {
            string firstName; // value 
            string lastName;  // key 
        };

        int tableSize;            // table size (will use PRIME_LIST for rehash values)
        struct Celebrity* table1; // the primary hash table 
        struct Celebrity* table2; // the secondary "eviction" table 

        int hash1(const string &key); // hash function for table1
        int hash2(const string &key); // hash function for table2

    public: 

        CuckooHash();                                        // default constructor
        CuckooHash(const string &key, const string &value);  // constructor taking an initial key and value 
        ~CuckooHash();                                       // destructor 

        void insert(const string &key, const string &value); // insert method 
         
};

#endif // CUCKOOHASH_HPP_INCLUDED
