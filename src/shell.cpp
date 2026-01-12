#include "shell.hpp"
#include <iostream>
#include <sstream>

#include "exit.hpp"
#include "echo.hpp"
#include "type.hpp"

MyShell::Shell::Shell()
{
    Exit* exit = new Exit(this);
    Echo* echo = new Echo(this);
    Type* type = new Type(this);

    Commands.insert({"exit", "echo", "type"});
    Execute.insert({{"exit", exit}, {"echo", echo}, {"type", type}});
}

bool MyShell::Shell::is_builtin(const string &cmd) const
{
    return Commands.find(cmd) != Commands.end();
}

void MyShell::Shell::input()
{
    Input.clear();
    InputCommand.clear();
    Args.clear();

    std::getline(std::cin, Input);

    stringstream ss;
    ss.str(Input);

    string temp;
    ss >> InputCommand;
    while(ss >> temp)
        Args.push_back(temp);
}

void MyShell::Shell::execute()
{
    if(Commands.find(InputCommand) != Commands.end())
    {
        Command* cmd = Execute[InputCommand];
        if (cmd)
            cmd->Execute(Args);
    }
    else
        std::cout << Input << ": " << "command not found" << std::endl;
}
