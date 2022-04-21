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
*  Initialize tableSize to the first value in PRIME_LIST. 
*  When a rehash is necessary, the tableSize
*  will use the next value (doubled and rounded up to the nearest
*  prime number).
*/
CuckooHash::CuckooHash() : tableSize(PRIME_LIST[0]), tableSizeCounter(0), nodeCount(0)
{
    std::cout << "Default constructor was called\n";
    table1 = new HashNode[tableSize];
    table2 = new HashNode[tableSize];
}

/* key-value Constructor 
*
*  Initialize tableSize to the first value in PRIME_LIST. 
*  When a rehash is necessary, the tableSize
*  will use the next value (doubled and rounded up to the nearest
*  prime number). Take in an intital key and value.
*/
CuckooHash::CuckooHash(const string &key, const int value) : tableSize(PRIME_LIST[0]), tableSizeCounter(0), nodeCount(0)
{
    std::cout << "key-value constructor was called\n";
    table1 = new HashNode[tableSize];
    table2 = new HashNode[tableSize];

    // call insert with given key and value
    insert(key, value);
}

// Destructor
CuckooHash::~CuckooHash()
{
    std::cout << "destructor was called\n";
    delete[] table1;
    delete[] table2;
}

void CuckooHash::insert(const string &key, const int value)
{
    if (isFourDigit(value))
    {
        int position1 = hash1(key); // position found for the first table 
        
        // try to insert at that spot 
    }
    else
    {
        std::cerr << "The birth year provided must be four digits\n";
    }

    return;
}

/* hash1 
*
*  hash function for table 1 
*/
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

/* hash2 
*
*  hash function for table 2
*/
int CuckooHash::hash2(const string &key)
{
    // iterate through the string and find a hash value according 
    // to character ascii values (dependent on their position i within the string)
    
    int hashTotal = 0; 
    int mult = 31;              
    for (int i = 0; i < key.length(); ++i)
    {    
        hashTotal += mult * (key[i] + i);
    }

    return hashTotal % tableSize;
}

/* isFourDigit()
*
*  in a loop, divides by ten until the value is 0,
*  each iteration incrementing a counter.
*  Ex.] 1234 / 10 = 123    (++numDigits)
*        123 / 10 = 12     (++numDigits)
*         12 / 10 = 1      (++numDigits)
*          1 / 10 = 0      (++numDigits)
*          end loop
*  If numDigits is anything other than 4, isFourDigit returns 0,
*  and otherwise returns 1.
*/        
bool CuckooHash::isFourDigit(const int value)
{
    int numDigits = 0;
    int tempValue = value;
    while (tempValue != 0)
    {
        tempValue /= 10;
        ++numDigits;
    }
    
    if (numDigits == 4)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


