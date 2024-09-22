#include "core/defines.h"
#include "core/logger.h"

#include <toml++/toml.h>

// TODO: change back to YMake.toml
#define DEFAULT_FILE "test/YMake.toml"

std::vector<std::string> GetProjectNames(const char *filepath)
{
    std::ifstream file(filepath, std::ios::in);

    std::string line;

    std::vector<std::string> names;

    while(std::getline(file, line))
    {
        std::stringstream ss{line};
        std::string word;

        ss >> word;
        if(word == "#")
        {
            ss >> word;
            if(word == "PROJECT:")
            {
                ss >> word;
                names.push_back(word);
            }
        }
    }

    file.close();
    return names;
}

int main(int argc, char **argv)
{
    LINFO(false, "YMake v0.01\n");

    //_____________ CONFIG FILE OPENING _____________
    std::string filepath = DEFAULT_FILE;

    std::ifstream file(filepath, std::ios::in);
    if(!file.is_open())
    {
        if(argc < 2)
        {
            LERROR("The File ", DEFAULT_FILE, " was not found.\n");
            LERROR("You must create the file, or specify the path of a .toml file as the 1st argument.");
        }
        else
        {
            filepath = argv[1];
        }
    }

    std::vector<std::string> projects = GetProjectNames(filepath.c_str());

    LINFO(false, "projects to be compiled: \n");
    for(auto proj : projects)
    {
        LINFO(false, "proj: ", proj, "\n");
    }

    auto config = toml::parse_file(filepath);
    return 0;
}