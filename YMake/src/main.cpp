#include "core/defines.h"
#include "core/logger.h"

#include <toml++/toml.h>

// TODO: change back to YMake.toml
#define DEFAULT_FILE "test/YMake.toml"

struct Project
{
    std::string name;
    u32 lineNum; // the start of the config file.

    Project() {}
    Project(std::string name, u32 lineNum) : name{name}, lineNum{lineNum} {}
};

std::vector<Project> GetProjects(const char *filepath)
{
    std::vector<Project> projects;

    std::ifstream file(filepath, std::ios::in);

    u32 lineNo = 0;
    std::string line;
    while(std::getline(file, line))
    {
        lineNo++;
        std::stringstream ss{line};
        std::string word;

        ss >> word;
        if(word == "#")
        {
            ss >> word;
            if(word == "PROJECT:")
            {
                ss >> word;
                projects.push_back(Project(word, lineNo));
            }
        }
    }

    file.close();
    return projects;
}

// TODO: need to setup cmd arguments properly
int main(int argc, char **argv)
{
    LLOG(BLUE_TEXT("[INFO]\t"), "YMake v0.0.1\n");

    //_____________ CONFIG FILE OPENING _____________
    std::string filepath = DEFAULT_FILE;

    std::ifstream file(filepath, std::ios::in);
    if(!file.is_open())
    {
        LERROR("The File ", DEFAULT_FILE, " was not found.\n");
        LERROR("You must create the file: \'", DEFAULT_FILE, "\'");
    }

    std::vector<Project> projects = GetProjects(filepath.c_str());

    if(projects.size() == 0)
    {
        LERROR("No Projects found in ", DEFAULT_FILE, ".\n");
        LERROR("\tmust specify at least one \'# PROJECT: project_name\' comment in the file.\n");
        return 2;
    }

    LINFO(false, "projects to be compiled: \n");
    for(Project proj : projects)
    {
        LINFO(false, "proj: ", proj.name, ".\tline: ", proj.lineNum, "\n");
    }

    auto config = toml::parse_file(filepath);
    return 0;
}