#ifndef WORDCOUNTER_HPP
#define WORDCOUNTER_HPP
#include <string>
#include <vector>
#include <map>

class WordCounter
{
private:
    int N;
    std::map<std::string,int> WordsMap;
    std::vector<std::pair<std::string,int>> SortedWords;
public:
    WordCounter(const char *,const char *,const int &);
    ~WordCounter();
    void ReadInput(const char *);
    void WriteOutput(const char *);
    void setN(const int &);
    int getN()const;
    void UpdateWordsMap(const std::string &);
    void SortMap();
    int getMapSize()const;
    int getMapValue(std::string)const;
};

#endif
