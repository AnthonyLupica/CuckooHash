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


using std::cout;

int main()
{
    //-- Testing Section For Correctness --//

    // create a hash table object, call it hashy, and initialize with a name and birth year
    CuckooHash hashy("Brad Pitt", 1963);
    
    // insert names and birth years
    hashy.insert("Natalie Portman", 1981);
    hashy.insert("Johnny Depp", 1963);
    hashy.insert("Beyonce", 1981);
    hashy.insert("Tom Brady", 1977);
    hashy.insert("Betty White", 1922);

    // search those names to display their birth years
    cout << "\nBrad Pitt was born in " << hashy.search("Brad Pitt") << "\n"; 
    cout << "Natalie Portman was born in " << hashy.search("Natalie Portman") << "\n"; 
    cout << "Johnny Depp was born in " << hashy.search("Johnny Depp") << "\n"; 
    cout << "Beyonce was born in " << hashy.search("Beyonce") << "\n"; 
    cout << "Tom Brady was born in " << hashy.search("Tom Brady") << "\n"; 
    cout << "Betty White was born in " << hashy.search("Betty White") << "\n";

    // display the number of records in the table 
    cout << "\nThe number of records is " << hashy.size() << "\n";

    //-------------------------------------//

    return 0;
}
