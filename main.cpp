//
//  main.cpp
//  Gallegos-Michael-PAX
//
//  Created by Michael Gallegos on 12/4/18.
//  Copyright © 2018 Michael Gallegos. All rights reserved.
//
/* For this programming assignment, you will implement three different versions of hash table and study their performance.  You will implement (1) Chaining, (2) Linear Probing and (3) Double Hashing.
 
 Your program will be a simple word-counting application. It reads a text file and creates a hash table, mapping each word to its number of occurrences. Your program should take in and process a .txt file as input (example dictionary.txt). The  dictionary.txt input has one million words in which there are about 58,000 unique words, each occurring a different number of times. Once you have inserted all the words into a hash table, your program should output the number of occurrences for all given strings in the .txt file.
 
 
 Your program should use an array-based implementation for the hash table. The program should also implement a hash function that takes the ASCII values of each character within a word, multiplies them by a positive constant, adds them together, then compresses them with the modulo function (pseudocode below).
 
 int hash = 0
 int n = s.length
 for (int i = 0; i < n; i++)
 hash = g * hash + ASCII value of char
 //g is some positive constant
 //s is a given word
 index = hash % hashTable.length()
 
 For the Double Hashing portion you should review and consider course materials and literature regarding double hashing and implement an efficient secondary hash function. Be sure to give this some critical thought, as you will be asked to justify your function in the report.
 
 Using your three implementations, you will also time how long it takes to insert all strings into the tables. Time how long it takes using the StopWatch class we provided (you don’t need to print the numbers when timing).  You will then show a graph of insertion time into hash tables versus the version of hash tables.
 
 N.B. Preload the entire document in memory to avoid I/O overhead.
 */

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Timer.h"
const long int numberOfSpots = 10000001;
using namespace std;

    class hashChain{
        long int slots; // How many spaces you'd like to make
        vector<string> *table;
    public:
        hashChain() {
            this->slots = numberOfSpots; // Set the bucket number equal to the number of spots
            table = new vector<string>[slots];
        }
        void insertWord(string key) {
            long int index = hashFunction(key);
            table[index].push_back(key);
        }
        long int hashFunction(string key) {
            long int hash = 0;
            for (long int i = 0; i < key.size(); i++){ // Hash the individual ascii character values
                long int x = key.at(i);
                hash = 3.5 * (hash + x); // Use 3.5 as my constant
            }
            long int index = hash % numberOfSpots;
            return index;
        }

        void printHash(string filepath) {
        ofstream cout("/Users/Snowspeeder/Documents/School/CSCE 221/PAX/Gallegos-Michael-PAX/Gallegos-Michael-PAX/output.txt"); // Output cout to output.txt
//            ofstream cout(filepath);
            for (long int i = 0; i < slots; i++){
                string z; // This will be used for the word
                long int y = 0; // this will be our frequency count
                for (auto x : table[i]){ // AS long as the element's in the table
                    if (x != "") { // If the element is not blank, meaning there's a word!
                        y++; // Increase the frequency count by 1
                    }
                    z = x; // This is a string variable for the current word you're looking at
                }
                if (y != 0) // Make sure you're printing actual reoccurences
                cout << z << " : " << y << endl; // Print the element/word and its frequency
            }
        }
    };
    
    class HashLinearProbing {
        string * table = new string[numberOfSpots];
        long int * freqTable = new long int[numberOfSpots];
    public:
        HashLinearProbing(){
            for (long int i = 0; i < numberOfSpots; i++){
                table[i] = "";
                freqTable[i] = 0;
            }
        }
        long int hashFunction(string key) {
            long int hash = 0;
            for (long int i = 0; i < key.size(); i++){ // Hash the individual ascii character values
                long int x = key.at(i);
                hash = 3.5 * (hash + x); // Use 3.5 as my constant
            }
            long int index = hash % numberOfSpots;
            return index;
        }
        
        void insertWord(string key) {
            long int index = hashFunction(key);
            if (table[index] == ""){
                table[index]=key;
                freqTable[index]++;
            }
            else {
                while (table[index] != ""){ // Check and go until you've reached a spot where it's not empty. Until then, keep linear probing by using the hash function. This is included in the original index, and then modded here.
                    index = (index+5) % numberOfSpots; // do the hash function over again
                }
                table[index] = key;
                freqTable[hashFunction(key)]++;
            }
        }
        
        long int getFrequency(string key){
            long int index = hashFunction(key);
            long int frequency = freqTable[index];
            return frequency;
        }
        
        long int size() {
            return numberOfSpots;
        }
//        void printHash(){ OLD ARRAY IMPLEMENTATION, COMMENTING OUT FOR RE-WRITTEN PRINT FUNCTION
//            for (int i = 0; i < numberofSpots; i++){
//                if (wordPrint(i) != "") // This sets up a coniditon so it won't spit out empty values in console
//                    cout << wordPrint(i) << ":" << frequency(i) << endl;
//            }
//        }
        void printHash(string filepath){
            ofstream cout("/Users/Snowspeeder/Documents/School/CSCE 221/PAX/Gallegos-Michael-PAX/Gallegos-Michael-PAX/output.txt"); // Output cout to output.txt
//            ofstream cout(filepath);
            vector<string> listedWords;
            for (long int i = 0; i < numberOfSpots; i++){
                if (find(listedWords.begin(), listedWords.end(), table[i]) == listedWords.end()){
                    if (getFrequency(table[i]) != 0)
                    cout << table[i] << " " << this->getFrequency(table[i]) << endl;
                    listedWords.push_back(table[i]);
                }
            }
//            for (long int i = 0; i < numberOfSpots; i++){
//                if ((listedWords.empty() == false) && (find(listedWords.begin(), listedWords.end(), table[i]) != listedWords.end())){
//                }
//                else{
//                listedWords.push_back(table[i]);
//                if (freqTable[hashFunction(table[i])] != 0)
//                    cout << listedWords[i] << " : " << freqTable[hashFunction(table[i])] << endl;
//                }
//            }
        }
    };
    class DoubleHashing {
        string * table = new string[numberOfSpots];
        long int * freqTable = new long int[numberOfSpots];
    public:
        DoubleHashing(){
            for (long int i = 0; i < numberOfSpots; i++){ // Construct it by setting the errays equal to no string or zero :)
                table[i] = "";
                freqTable[i] = 0;
            }
        }
        long int hashFunction(string key) {
            long int hash = 0;
            for (long int i = 0; i < key.size(); i++){ // Hash the individual ascii character values
                long int x = key.at(i);
                hash = 3.4 * (hash + x); // Use 3.4 as my constant
            }
            long int index = hash % numberOfSpots;
            return index;
        }
        long int hashFun2(string key) {
            long int hash = 0;
            for (long int i = 0; i < key.size(); i++){ // Hash/add the individual ascii character values
                long int x = key.at(i);
                hash = 2.2 * (hash + x); // Use 2.2 as my constant
            }
            long int index = hash % numberOfSpots;
            return index;
        }
        
        void insertWord(string key) {
            long int i = 0;
            long int index = hashFunction(key);
            long int index2 = hashFun2(key);
            if (table[index] == ""){
                table[index] = key;
                freqTable[index]++;
            }
            else {
                while (table[index] != ""){
                    // Check and go until you've reached a spot where it's not empty. Until then, keep linear probing by using the hash function. This is included in the original index, and then modded here.
                    index = (index + (i * index2)) % numberOfSpots;
                    i++; // Increment i as well woohoo!
                }
                table[index] = key;
                freqTable[hashFunction(key)]++;
            }
        }
        
        long int getFrequency(string key){
            long int index = hashFunction(key);
            long int frequency = freqTable[index];
            return frequency;
        }
        
        long int size() {
            return numberOfSpots;
        }
        void printHash(string filepath){
            ofstream cout("/Users/Snowspeeder/Documents/School/CSCE 221/PAX/Gallegos-Michael-PAX/Gallegos-Michael-PAX/output.txt"); // Output cout to output.txt
//            ofstream cout(filepath); // Output cout to output.txt
                vector<string> listedWords;
                for (long int i = 0; i < numberOfSpots; i++){
                    if (find(listedWords.begin(), listedWords.end(), table[i]) == listedWords.end()){
                        if (getFrequency(table[i]) != 0)
                            cout << table[i] << " " << this->getFrequency(table[i]) << endl;
                        listedWords.push_back(table[i]);
                    }
                }
        }
    };

int main(int argc, const char * argv[]) {
    string line; // These will be used for pushing the input to a vector.
    // ===============
    // UNCOMMENT THIS LINE IF YOU WISH TO HARD-CODE THE FILE PATH
     ifstream myfileinput("/Users/Snowspeeder/Documents/School/CSCE 221/PAX/Gallegos-Michael-PAX/Gallegos-Michael-PAX/dictionary.txt");
    /* Xcode console requires this path not have spaces in the name,
    which my CS 221 folder does, so I hard code it during my test runs */
    
    // COMMENT THE FOLLOWING IF YOU WISH TO HARD-CODE THE FILE PATH :)
    
//            string nameOfFile;
//            cout << "Please input the input file path: ";
//            cin >> nameOfFile;
//            cout << endl;
//            ifstream myfileinput(nameOfFile);
            string nameOfFileOut;
//            cout << "Please input the output file path: ";
//            cin >> nameOfFileOut;
//            cout << endl;
//            ofstream outFile(nameOfFileOut);
            ofstream outFile("/Users/Snowspeeder/Documents/School/CSCE 221/PAX/Gallegos-Michael-PAX/Gallegos-Michael-PAX/output.txt");
    
    long int n = 0; // Use this for counting which word has been inputted
    int choice = 0; // Ask the user to pick a hash type
    cout << "Please select a hash table type to try: " << endl;
    cout << "1) Chain Hashing \n" << "2) Linear Probing \n" << "3) Double Hashing \n";
    cin >> choice;
    CStopWatch j;
    if (choice == 1){
        hashChain h;
        while(getline(myfileinput,line)){ // Make each vector element a line from the file
            h.insertWord(line);
            n++;
            cout << "Inserting Word : "<< n <<" " << line << endl;
        }
        float x = j.GetElapsedSeconds(); // We only want to output how long it takes to insert it, I think.
        h.printHash(nameOfFileOut);
        cout << "Time taken to insert the words in Chaining Hashtable: " << x << " seconds." << endl;
        cout << "Time taken total (Implement hash table and find/print word frequencies): " << j.GetElapsedSeconds() << endl;
    }
    else if (choice == 2){
        HashLinearProbing h;
        while(getline(myfileinput,line)){ // Make each vector element a line from the file
            h.insertWord(line);
            n++;
            cout << "Inserting Word : " << n << " " << line << endl;
        }
        float x = j.GetElapsedSeconds(); // We only want to output how long it takes to insert it, I think.
        h.printHash(nameOfFileOut);
        cout << "Time taken to insert the words in Linear Probing method: " << x << " seconds." << endl;
        cout << "Time taken total (Implement hash table and find/print word frequencies): " << j.GetElapsedSeconds() << endl;
    }
    else if (choice == 3){
        DoubleHashing h;
        while(getline(myfileinput,line)){ // Make each vector element a line from the file
            h.insertWord(line);
            n++;
            cout << "Inserting Word : "<< n << " " << line << endl;
            
        }
        float x = j.GetElapsedSeconds(); // We only want to output how long it takes to insert it, I think.
        h.printHash(nameOfFileOut);
        cout << "Time taken to insert the words in Double Hashing method: " << x << " seconds." << endl;
        cout << "Time taken total (Implement hash table and find/print word frequencies): " << j.GetElapsedSeconds() << endl;
    }
    else{
        cout << "Invalid Input." << endl;
        return 0;
    }
    myfileinput.close(); // close the file
    return 0;
}
