#include "execute.h"

using namespace std;

bool execute(string &input, vector<string> &history, chrono::microseconds &totalClock)
{
	vector<string> myInput = separate(input, ' ');

	//try block for the exit command
	try
	{
		// check for exit
		if (myInput.at(0) == "exit")
		{
			return false;
		}

		// if the command entered was not exit, go on to do the other functions
		else
		{
			//command history
			if (myInput.at(0) == "history")
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
			else if (myInput.at(0) == "^")
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
					int historyPosition = stoi(myInput.at(1));
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
			else if (myInput.at(0) == "ptime")
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
				history.insert(history.begin(), input);

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
					int argc = (int)myInput.size();
					char** args = new char*[argc + 1];

					for (int i = 0; i < argc; ++i)
					{
						int length = myInput[i].length() + 1;
						args[i] = new char[length];
						strncpy(args[i], myInput[i].c_str(), length);
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
