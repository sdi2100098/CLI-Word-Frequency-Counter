#include "../Include/HelperFunc.hpp"
#include<iostream>

bool FileExists(std::filesystem::path FilePath,std::filesystem::file_status Status = std::filesystem::file_status{},bool verbose = true){
    if(verbose == true)
        std::cout << "\nPath : " << FilePath << std::endl;
    if(std::filesystem::status_known(Status) ? std::filesystem::exists(Status) : std::filesystem::exists(FilePath))
        return true;
    return false;
}

bool CheckArgs(const int &argc,char **argv,bool verbose){
    if(argc !=4){
        if(verbose == true){
            std::cerr << "Not enough arguments where given : argc=" << argc << " Expected Arguments : " << Expected_Arguments << '\n';
            for(int i=0;i<argc;i++) 
                std::cerr << "argv["<<i<<"]=" << argv[i] << '\n';
            std::cerr << "Use Command : make run ARGS= \"input.txt output.txt N(int)\" \n";
            std::cerr << "Or Use : ./bin/WordCount input.txt output.txt N(int)" << std::endl;
        }
        return false;
    }
    if(FileExists(argv[1],{},verbose) == false){
        if(verbose == true){
            std::cerr << "First Argument ("<< argv[1] << ")" << " doesn't exist" << std::endl;
            std::cerr << "Expected Argument : Input/$$$.txt" << std::endl;
        }
        return false;
    }

    // Check that user gave number 
    std::string Num = argv[3];
    for(char c : Num){
        if(std::isdigit(c) == false){
            if(verbose == true)
                std::cerr << "Last Argument must be an integer number" << std::endl;
            return false;
        }
    }
    return true;
}