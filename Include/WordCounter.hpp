#ifndef WORDCOUNTER_HPP
#define WORDCOUNTER_HPP
#include <string>
#include <map>

class WordCounter
{
private:
    int N;
    std::map<std::string,int> WordsMap;
public:
    WordCounter(const char *,const char *,const int &);
    ~WordCounter();
    void ReadInput(const char *);
    void setN(const int &);
    int getN()const;
    void UpdateWordsMap(const std::string &);
    void SortMap();
};

#endif
