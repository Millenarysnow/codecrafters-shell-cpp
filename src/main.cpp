#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <sstream>

using namespace std;

bool Start = true;

void Exit(vector<string>& Args)
{
  Start = false;
}

void Echo(vector<string>& Args)
{
  for (int i = 0; i < Args.size() - 1; i++)
  {
    cout << Args[i] << " ";
  }
  cout << Args[Args.size() - 1] << endl;
}

void SplitInput(string& Input, string& Command, vector<string>& Args)
{
  stringstream ss;
  ss.str(Input);

  string temp;
  ss >> Command;
  while(ss >> temp)
    Args.push_back(temp);
}

int main() 
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  set<string> Commands;
  unordered_map<string, void(*)(vector<string>&)> Execute;

  Commands.insert({"exit", "echo"});
  Execute.insert({{"exit", &Exit}, {"echo", &Echo}});

  while(Start)
  {
    std::cout << "$ ";

    string Input;
    getline(cin, Input);

    string Command;
    vector<string> Args;

    SplitInput(Input, Command, Args);

    if(Commands.find(Command) != Commands.end())
    {
      void (*p)(vector<string>&) = Execute[Command];
      p(Args);
    }
    else
      cout << Input << ": " << "command not found" << endl;
  }
}
