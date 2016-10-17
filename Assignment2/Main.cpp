#include <iomanip>
#include <iostream>
#include <string>
#include <cstring>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include "computee.h"
#include "computefib.h"
#include "computepi.h"

using namespace std;

//help  menu
void helpmenu()
{
	cout << " --- Assign 1 Help --- " << endl;
	cout << "\t -fib [n] : Compute the fibonacci of [n]" << endl;
	cout << "\t -e [n] : Compute the value of 'e' using [n] iterations" << endl;
	cout << "\t -pi [n] : Compute Pi to [n] digits" << endl;
}



//main
int main(int argc, char *argv[])
{
	//if the user chose -fib as their action
	if (strcmp(argv[1], "-fib") == 0)
	{
		//using isdigit to ensure the second parameter was indeed a digit. Decimal numbers are truncated to ints
		if (isdigit(stoi(argv[2])) != 0)
		{
			cout << "You did not enter valid input" << endl;
			helpmenu();
		}
		else
		{
			//store the user inputted integer for program use
			int n = stoi(argv[2]);
			if (n >= 0 && n <= 40)
			{
				int output = fibonacci(n);
				cout << "The fibonacci of " << n << " is " << output << endl;
			}
			else
			{
				cout << "You did not enter valid input" << endl;
				helpmenu();
			}
		}
	}
	//if the user chose -e as their action
	else if (strcmp(argv[1], "-e") == 0)
	{
		if (isdigit(stoi(argv[2])) != 0)
		{
			cout << "You did not enter valid input" << endl;
			helpmenu();
		}
		else
		{
			int n = stoi(argv[2]);
			if (n >= 1 && n <= 30)
			{
				double result = getValueOfe(1, n, 1.0, 0.0);
				cout << "The computed value of 'e' is " << result << endl;
			}
			else
			{
				cout << "You did not enter valid input" << endl;
				helpmenu();
			}
		}
	}
	// if the user chose -pi as their action
	else if (strcmp(argv[1], "-pi") == 0)
	{
		if (isdigit(stoi(argv[2])) != 0)
		{
			cout << "You did not enter valid input" << endl;
			helpmenu();
		}
		else
		{
			int n = stoi(argv[2]);
			if (n >= 1 && n <= 10)
			{
				//compute pi here
				long double result = getPi(n);
				cout << "Pi computed to " << n << " number of digits is " << setprecision(10) << result << endl;
			}
			else
			{
				cout << "You did not enter valid input" << endl;
				helpmenu();
			}

		}
	}
	// if the user did not input -fib, -e, or -pi, display the help menu
	else
	{
		cout << "You did not enter valid input" << endl;
		helpmenu();
	}

}