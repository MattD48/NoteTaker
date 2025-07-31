// Files.hpp
#ifndef FILES_HPP
#define FILES_HPP

#define DelDONE 1

#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace Files {

    void writeToFile(std::string fileName, std::string text);

    void createFile(std::string fileName);

    // void combineFiles(std::string file1, std::string file2, std::string combined);

    void deleteFile(std::string fileName);

    void listFiles(std::string path);

}

#endif // FILES_HPP