#include "acutest.h"
#include "HelperFunc.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

void Test_FileExists(){
    std::stringstream dummy;
    std::streambuf* OldCout = std::cout.rdbuf(dummy.rdbuf());
    std::vector<std::string> TestPaths = {"Input","Input/TestInput.txt","Garbage","NothingHere","Input/NoFile.txt"};
    bool Exists;
    for(int i = 0; i<static_cast<int>(TestPaths.size()); i++){
        if(i>1){
            Exists = (FileExists(TestPaths[i],std::filesystem::status(TestPaths[i])) == true);
            TEST_ASSERT(Exists == false);
            continue;
        }
        Exists = (FileExists(TestPaths[i],std::filesystem::status(TestPaths[i])) == true);
        TEST_ASSERT(Exists == true);
    
    }
    std::cout.rdbuf(OldCout);   
}

void Test_CheckArgs(){
    std::vector<std::pair<int,char **>> CheckAgrumentsVector;

}




TEST_LIST = {
    {"File Existing Function",Test_FileExists},
    //{"Arguments Checking Function",Test_CheckArgs},
    {NULL,NULL}
};