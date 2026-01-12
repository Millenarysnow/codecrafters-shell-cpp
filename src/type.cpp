#include "type.hpp"

#ifdef _WIN32
constexpr char PATH_LIST_SEPARATOR = ';';
#include <io.h>
#else
constexpr char PATH_LIST_SEPARATOR = ':';
#include <unistd.h>
#endif

#include <iostream>
#include <cstdlib>
#include <sstream>

MyShell::Type::Type(MyShell::Shell *shell) : Command(shell)
{
    const char* value = std::getenv("PATH");
    if(value != nullptr)
    {
        std::string Path = std::string(value);

        std::stringstream ss;
        ss.str(Path);

        std::string temp;
        while(getline(ss, temp, PATH_LIST_SEPARATOR))
        {
            PathDir.push_back(temp);
        }
    }
    else
    {
        PathDir = {};
    }
}

string MyShell::Type::is_exist(std::string &CmdName)
{
    string result;

    for (auto& dir : PathDir)
    {
        std::string current_dir = dir + "/" + CmdName;

#ifdef _WIN32
        if (_access(current_dir.c_str(), 02) == 0)
#else
        if (access(current_dir.c_str(), X_OK) == 0)
#endif
        {
            result = current_dir;
            break;
        }
    }

    return result;
}

void MyShell::Type::Execute(std::vector<std::string> &Args)
{
    if(Args.size() == 0)
    {
        std::cout << "error" << std::endl;
        return;
    }

    if(shell->is_builtin(Args[0]))
    {
        std::cout << Args[0] << " is a shell builtin" << std::endl;
        return;
    }

    if(PathDir.size() > 0)
    {
        std::string res = is_exist(Args[0]);
        if(!res.empty())
        {
            std::cout << Args[0] << " is " << res << std::endl;
            return;
        }
    }

    std::cout << Args[0] << ": not found" << std::endl;
}

