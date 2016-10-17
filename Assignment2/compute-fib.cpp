#include "computefib.h"
#include <iostream>


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
