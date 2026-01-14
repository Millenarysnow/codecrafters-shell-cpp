#include "cd.hpp"

#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

#include <iostream>

MyShell::Cd::Cd(MyShell::Shell *shell) : Command(shell)
{ }

void MyShell::Cd::Execute(std::vector<std::string> &Args)
{
    int ret = 0;

#ifdef _WIN32
    if(!Args[0].empty())
    {
        ret = _chdir(Args[0].c_str());
    }
    else
    {
        ret = -1;
    }
#else
    if(!Args[0].empty())
    {
        ret = chdir(Args[0].c_str());
    }
    else
    {
        ret = -1;
    }

#endif

    if(ret == 0)
    { }
    else
    {
        std::cout << "cd: " << Args[0] << ": No such file or directory" << std::endl;
    }
}