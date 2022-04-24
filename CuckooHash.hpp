/*
    Data Structures
    Project Hash: Cuckoo Hashing
    Author: Anthony Lupica <arl127@uakron.edu> 2022

    Header file for a hash table class using the cuckoo hashing technique.

    The hash table implements a name - year pair lookup. The name of a person 
    can be used as the key to quickly find an associated year.
    
    Ex.] Birth Year
    std::cout << CuckooHash.search("Brad Pitt");
        --> "1963"
    
    The user may decide which logical assiocation to use between names and years.
*/

#ifndef CUCKOOHASH_HPP_INCLUDED
#define CUCKOOHASH_HPP_INCLUDED

#include <string>

using std::string;

// the defined size declarator for PRIME_LIST (increase or decrease when adding or removing elements from PRIME_LIST)
const int LENGTH_PRIME = 13; 

// list of prime numbers beginning at 11 for table sizes. Double and round up to nearest prime
const int PRIME_LIST[LENGTH_PRIME] = { 11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51481 };

class CuckooHash
{
    private:
       
        struct HashNode 
        {
            string name; // key 
            int year;    // value 
        };

        int tableSize;               // table size (will use PRIME_LIST for rehash values)
        struct HashNode* table1;     // the primary hash table 
        struct HashNode* table2;     // the secondary "eviction" table 
        int tableSizeCounter;        // keeps track of which index of PRIME_LIST is in use (for rehash())
        int nodeCount1;              // keeps track of the number of initialized nodes in table1
        int nodeCount2;              // keeps track of the number of initialized nodes in table2
        struct HashNode* tempTable1; // tempTable for rehash() 
        struct HashNode* tempTable2; // tempTable for rehash() 

        int hash1(const string &key);                                        // hash function for table1
        int hash2(const string &key);                                        // hash function for table2
        bool isFourDigit(const int value);                                   // predicate for veryifing a valid birth year 
        void evictToOne(const string &key, const int value, int staticPass); // finds evicted records a new home in table 1 
        void evictToTwo(const string &key, const int value, int staticPass); // finds evicted records a new home in table 2
        bool rehash();                                                       // rehash method to increase the tableSize;
        int position(const string &key, int &whichTable);                    // helper for delete(). Returns the index of a found record
        void insert(const string &key, const int value, int signal);         // overloaded insert() for rehash()
        void evictToOne(const string &key, const int value);                 // overloaded evictToOne() for rehash()
        void evictToTwo(const string &key, const int value);                 // overloaded evictToTwo() for rehash()

    public: 

        CuckooHash();                                    // default constructor
        CuckooHash(const string &key, const int value);  // constructor taking an initial key - value pair
        ~CuckooHash();                                   // destructor 

        void insert(const string &key, const int value); // insert method 
        int search(const string &key);                   // search method
        void remove(const string &key);                  // remove method 
        bool contains(const string &key);                // contains method    
        int size() const                                 // getter for the number of records (in table1 + in table2)
        { return nodeCount1 + nodeCount2; }   
        void display() const;                            // display the hash table  
};

#endif // CUCKOOHASH_HPP_INCLUDED
