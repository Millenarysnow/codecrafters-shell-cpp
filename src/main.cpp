#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

set<string> Commands;
unordered_map<string, void(*)()> Execute;

bool Start = true;

void Exit()
{
  Start = false;
}

int main() 
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  Commands.insert("exit");
  Execute.insert({"exit", &Exit});

  while(Start)
  {
    std::cout << "$ ";

    string inputCommand;
    getline(cin, inputCommand);

    if(Commands.find(inputCommand) != Commands.end())
    {
      void (*p)() = Execute[inputCommand];
      p();
    }
    else
      cout << inputCommand << ": " << "command not found" << endl;
  }
}
