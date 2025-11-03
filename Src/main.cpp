#include <iostream>
#include <fstream>
#include "../Include/WordCounter.hpp"
#include "../Include/HelperFunc.hpp"
#include <chrono>

int main(int argc,char **argv){
    auto start = std::chrono::high_resolution_clock::now();
    if(CheckArgs(argc,argv,true) == false)
        return 1;
    
    WordCounter CountWords(argv[1],argv[2],atoi(argv[3]));
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::ofstream out ("Benchmark/Times.txt",std::ios::app);
    out << "Map elpased : " << elapsed.count() << "seconds with Input : " << argv[1] << " and N : " << argv[3] << " \n ";
    return 0;
}