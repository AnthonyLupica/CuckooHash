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
    CuckooHash hashy("Anthony Lupica", 2000);
    hashy.insert("George Lopez", 1900);
    hashy.insert("Kim Possible", 1999);
    hashy.insert("Robert Lupica", 1964);

    cout << hashy.search("Anthony Lupica") << " ";
    cout << hashy.search("George Lopez") << " ";
    cout << hashy.search("Kim Possible") << " ";
    cout << hashy.search("Robert Lupica") << " ";
  
    return 0;
}
