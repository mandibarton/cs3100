#include "computee.h"
#include <iomanip>
#include <iostream>
using namespace std;


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

