#ifndef HELPERFUNC_HPP
#define HELPERFUNC_HPP
#include <filesystem>

#define Expected_Arguments 4

bool CheckArgs(const int &,char **,bool);
bool FileExists(std::filesystem::path ,std::filesystem::file_status,bool);

#endif