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
    hashy.insert("Hulk from avengers", 3000);
    hashy.insert("Katniss everdeen", 3050);
    hashy.insert("Peta from the movie", 3051);
    hashy.insert("Rehash", 3052);
    hashy.insert("Rehash now?", 3053);
    hashy.insert("The Fuck?", 3054);
    hashy.insert("The Fuck?", 3054);
    hashy.insert("Will Smith", 3055);
    hashy.insert("jada", 7000);
    hashy.insert("rob thomas", 7001);
    hashy.insert("ozzy", 7002);

    cout << "\n" << hashy.search("Anthony Lupica") << " ";
    cout << hashy.search("George Lopez") << " ";
    cout << hashy.search("Kim Possible") << " ";
    cout << hashy.search("Robert Lupica") << " ";
    cout << hashy.search("Captain America") << " ";
    cout << hashy.search("Hulk from avengers") << " ";
    cout << hashy.search("Katniss everdeen") << " ";
    cout << hashy.search("Peta from the movie") << " ";
    cout << hashy.search("Rehash") << " ";
    cout << hashy.search("Rehash now?") << " ";
    cout << hashy.search("The Fuck?") << " ";
    cout << hashy.search("Will Smith") << " ";
    cout << hashy.search("Tom") << " ";
    cout << hashy.search("jada") << " ";
    cout << hashy.search("rob thomas") << " ";
    cout << hashy.search("ozzy") << " ";

    cout << hashy.contains("butt");





    cout << "    " << hashy.getNodes1() << " || " << hashy.getNodes2();
  
    return 0;
}
