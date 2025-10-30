#include "../Include/WordCounter.hpp"
#include <iostream>

WordCounter :: WordCounter(const char *InputFilename,const char *OutputFilename,const int &N){
    std::cout << "Constructor Invoked \n";
    setN(N);
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