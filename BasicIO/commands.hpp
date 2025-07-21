//enums.hpp
#ifndef COMMANDS_APP
#define COMMANDS_APP


namespace Main {


    void write();

    void create();

    void dlete();

    void quit();



    void printOptions(); // Print available user options

    void quickThought(); // For a quick, brain dump. Placed in a holding file and user is asked if they have a destination they want to provide for further sorting

}

namespace Secondary {

    void normalizeInput(std::string& input); // Used to make all input the same case (lower) to avoid any casing issues

    void initCommands(); // Populate our command map with all commands
}

#endif