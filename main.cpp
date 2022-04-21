/*
    Data Structures
    Project Hash: Cuckoo Hashing
    Author: Anthony Lupica <arl127@uakron.edu> 2022

    Driver file using the CuckooHash class

    Test Cases are used to display the functionality and analyze the performance
    of a hash table that uses the cuckoo hashing technique
*/

#include "CuckooHash.hpp"
#include <iostream>

using std::cout;

int main()
{

{
    CuckooHash hashy;
    
    hashy.insert("brad", 1000);
    cout << hashy.search("nick");

    
}
 
    
    
    return 0;
}
