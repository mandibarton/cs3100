#include "execute.h"
using namespace std;

int main()
{
	//string for the text entered by the user
	string userInput;
	//initializing the history vector
	vector<string> history{};
	//starting time is 0
	chrono::microseconds totalTime(0);

	//use a do-while loop for ease of program continuity
	do 
	{
		cout << "[cmd]: ";
		getline(cin, userInput);
	} 

	while (execute(userInput, history, totalTime));

	return 0;
}
