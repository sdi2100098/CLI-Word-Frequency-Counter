#ifndef WORDCOUNTER_HPP
#define WORDCOUNTER_HPP
#include <string>

class WordCounter
{
private:
    std::string InputFile;
public:
    WordCounter(const char * const,const char * const,const int &);
    ~WordCounter() = default;
    void ReadInput(const char * const,std::string &);
};

#endif
