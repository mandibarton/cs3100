#ifndef EXECUTE_H
#define EXECUTE_H

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <exception>
#include <chrono>

using namespace std;

//definitions
bool execute(vector<string> &, vector<string> &, chrono::microseconds &);

vector<string> separate(string origString, char c);

bool pipeInterpreter(vector<string> &, vector<string> &, vector<string> &, chrono::microseconds &);

bool checkIfPipe(vector<string> &, int &);

bool shell(string &, vector<string> &, chrono::microseconds &);

#endif // !EXECUTE_H
