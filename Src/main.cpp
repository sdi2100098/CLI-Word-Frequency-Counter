#include <iostream>
#include <fstream>
#include "../Include/WordCounter.hpp"
#include "../Include/HelperFunc.hpp"

int main(int argc,char **argv){

    if(CheckArgs(argc,argv) == false)
        return 1;
    
    WordCounter CountWords(argv[1],argv[2],atoi(argv[3]));
    return 0;
}