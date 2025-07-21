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

#endif