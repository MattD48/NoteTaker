// Files.hpp
#ifndef FILES_HPP
#define FILES_HPP

#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>

void writeToFile(std::string fileName, std::string text);

void createFile(std::string fileName);

// void combineFiles(std::string file1, std::string file2, std::string combined);

void deleteFile(std::string fileName);

#endif // FILES_HPP