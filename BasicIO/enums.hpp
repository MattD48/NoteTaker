//enums.hpp
#ifndef ENUMS_APP
#define ENUMS_APP


#include <iostream>
#include <map>
#include <functional>
#include <string>

namespace Secondary { // Created namespace for better grouping/readability

    extern std::map<std::string, std::function<void()>> commandMap; // Container to be used to store command key-value pairs

}

namespace UI {

    extern std::map<std::string, std::string> helpConfigMap; // Constainer to store helpConfig data from helpConfig.txt
}

namespace Files {

    extern std::map<int, std::string> fileListMap; // Container to store names of files in a specific directory

}    

#endif