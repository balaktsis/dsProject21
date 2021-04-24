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

long initStructures(const string& filename, UnorderedArray &unorderedArray, hashTable &HashTable){
    long count=0;
    long uniqueCount=0;
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
//            cout<<"Progress: "<<count<<"\r";
            if (HashTable.insert(word)){
                uniqueCount++;
                unorderedArray.InsertUnique(word, 0);
            }


        }
        ifs.close();

        printf("Filled\n");

        for (long i = 0; i < uniqueCount; ++i) {
            unorderedArray.setNum(i, HashTable.search(unorderedArray.getData(i)));
//            printf("%d\n", i);
        }

        printf("Copied\n");

        string searchword = "legal";
        printf("\"%s\" appeared %d times in the Hash Table.\n",searchword.c_str(), HashTable.search(searchword));
        int pos, appearances;
        unorderedArray.Search(searchword, pos, appearances);
        printf("\"%s\" appeared %d times in the Unordered Table.\n",searchword.c_str(), appearances);
        printf("Unique words: %ld.\n", uniqueCount);
        printf("Total words: %ld.\n", count);




    }
    else
        cout<<"File error"<<endl;

    return count;
}




#endif //TEST_MAINFUNCTIONS_H
