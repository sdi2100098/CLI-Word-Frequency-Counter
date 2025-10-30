#include "../Include/WordCounter.hpp"
#include <cctype>
#include <iostream>
#include <fstream>
#include <iomanip>

WordCounter :: WordCounter(const char *InputFilename,const char *OutputFilename,const int &N){
    std::cout << "Constructor Invoked \n";
    setN(N);
    ReadInput(InputFilename);
}

WordCounter :: ~WordCounter(){
    std::cout << "Destructor Invoked \n";
}

void WordCounter :: setN(const int &N){
    this->N = N;
    return ;
}

int WordCounter :: getN()const{
    return this->N;
}

void WordCounter :: ReadInput(const char *File){
    std::ifstream FileOpened(File); // open File
    if(FileOpened.fail()){
        std::cerr << "Failed to open File : " << File << std::endl;
    }
    char character;
    std::string Word;

    // Start processing one Character at a time
    while(FileOpened.get(character)){

        //Ignore Panctuations
        if(std::ispunct(character))
            continue;
        
        //Convert uppercase to lowercase
        if(std::isupper(character))
            character = std::tolower(character);
        
        if(std::isspace(character)){
            UpdateWordsMap(Word);
            Word.clear();
            continue;
        }

        Word += character;
    }
}

void WordCounter :: UpdateWordsMap(const std::string &Word){
    // Exists in the Map
    if(WordsMap.find(Word)!=WordsMap.end())
        WordsMap[Word] ++;
    else
        WordsMap[Word] = 1;
}

void WordCounter :: PrintMap(){
    int colsize = 20;
    std::cout << std::left;
    std::cout << std::setw(colsize) <<  "Words" << std::setw(colsize) << "Counts" << std::endl;
    for(auto &element : WordsMap)
        std::cout << std::setw(colsize) <<  element.first  << std::setw(colsize) << element.second << std::endl;
}