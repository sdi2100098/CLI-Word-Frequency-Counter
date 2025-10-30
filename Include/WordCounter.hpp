#ifndef WORDCOUNTER_HPP
#define WORDCOUNTER_HPP
#include <string>
#include <map>

class WordCounter
{
private:
    int N;
    std::map<std::string,int> WordMap;
public:
    WordCounter(const char *,const char *,const int &);
    ~WordCounter();
    void ReadInput(const char *,std::string &);
    void setN(const int &);
    int getN()const;
};

#endif
