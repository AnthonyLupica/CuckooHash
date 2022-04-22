/*
    Data Structures
    Project Hash: Cuckoo Hashing
    Author: Anthony Lupica <arl127@uakron.edu> 2022

    Implementation file for a hash table class using the cuckoo hashing technique

    The hash table implements a celebrity birth-year lookup. The name of a celebrity
    (and non-famous people alike) can be used as the key to quickly find their birth year.
    Ex.] std::cout << CuckooHash.search("Brad Pitt");
         --> "1963"
    
    The user may also wish use some other logical assiocation of names and years.
*/

#include "CuckooHash.hpp"
#include <iostream>
#include <cmath> 

/* Default Constructor 
*
*  Initialize table size to the first value in PRIME_LIST. 
*  When a rehash is necessary, the table size
*  will use the next value in PRIME_LIST (double previous table size and round up to the nearest
*  prime number).
*/
CuckooHash::CuckooHash() : tableSize(PRIME_LIST[0]), tableSizeCounter(0), nodeCount1(0), nodeCount2(0)
{
    table1 = new HashNode[tableSize];
    table2 = new HashNode[tableSize];
}

/* key-value Constructor 
*
*  Initialize table size to the first value in PRIME_LIST. 
*  When a rehash is necessary, the table size
*  will use the next value in PRIME_LIST (double previous table size and round up to the nearest
*  prime number). Take in an intital key and value to pass to insert().
*/
CuckooHash::CuckooHash(const string &key, const int value) : tableSize(PRIME_LIST[0]), tableSizeCounter(0), nodeCount1(0), nodeCount2(0)
{
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
    delete[] table1;
    delete[] table2;
}

/* insert() 
*
*  If the given key is unique, and the given value is a four digit number, the record 
*  will be inserted at the home slot computed by the hash function for table 1. If either table
*  is at or over half full, the tableSize is first rehashed. If there was already an occupant in the home
*  slot, that occupant is evicted and passed to evictToTwo() for reseating. In the event of an eviction cycle, 
*  specifically determined by log N evictions (where N is the table size), rehash is called. 
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

    // CONDITION THREE: We have good data, now check that both tables are less than half full.
    // if not, call rehash()
    if ((nodeCount1 >= tableSize / 2) || (nodeCount2 >= tableSize / 2))
    {
        if (rehash() == 1)
        {
            return;
        }

        // need to recompute the hash value 1 with new tableSize 
        homePosition = hash1(key); 

        std::cout << "\nrehash was called. " << "tableSize: " << tableSize << ". PRIME index: " << tableSizeCounter << std::endl;
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
    if (!needEvict)
    {
        ++nodeCount1;

        return;
    }
    // if there was an eviction (flag is turned on), then call evictToTwo()
    else 
    {
        // pass in an initial value of 0 for the evictCount
        evictToTwo(tempKey, tempValue, 0);
    }

    return;
}

/* search() 
*
*  looks first in table 1 to see if the key can be found at its hash location.
*  If not present, looks instead in table 2 for the record. If found in either table,
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
    std::cout << "evictToOne was called\n";

    // when evictCount is log n, we rehash
    static int evictCount; 
    evictCount = staticPass;
    ++evictCount;

    std::cout << "evictCount: " << evictCount << "\n\n";

    // if evictCount is greater than or equal to log(N), rehash
    if (evictCount >= log2(tableSize))
    {
        // rehash()

        std::cout << "rehash would have been called in table One\n";


        // reset evictCount to 0 after rehash
        evictCount = 0;
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
    // (in which case we would be adding a record to table1 but also removing a record from table1)
    if (!needEvict)
    {
        ++nodeCount1;

        return;
    }
    // if there was an eviction (flag is turned on), then call evictToTwo()
    else 
    {
        evictToTwo(tempKey, tempValue, evictCount);
    }

    return;
}

/* evictToTwo() 
*
*  Reseats the key - value parameters in table 2. If there is a previous occupant.
*  Call evictToOne() with that occupant. The result is a "ping-pong" effect back and forth 
*  until no eviction is necessary.
*/
void CuckooHash::evictToTwo(const string &key, const int value, int staticPass)
{
    std::cout << "EvictToTwo was called\n";
    
    // when evictCount is log n, we rehash
    static int evictCount; 
    evictCount = staticPass;
    ++evictCount;

    std::cout << "evictCount: " << evictCount << "\n\n";

    // if evictCount is greater than or equal to log(N), rehash
    if (evictCount >= log2(tableSize))
    {
        // rehash()

        std::cout << "rehash would have been called in table two\n";

        // reset evictCount to 0 after rehash
        evictCount = 0;
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
    
    // only increment nodeCount2 if the new key didn't evict a record
    // (in which case we would be adding a record to table2 but also removing a record from table2)
    if (!needEvict)
    {
        ++nodeCount2;

        return;
    }
    // if there was an eviction (flag is turned on), then call evictToOne()
    else 
    {
        evictToOne(tempKey, tempValue, evictCount);
    }

    return;
}

/* rehash() 
*
*  uses the next value in PRIME_LIST (approximately double the size), to allocate new tables.
*  All records in the old tables are then rehashed to the new tables using the new table size.
*  If the user has stored enough records such that there is no next value in PRIME_LIST, the demo
*  has reached it's conclusion and no new records may be inserted.
*/
bool CuckooHash::rehash() 
{
    if (tableSizeCounter == LENGTH_PRIME - 1)
    {
        std::cerr << "You've reached the maximum size for this hash table demo.\n";

        // return 1 to signal insert() to return without attempting to insert
        return 1;
    }

    // increment the index to use for selecting a prime number from PRIME_LIST
    ++tableSizeCounter;    
    // update tableSize with the new PRIME_LIST index  
    tableSize = PRIME_LIST[tableSizeCounter];

    // allocate new (temporary tables with increased size)
    HashNode* table1Temp = new HashNode[tableSize];
    HashNode* table2Temp = new HashNode[tableSize];

    // loop through the elements for table1 and table2, and rehash all intialized nodes to the temporary tables
    // use the old tableSize for the loop condition
    int hash1Index = -1;
    int hash2Index = -1;
    for (int i = 0; i < PRIME_LIST[tableSizeCounter - 1]; ++i)
    {
        if (!table1[i].name.empty())
        {
            hash1Index = hash1(table1[i].name);

            table1Temp[hash1Index].name = table1[i].name;
            table1Temp[hash1Index].birthYear = table1[i].birthYear;
        }
        if (!table2[i].name.empty())
        {
            hash2Index = hash2(table2[i].name);

            table2Temp[hash2Index].name = table2[i].name;
            table2Temp[hash2Index].birthYear = table2[i].birthYear;
        }
    }

    // delete the old arrays
    delete[] table1;
    delete[] table2;

    // point old array pointers to new arrays
    table1 = table1Temp;
    table2 = table2Temp;

    // make temp pointers point to null
    table1Temp = nullptr;
    table2Temp = nullptr;

    // 0 for good reallocation
    return 0;
}

/* contains()
*
*  returns true if the key is found in the table, and false otherwise
*/
bool CuckooHash::contains(const string &key)
{
    int homePosition = hash1(key); // position found for the first table 

    // if the key at that index matches the key argument, return true
    if (table1[homePosition].name == key)
    {
        return 1;
    }
    else
    {
        int evictionPosition = hash2(key); // position found for the second table
        // if the key at that index matches the key argument, return true
        if (table2[evictionPosition].name == key)
        {
            return 1;
        }
    }

    // return false if the element was not found
    return 0;
}
