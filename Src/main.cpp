#include <iostream>
#include <fstream>

int main(int argc,char **argv){
    if(argc !=4){
        std::cout << "./WordCount Input.txt Output.txt N \n";
        std::cout << "Example : ./WordCount Input/MyFile.txt Output/MyOutputFile.txt 100" << std::endl;
    }

    return 0;
}