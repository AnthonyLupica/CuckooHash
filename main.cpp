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
    hashy.insert("Captain America", 2012);
    hashy.insert("Hulk", 3000);
    hashy.insert("I hope this works", 1200);
    hashy.insert("I hope", 1957);

    cout << "\n" << hashy.search("Anthony Lupica") << " ";
    cout << hashy.search("George Lopez") << " ";
    cout << hashy.search("Kim Possible") << " ";
    cout << hashy.search("Robert Lupica") << " ";
    cout << hashy.search("Captain America") << " ";
    cout << hashy.search("Hulk") << " ";
    cout << hashy.search("I hope this works") << " ";
    cout << hashy.search("I hope") << " ";


    cout << hashy.getNodes1() << " || " << hashy.getNodes2();
  
    return 0;
}
