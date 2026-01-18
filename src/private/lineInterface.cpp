#include "lineInterface.hpp"

#ifdef _WIN32
#include "linenoise.h"
#else
#include <readline/readline.h>
#endif

extern char* command_generator(const char* text, int state);

void MyShell::cross_platform_register_linecompletion()
{
#ifdef _WIN32
    linenoiseSetCompletionCallback(completion);
#else
    rl_attempted_completion_function = [](const char* text, int start, int end) -> char** 
    {
        rl_attempted_completion_over = 1; 
        if (start == 0) {
            return rl_completion_matches(text, command_generator);
        }
        return nullptr; 
    };
#endif
}

char* MyShell::cross_platform_readline(char *prompt)
{
#ifdef _WIN32
    return linenoise(prompt);
#else
    return readline(prompt);
#endif
}
