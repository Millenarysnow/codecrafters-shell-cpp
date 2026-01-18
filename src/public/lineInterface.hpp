#pragma once

namespace MyShell 
{
    void cross_platform_register_linecompletion();

    char* cross_platform_readline(char* prompt);
}