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
bool execute(string &, vector<string> &, chrono::microseconds &);

vector<string> separate(string origString, char c);


#endif // !EXECUTE_H