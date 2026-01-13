#include "utils.hpp"

#ifdef _WIN32
#include <io.h>
#include <windows.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#endif

#include "shell.hpp"

#include <iostream>

std::string MyShell::is_exist(std::string &CmdName, const std::vector<std::string>& PathDir)
{
    std::string result;

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

int MyShell::call_external_program(const std::string &ProgramPath, const std::vector<std::string> &Args, const MyShell::Shell* shell)
{
    int retn = 0;
#ifdef _WIN32
    // ...
#else
    pid_t pid = fork();
    if (pid == 0)
    {
        execv(ProgramPath.c_str(), shell->get_cargs());
        std::cerr << "execv failed" << std::endl;
        exit(1);
    }
    else if (pid > 0)
    {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            retn = WEXITSTATUS(status);
        }
    }
    else
    {
        std::cerr << "fork failed" << std::endl;
    }
#endif
    return retn;
}
