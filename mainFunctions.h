#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "UnorderedArray.h"
#include "hashTable.h"
#ifndef TEST_MAINFUNCTIONS_H
#define TEST_MAINFUNCTIONS_H


string wordStrip(const string& word){
    string temp;                            //Initialize empty string
    for (char i : word) {                   //Iterate through all chars in the word
        if ('A'<=i && i<='Z'){              //Make char lowercase
            i+= 'a'-'A';
        } else if (!('a'<=i && i<='z')){    //Discard non alphabetical chars
            continue;
        }
        temp += i;                          //Add valid characters (lowercase alphabetic) to the temp string
    }
    return temp;
}

long initStructures(string filename, UnorderedArray &unorderedArray, hashTable &HashTable){
    long count=0;
    string word;
    ifstream ifs;
    ifs.open(filename);
    if (ifs.is_open())
    {
        cout<<"File open ok"<<endl;
        while (ifs >> word)
        {
            word = wordStrip(word);
            if (word.empty() || (0 <= word[0] && word[0] <= 32)){
                continue;
            }
            count++;
            cout<<"Progress: "<<count<<"\r";

            unorderedArray.Insert(word);    //Start off by filling the unordered array to avoid repeating word count calculations

        }
        ifs.close();

        printf("Filling hashtable!");

        for (int i = 0; i < unorderedArray.size; ++i) {
            HashTable.insert(unorderedArray.data[i], unorderedArray.num[i]);
        }



    }
    else
        cout<<"File error"<<endl;

    return count;
}




#endif //TEST_MAINFUNCTIONS_H
