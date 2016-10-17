#include <iomanip>
#include <iostream>
#include <string>
#include <cstring>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

using namespace std;

//help  menu
void helpmenu()
{
	cout << " --- Assign 1 Help --- " << endl;
	cout << "\t -fib [n] : Compute the fibonacci of [n]" << endl;
	cout << "\t -e [n] : Compute the value of 'e' using [n] iterations" << endl;
	cout << "\t -pi [n] : Compute Pi to [n] digits" << endl;
}

//fibonacci function
int fibonacci(int n)
{
	//first number of the sequence is zero
	if (n == 0)
	{
		return 0;
	}
	//second and third numbers are one
	if (n == 1 || n == 2)
	{
		return 1;
	}
	//otherwise, compute using recursion
	else
	{
		return fibonacci(n - 1) + fibonacci(n - 2);
	}
}

//compute value of e
//pass in number of iterations to estimate over
double getValueOfe(int cur, int iters, double f, double v)
{
	if (cur <= iters)
	{
		//recurse through until we hit the number of iterations we want
		//forumla is e = 1 + 1/n! + ...
		return getValueOfe(cur + 1, iters, f * cur, v + 1.0 / f);
	}
	return v;
}

//compute pi
//passing in number of digits to compute to
long double getPi(int n)
{
	//store user inut in variable 'x'
	int x = n;
	//array of pis
	long double pis[] = { 3.0, 3.1, 3.14, 3.141, 3.1415, 3.14159, 3.141592, 3.1415926, 3.14159265, 3.1414592653 };
	//have to return user input -1 to account for array indexing :)
	return pis[x - 1];
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

