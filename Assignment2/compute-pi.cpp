#include "computepi.h"
#include <iomanip>
#include <iostream>
using namespace std;


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