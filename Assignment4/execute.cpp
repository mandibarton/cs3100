#include "execute.h"

using namespace std;

const int NUM_OF_PIPES = 2;
const int PIPE_READ_END = 0;
const int PIPE_WRITE_END = 1;

const int STDOUT = 1;
const int STDIN = 0;

bool execute(vector<string> &inputVec, vector<string> &history, chrono::microseconds &totalClock)
{	
	//try block for the exit command
	try
	{
		// check for exit
		if (inputVec.at(0) == "exit")
		{
			return false;
		}

		// if the command entered was not exit, go on to do the other functions
		else
		{
			//command history
			if (inputVec.at(0) == "history")
			{
				cout << "-- Command History --" << endl;
				// i is just an iterator that will number the history of commands
				int i = 1;
				//not bounded
				for (string histString : history)
				{
					cout << i << " " << histString << endl;
					++i;
				}
			}

			// next, allow user to perform a oommand from history
			else if (inputVec.at(0) == "^")
			{
				if (fork())
				{
					// start counting the time it takes
					auto startClock = chrono::system_clock::now();
					//telling it to wait for the child process
					wait(NULL);
					// stop counting
					auto endClock = chrono::system_clock::now();
					//take difference between the start and end time
					totalClock += chrono::duration_cast<chrono::microseconds>(endClock - startClock);
				}
				else
				{
					int historyPosition = stoi(inputVec.at(1));
					//store the commands in a vector for ease
					vector<string> historyStored = separate(history[historyPosition - 1], ' ');

					int argc = (int)historyStored.size();
					char** args = new char*[argc + 1];

					for (int i = 0; i < argc; ++i)
					{
						int length = historyStored[i].length() + 1;
						args[i] = new char[length];
						strncpy(args[i], historyStored[i].c_str(), length);
					}
					//execvp needs a null character :)
					args[argc] = NULL;
					execvp(args[0], args);
					return false;

					//end of else block
				}

				//end of if-else block
			}

			//ptime functionality 
			else if (inputVec.at(0) == "ptime")
			{
				//casting these to durations so that I can use them in calculations

				auto seconds = chrono::duration_cast<chrono::seconds>(totalClock);
				auto milliseconds = chrono::duration_cast<chrono::milliseconds>(totalClock - seconds);
				auto microseconds = chrono::duration_cast<chrono::microseconds>(totalClock - seconds - milliseconds);

				//display on the command line 
				cout << "Time spent executing child processes: " << seconds.count() << " seconds ";
				cout << milliseconds.count() << " milliseconds and " << microseconds.count() << " microseconds. " << endl;
			}

			//adding commands to history, except for the history command
			else
			{
				string historyAdd;
				for (string s : inputVec)
				{
					historyAdd.append(s);
					historyAdd.append(" ");
				}
				history.insert(history.begin(),historyAdd);

				if (fork())
				{
					//start counting how long it takes
					auto startTime = chrono::system_clock::now();
					//tell it to wait for child processes
					wait(NULL);
					// stop counting
					auto endTime = chrono::system_clock::now();
					//take difference between the start and end time
					totalClock += chrono::duration_cast<chrono::microseconds>(endTime - startTime);
				}
				else
				{
					int argc = (int)inputVec.size();
					char** args = new char*[argc + 1];

					for (int i = 0; i < argc; ++i)
					{
						int length = inputVec[i].length() + 1;
						args[i] = new char[length];
						strncpy(args[i], inputVec[i].c_str(), length);
					}

					args[argc] = NULL;

					execvp(args[0], args);
					return false;
					//end of else block
				}
				//end of parent else
			}
			return true;
			//end of else-if
		}
		//end of try block
	}
	//exception handling
	//catch block
	catch (exception& e)
	{
		return true;
	}
}
	//this function contains the functionality to separate arguments
	vector<string> separate(string originalString, char c)
	{
		//declare a vector of strings
		vector<string> stringVector;
		string subString;

		//find the character by which I want to split things
		int i = originalString.find(c);

		while (i != string::npos)
		{
			// split the string
			subString = originalString.substr(0, i);
			originalString = originalString.substr(i + 1, string::npos);

			// add the string to the vector, unless it's 0
			if (i != 0 && subString.size() != 0)
			{
				stringVector.push_back(subString);
			}

			//now, find the next instance of the character by which I split the string
			i = originalString.find(c);
			//end of while 
		}

		if (originalString.size() != 0)
		{
			stringVector.push_back(originalString);
		}
		return stringVector;
		//end of function
	
}

bool checkIfPipe(vector<string> &input, int &inputLocationOfPipe)
{
	int i = 0;
	for (string s : input)
	{
		if(s.compare("|") == 0)
		{
			inputLocationOfPipe = i;
			return true;
		}
	++i;
	}
return false;
}

bool pipeInterpreter(vector<string> &interpretInput, vector<string> &interpretInput2, vector<string> &history, chrono::microseconds &totalTime)
{
	string inputToHistory;
	for (string s : interpretInput)
	{
		inputToHistory.append(s);
		inputToHistory.append(" ");
	}

	inputToHistory.append("| ");

	for (string s : interpretInput2)
	{
		inputToHistory.append(s);
		inputToHistory.append(" ");
	}

	history.insert(history.begin(), inputToHistory);

	if (fork())
	{
		// start counting the time it takes
		auto startClock = chrono::system_clock::now();
		//telling it to wait for the child process
		wait(NULL);
		// stop counting
		auto endClock = chrono::system_clock::now();
		//take difference between the start and end time
		totalTime += chrono::duration_cast<chrono::microseconds>(endClock - startClock);
	}

	else
	{
		int pids[NUM_OF_PIPES];
		pipe(pids);

		int origstdout = dup(STDOUT);
		int origstdin = dup(STDIN);

		pid_t pid = fork();
		if (pid == 0)
		{
			dup2(pids[PIPE_WRITE_END], STDOUT);
			int argc = (int)interpretInput.size();
			char** argv = new char*[argc + 1];

			for (int i = 0; i < argc; ++i)
			{
				int length = interpretInput[i].length() + 1;
				argv[i] = new char[length];
				strncpy(argv[i], interpretInput[i].c_str(), length);
			}
			argv[argc] = NULL;
			execvp(argv[0], argv);
		}

		pid_t pid2 = fork();
		if (pid2 == 0)
		{
			dup2(pids[PIPE_READ_END], STDIN);
			close(pids[PIPE_WRITE_END]);

			int argc = (int)interpretInput2.size();
			char** argv = new char*[argc + 1];

			for (int i = 0; i < argc; ++i)
			{
				int length = interpretInput2[i].length() + 1;
				argv[i] = new char[length];
				strncpy(argv[i], interpretInput2[i].c_str(), length);
			}

			argv[argc] = NULL;
			execvp(argv[0], argv);
		}

		int status;
		waitpid(pid, &status, 0);

		close(pids[PIPE_WRITE_END]);
		close(pids[PIPE_READ_END]);

		waitpid(pid2, &status, 0);

		dup2(origstdin, STDIN);
		dup2(origstdout, STDOUT);

		return false;
	}
	return true;
}

bool shell(string &input, vector<string> &history, chrono::microseconds &totalClock)
{
	int inputLocationOfPipe = 0;
	vector<string> inputVec = separate(input, ' ');

		if (checkIfPipe(inputVec, inputLocationOfPipe))
		{
			try
			{
				vector<string> inputVecOne;
				vector<string> inputVecTwo;

				for (int i = 0; i < inputLocationOfPipe; i++)
				{
					inputVecOne.insert(inputVecOne.end(), inputVec[i]);
				}

				for (int i = inputLocationOfPipe + 1; i < inputVec.size(); i++)
				{
					inputVecTwo.insert(inputVecTwo.end(), inputVec[i]);
				}

				return pipeInterpreter(inputVecOne, inputVecTwo, history, totalClock);
			}

			catch (exception& e)
			{
				cout << "There was a problem with the pipe" << endl;
				return true;
			}
		}
		else
		{
			return execute(inputVec, history, totalClock);
		}
		return true;
}