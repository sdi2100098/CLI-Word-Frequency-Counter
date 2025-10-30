#ifndef WORDCOUNTER_HPP
#define WORDCOUNTER_HPP
#include <string>
#include <map>

class WordCounter
{
private:
    std::string InputFile;
    std::map<std::string,int> WordMap;
public:
    WordCounter(const char *,const char *,const int &);
    ~WordCounter() = default;
    void ReadInput(const char *,std::string &);
};

#endif
