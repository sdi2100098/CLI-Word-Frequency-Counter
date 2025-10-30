#include "../Include/HelperFunc.hpp"
#include<iostream>

bool FileExists(std::filesystem::path FilePath,std::filesystem::file_status Status = std::filesystem::file_status{}){
    std::cout << "\nInput Path : " << FilePath << std::endl;
    if(std::filesystem::status_known(Status) ? std::filesystem::exists(Status) : std::filesystem::exists(FilePath))
        return true;
    return false;
}

bool CheckArgs(const int &argc,char **argv){
    if(argc !=4){
        std::cerr << "Not enough arguments where given : argc=" << argc << " Expected Arguments : " << Expected_Arguments << '\n';
        for(int i=0;i<argc;i++) 
            std::cerr << "argv["<<i<<"]=" << argv[i] << '\n';
        std::cerr << "Use Command : make run ARGS= \"input.txt output.txt N(int)\" \n";
        std::cerr << "Or Use : ./bin/WordCount input.txt output.txt N(int)" << std::endl;
        return false;
    }
    if(FileExists(argv[1]) == false){
        std::cerr << "First Argument ("<< argv[1] << ")" << " doesn't exist" << std::endl;
        return false;
    }
    return true;
}