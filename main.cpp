/*
    Data Structures
    Project Hash: Cuckoo Hashing
    Author: Anthony Lupica <arl127@uakron.edu> 2022

    Driver file using the CuckooHash class

    Test Cases are used to display the functionality and analyze the performance
    of a hash table that uses the cuckoo hashing technique.

    The chosen name - year association is different celebrities and their birth years.
*/

#include "CuckooHash.hpp"
#include <iostream>
#include <cassert>

using std::cout;

int main()
{
    //-- Testing Section For Correctness --//

    // create a hash table object, call it hashTest, and initialize with a name and birth year
    CuckooHash hashTest("Brad Pitt", 1963);
    
    // insert names and birth years
    hashTest.insert("Natalie Portman", 1981);
    hashTest.insert("Johnny Depp", 1963);
    hashTest.insert("Beyonce", 1981);
    hashTest.insert("Tom Brady", 1977);
    hashTest.insert("Betty White", 1922);

    // call search() on the inserts and verify with asserts that the years match
    assert(hashTest.search("Brad Pitt") == 1963 && "An unexpected birth year was found");
    assert(hashTest.search("Natalie Portman") == 1981 && "An unexpected birth year was found");
    assert(hashTest.search("Johnny Depp") == 1963 && "An unexpected birth year was found");
    assert(hashTest.search("Beyonce") == 1981 && "An unexpected birth year was found");
    assert(hashTest.search("Tom Brady") == 1977 && "An unexpected birth year was found");
    assert(hashTest.search("Betty White") == 1922 && "An unexpected birth year was found");
    
    // call size() for the number of records in the table and verify with an assert 
    assert(hashTest.size() == 6 && "An unexpected size was returned");

    // insert two more records
    hashTest.insert("Ariana Grande", 1993);
    hashTest.insert("Chris Rock", 1965);

    // call size() for the number of records in the table and verify with an assert 
    assert(hashTest.size() == 8 && "An unexpected size was returned");

    // verify that the non duplicate keys rule is supported
    hashTest.insert("Beyonce", 1981);

    // delete a record, test search on that record, verify that size updates, reinsert the same record, and test search again
    hashTest.remove("Beyonce");
    assert(hashTest.search("Beyonce") == -1 && "An unexpected birth year was found");
    assert(hashTest.size() == 7 && "An unexpected size was returned");
    hashTest.insert("Beyonce", 1981);
    assert(hashTest.search("Beyonce") == 1981 && "An unexpected birth year was found");

    // test contains()
    assert(hashTest.contains("LeBron james") == 0 && "Found a record that should not exist");
    assert(hashTest.contains("Natalie Portman") == 1 && "A record that should exist was not found");

    //-------------------------------------//

    return 0;
}
