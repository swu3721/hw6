#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

#include <ctime>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        HASH_INDEX_T hash[5] = {0};  //Make array of size 5 (biggest possible word)

        int strIndex = k.length() - 1; //String index (starts at end)
        int hashIndex = 4; //Hash index starts at end as well
        while (strIndex >= 0 && hashIndex >= 0) { //While they are not at the beginning

            HASH_INDEX_T weight = 1; //The 36^x part
            HASH_INDEX_T val = 0; //val put into w

            for (int i = 0; i < 6 && strIndex >= 0; ++i) { //Iterating from 0-6 and strIndex >= 0 (in case string less than 6)
                HASH_INDEX_T digit = letterDigitToNumber(k[strIndex]);
                val += digit * weight;
                weight *= 36;
                --strIndex; //Decrement
            }
            hash[hashIndex] = val;
            --hashIndex; //Decrement
        }

        unsigned long long hashVal = 0;
        for (size_t i = 0; i < 5; ++i) {
            hashVal += rValues[i] * hash[i]; //Compute the hash val
        }

        return hashVal;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (isdigit(letter)) {
            return letter - '0' + 26; //integers are after the letters of alphabet
        } else {
            return tolower(letter) - 'a'; //a - a = 0, b - a = 1, etc.
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
