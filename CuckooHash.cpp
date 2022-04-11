/*
    Data Structures
    Project Hash: Cuckoo Hashing
    Author: Anthony Lupica <arl127@uakron.edu> 2022

    Implementation file for a hash table class using the cuckoo hashing technique

    The hash table implements a "celebrity lookup." The last name of a celebrity
    is used as the key to quickly find if any entries in the table are a match.
    Ex.] std::cout << CuckooHash.search("Pitt");
         --> "Brad Pitt"
*/

#include "CuckooHash.hpp"
