#ifndef GETRAND_H
#define GETRAND_H

#include <stdlib.h>
#include <time.h>
#include <math.h>


int GetRandomNumber(int min, int max)
{
	int num = min + rand() % (max - min + 1);
	return num;
}

double GetRandomNumberDouble(double min, double max, int precision)
{
	double value;

	value = rand() % (int)pow(10, precision);
	value = min + (value / pow(10, precision)) * (max - min);
	value = floor(value * 10) / 10;
	return value;
}
#endif // GETRAND_H