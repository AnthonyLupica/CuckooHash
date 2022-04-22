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
#include <cmath> 

/* Default Constructor 
*
*  Initialize tableSize to the first value in PRIME_LIST. 
*  When a rehash is necessary, the tableSize
*  will use the next value in PRIME_LIST (doubled and rounded up to the nearest
*  prime number).
*/
CuckooHash::CuckooHash() : tableSize(PRIME_LIST[0]), tableSizeCounter(0), nodeCount1(0), nodeCount2(0)
{
    std::cout << "\nDefault constructor was called\n\n";
    table1 = new HashNode[tableSize];
    table2 = new HashNode[tableSize];
}

/* key-value Constructor 
*
*  Initialize tableSize to the first value in PRIME_LIST. 
*  When a rehash is necessary, the tableSize
*  will use the next value in PRIME_LIST (doubled and rounded up to the nearest
*  prime number). Take in an intital key and value to pass to insert().
*/
CuckooHash::CuckooHash(const string &key, const int value) : tableSize(PRIME_LIST[0]), tableSizeCounter(0), nodeCount1(0), nodeCount2(0)
{
    std::cout << "\nkey-value constructor was called\n\n";
    table1 = new HashNode[tableSize];
    table2 = new HashNode[tableSize];

    // call insert with given key and value
    insert(key, value);
}

/* ~Destructor() 
*
*  Destructs both hash tables used for the CuckooHash object.
*/
CuckooHash::~CuckooHash()
{
    std::cout << "\ndestructor was called\n\n";
    delete[] table1;
    delete[] table2;
}

/* insert() 
*
*  If the given key is unique, and the given value is a four digit number, the record 
*  will be inserted at the home slot computed by the hash function for table 1. If either table
*  is at or over half full, the tableSize is first rehashed. If there was already an occupant in the home
*  slot, that occupant is evicted and passed to evictToTwo() for reseating.  
*/
void CuckooHash::insert(const string &key, const int value)
{
    // compute both hash values for checking if this key is a duplicate
    int homePosition = hash1(key);     // position found for the first table 
    int evictionPosition = hash2(key); // position found for the second table

    // CONDITION ONE: key must be unique amongst both tables 
    // use hash values to index into the tables and verify this key is unique
    if (table1[homePosition].name == key || table2[evictionPosition].name == key)
    {
        std::cerr << "key " << "'" << key << "' " << "already exists within the hash table\n";
        
        return;
    }
    
    // CONDITION TWO: value must be four digits
    if (!isFourDigit(value)) 
    {
        std::cerr << "The birth year must be in four-digit form\n";

        return;
    }

    // CONDITION THREE: We have good data, now check that the tables are less than half full.
    // if not, call rehash()
    if ((nodeCount1 >= tableSize / 2) || (nodeCount2 >= tableSize / 2))
    {
        //rehash();

        // make sure rehash() updates both tableSize and tableSizeCounter
    }
    
    // try to insert in the home position
    
    // save a temporary copy of the data already there, if it exists
    string tempKey;
    int tempValue = 0;
    bool needEvict = 0;
    if (!table1[homePosition].name.empty())
    {
        tempKey = table1[homePosition].name;
        tempValue = table1[homePosition].birthYear;
        needEvict = 1;
    }

    // new data replaces the old occupant as the new owner of the index
    table1[homePosition].name = key;
    table1[homePosition].birthYear = value;
    
    // only increment nodeCount1 if the new key didn't evict a record
    // (in which case we would be adding a record to table1 but also removing a record from table1)
    if (needEvict == 0)
    {
        ++nodeCount1;
    }
    
    // if there was an eviction (flag is turned on), then call evictToTwo()
    if (needEvict)
    {
        // pass in an initial value of 0 for the evictCount
        evictToTwo(tempKey, tempValue, 0);
    }

    return;
}

/* search() 
*
*  looks first in table1 to see if the key can be found at its hash location.
*  If not present, looks instead in table2 for the record. If found in either table,
*  the birth year is returned. If the record is not found at either hash location, -1 is returned.
*/
int CuckooHash::search(const string &key)
{
    int homePosition = hash1(key); // position found for the first table 

    // if the key at that index matches the key argument, return the year
    if (table1[homePosition].name == key)
    {
        return table1[homePosition].birthYear;
    }
    else
    {
        int evictionPosition = hash2(key); // position found for the second table
        // if the key at that index matches the key argument, return the year
        if (table2[evictionPosition].name == key)
        {
            return table2[evictionPosition].birthYear;
        }
    }

    // -1 signals that the record could not be found
    return -1;
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

/* evictToOne() 
*
*  Reseats the key - value parameters in table 1. If there is a previous occupant.
*  Call evictToTwo() with that occupant. The result is a "ping-pong" effect back and forth 
*  until no eviction is necessary.
*/
void CuckooHash::evictToOne(const string &key, const int value, int staticPass)
{
    // when evictCount is log n, we rehash
    static int evictCount; 
    evictCount = staticPass;
    ++evictCount;

    // if evictCount is greater than or equal to log(N), rehash
    if (evictCount >= log2(nodeCount1 + nodeCount2))
    {
        // rehash()
    }

    // try to insert in table1
    // compute the hash value for table 1
    int hashVal1 = hash1(key); 
    
    // save a temporary copy of the data already there, if it exists
    string tempKey;
    int tempValue = 0;
    bool needEvict = 0;
    if (!table1[hashVal1].name.empty())
    {
        tempKey = table1[hashVal1].name;
        tempValue = table1[hashVal1].birthYear;
        needEvict = 1;
    }

    // new data replaces the old occupant as the new owner of the index
    table1[hashVal1].name = key;
    table1[hashVal1].birthYear = value;
    
    // only increment nodeCount1 if the new key didn't evict a record
    // (in which case we would be adding a record to table1 but also removing a record)
    if (needEvict == 0)
    {
        ++nodeCount1;

        return;
    }
    
    // if there was an eviction (flag is turned on), then call evictToOne()
    if (needEvict)
    {
        evictToTwo(tempKey, tempValue, evictCount);
    }
}

/* evictToTwo() 
*
*  Reseats the key - value parameters in table 2. If there is a previous occupant.
*  Call evictToOne() with that occupant. The result is a "ping-pong" effect back and forth 
*  until no eviction is necessary.
*/
void CuckooHash::evictToTwo(const string &key, const int value, int staticPass)
{
    // when evictCount is log n, we rehash
    static int evictCount; 
    evictCount = staticPass;
    ++evictCount;

    // if evictCount is greater than or equal to log(N), rehash
    if (evictCount >= log2(nodeCount1 + nodeCount2))
    {
        // rehash()
    }

    // try to insert in table2
    // compute the hash value for table 2
    int hashVal2 = hash2(key); 
    
    // save a temporary copy of the data already there, if it exists
    string tempKey;
    int tempValue = 0;
    bool needEvict = 0;
    if (!table2[hashVal2].name.empty())
    {
        tempKey = table2[hashVal2].name;
        tempValue = table2[hashVal2].birthYear;
        needEvict = 1;
    }

    // new data replaces the old occupant as the new owner of the index
    table2[hashVal2].name = key;
    table2[hashVal2].birthYear = value;
    
    // only increment nodeCount1 if the new key didn't evict a record
    // (in which case we would be adding a record to table1 but also removing a record)
    if (needEvict == 0)
    {
        ++nodeCount2;

        return;
    }
    
    // if there was an eviction (flag is turned on), then call evictToOne()
    if (needEvict)
    {
        evictToOne(tempKey, tempValue, evictCount);
    }
}
