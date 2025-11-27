#include <iostream>
#include "secrets.h"
#include <fstream>
#include <string>

void load_env(std::ifstream& file)
{
    std::string line;

    while(std::getline(file, line))
    {
        // empty line
        if (line.empty() || line[0] == '#') continue;

        // parse line 
        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;

        std::string key = line.substr(0, eq);
        std::string value = line.substr(eq + 1);

        // set env variable
        setenv(key.c_str(), value.c_str(), 1);

    }



}