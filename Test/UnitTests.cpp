#include "acutest.h"
#include "HelperFunc.hpp"
#include "WordCounter.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>


void Test_FileExists(){
    
    std::stringstream dummy;
    std::streambuf* OldCout ; // redirect cout 
    OldCout = std::cout.rdbuf(dummy.rdbuf());

    std::vector<std::string> TestPaths = {"Input","Input/TestInput.txt","Garbage","NothingHere","Input/NoFile.txt"};
    bool Exists;
    for(int i = 0; i<static_cast<int>(TestPaths.size()); i++){
        if(i>1){
            Exists = (FileExists(TestPaths[i],std::filesystem::status(TestPaths[i]),false) == true);
            TEST_ASSERT(Exists == false);
            continue;
        }
        Exists = (FileExists(TestPaths[i],std::filesystem::status(TestPaths[i]),false) == true);
        TEST_ASSERT(Exists == true);
    
    }

    std::cout.rdbuf(OldCout); 
}

void Test_CheckArgs(){
    std::vector<std::vector<std::string>> test_cases = {
        {"prog"},                          
        {"prog", "input.txt"},             
        {"prog", "input.txt","output.txt","4"},
        {"prog", "Input/TestInput.txt", "b", "Not a number"},
        {"prog", "Input/TestInput.txt", "b", "100"},           
    };

    for (int i = 0; i<static_cast<int> (test_cases.size()); i++) {
        // Build non-owning char* array that points into the strings.
        std::vector<char*> argv;
        argv.reserve(test_cases[i].size());
        for (auto &s : test_cases[i]) {
            argv.push_back(const_cast<char*>(s.c_str()));
        }

        int argc = static_cast<int>(argv.size());
        if(i<4)
            TEST_ASSERT(CheckArgs(argc, argv.data(),false) == false);
        else
            TEST_ASSERT(CheckArgs(argc,argv.data(),false) == true);
    }
}

void Test_Map_Sort(){
    std::vector<std::string> test_cases  = {
        "./bin/WordCount", "Input/TestInput.txt", "Output/Output.txt", "100"
    };
    int argc = static_cast<int> (test_cases.size());
    std::vector<char*> argv;
    argv.reserve(argc);
    for(auto &element : test_cases)
        argv.push_back(const_cast<char*>(element.c_str()));

    WordCounter obj(argv[1],argv[2],atoi(argv[3]));
    TEST_ASSERT(obj.getMapSize() == 25);
    TEST_ASSERT(obj.getMapValue("hello") == 3);
    TEST_ASSERT(obj.getMapValue("again") == 2);
    TEST_ASSERT(obj.getMapValue("is") == 2);
    TEST_ASSERT(obj.getMapValue("world") == 2);
}


TEST_LIST = {
    {"File Existing Function",Test_FileExists},
    {"Arguments Checking Function",Test_CheckArgs},
    {"Map Sort",Test_Map_Sort},
    {NULL,NULL}
};