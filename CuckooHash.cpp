/*
    Data Structures
    Project Hash: Cuckoo Hashing
    Author: Anthony Lupica <arl127@uakron.edu> 2022

    Implementation file for a hash table class using the cuckoo hashing technique

    The hash table implements a celebrity birth-year lookup. The name of a celebrity
    (and non-famous people alike) can be used as the key to quickly find their birth year.
    Ex.] std::cout << CuckooHash.search("Brad Pitt");
         --> "1963"
*/

#include "CuckooHash.hpp"
#include <iostream>

/* Default Constructor 
*
*  Initialize tableSize to 11. 
*  When a rehash is necessary, the tableSize
*  will be doubled, and rounded up to the nearest
*  prime number.
*/

CuckooHash::CuckooHash() : tableSize(PRIME_LIST[0])
{
    std::cout << "Default constructor was called";
    table1 = new HashNode[tableSize];
    table2 = new HashNode[tableSize];
}

CuckooHash::CuckooHash(const string &key, const int value) : tableSize(PRIME_LIST[0])
{
    std::cout << "key-value constructor was called";
    table1 = new HashNode[tableSize];
    table2 = new HashNode[tableSize];
}

CuckooHash::~CuckooHash()
{
    std::cout << "destructor was called";
    delete[] table1;
    delete[] table2;
}

void CuckooHash::insert(const string &key, const int value)
 {
    int index1 = hash1(key);
    int index2 = hash2(key);

    if (table1[index1].name.empty())
     {
        std::cout << " it was empty";
     } 

    // the hash location is occupied
    if (!table1[index1].name.empty())
    {
        // save the key and value 
        string evicteeKey = table1[index1].name;
        int evicteeValue = table1[index1].birthYear;

        // insert new occupant 
        table1[index1].name = key;
        table1[index1].birthYear = value;
    }
    else 
    {
        table1[index1] = {key, value};
    }


     std::cout << table1[index1].birthYear << " " << table1[index1].name;
}

int CuckooHash::hash1(const string &key)
 {
     // iterate through the string and find a hash value according 
     // to character ascii values (dependent on their position i within the string)
     
     int hashTotal = 0; 
     int mult = 29;              
     for (int i = 0; i < key.length(); ++i)
     {   
         mult += i; 
         hashTotal += key[i] * mult;
     }

     return hashTotal % tableSize;
 }

 int CuckooHash::hash2(const string &key)
 {
     // iterate through the string and find a hash value according 
     // to character ascii values (dependent on their position i within the string)
     
     int hashTotal = 0; 
     int mult = 29;              
     for (int i = 0; i < key.length(); ++i)
     {    
         hashTotal += mult * (key[i] + i);
     }

     return hashTotal % tableSize;
}


