#pragma once

#include <vector>
#include <string>

#include "command.hpp"

namespace MyShell {
    class Type : public Command
    {
    public:
        Type() = default;
        Type(MyShell::Shell* shell);
        virtual void Execute(std::vector<std::string>& Args) override;

    private:
        std::vector<std::string> PathDir;

        string is_exist(std::string& CmdName);
    };
}
