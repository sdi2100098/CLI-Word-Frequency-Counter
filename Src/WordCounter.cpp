#include "../Include/WordCounter.hpp"
#include <cctype>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

WordCounter :: WordCounter(const char *InputFilename,const char *OutputFilename,const int &N){
    std::cout << "Constructor Invoked \n\n";
    setN(N);
    ReadInput(InputFilename);
}

WordCounter :: ~WordCounter(){
    std::cout << "\nDestructor Invoked \n";
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
            if(Word.empty() == false){
                UpdateWordsMap(Word);
                Word.clear();
            }
            continue;
        }

        Word += character;

    }

    if(Word.empty() == false){
            UpdateWordsMap(Word);
            Word.clear();
    }

    FileOpened.close();

    // When we Finish reading through the File sort the Map and redirect the output into a new File
    SortMap();
}

void WordCounter :: UpdateWordsMap(const std::string &Word){
    if(Word.empty() == true)
        return ;
    // Exists in the Map
    if(WordsMap.find(Word)!=WordsMap.end())
        WordsMap[Word] ++;
    else
        WordsMap[Word] = 1;
}

void WordCounter :: SortMap(){
    int colsize = 15;
    std::vector<std::pair<std::string,int>> SortedWords;
    SortedWords.reserve(WordsMap.size());
    for(auto &item : WordsMap)
        SortedWords.emplace_back(item);

    // Sort the Vector
    std::sort(SortedWords.begin(),SortedWords.end(),[](auto &a,auto &b){
        if(a.second != b.second)
            return a.second > b.second;
        return a.first < b.first;
    });

    if (N < static_cast<int>(SortedWords.size()))
        SortedWords.resize(N);

    std::cout << std::left;
    std::cout << std::setw(colsize) << "Words" << std::setw(colsize) << "Count" << std::endl;
    for(auto &ele : SortedWords)
        std::cout << std::setw(colsize) << ele.first << " " << std::setw(colsize) << ele.second << std::endl;
    
}