#include <math.h>

using namespace std;

float* Array1dSum(float* array1, float* array2, int length)
{
	float *arraySum = new float[length]();
	for (int i = 0; i < length; i++)
	{
		arraySum[i] = array1[i] + array2[i];
	}
	return arraySum;
}

bool Array1dIsEqual(float* array1, float* array2, int length)
{
	float *arraySum = new float[length]();
	for (int i = 0; i < length; i++)
	{
		if (array1[i] != array2[i])
			return false;
	}
	return true;
}

float* Array1dScalarMult(float* array, float scalar, int length)
{
	float *resultArray = new float[length]();
	for (int i = 0; i < length; i++)
	{
		resultArray[i] = array[i] * scalar;
	}
	return resultArray;
}

float* Array1dDiff(float* array1, float* array2, int length)
{
	float *arraySum = new float[length]();
	for (int i = 0; i < length; i++)
	{
		arraySum[i] = array1[i] - array2[i];
	}
	return arraySum;
}

float Array1dNorm(float* array, int length)
{
	float sum = 0.;
	for (int i = 0; i < length; i++)
	{
		sum += pow(array[i], 2.0);
	}
	return sqrt(sum);
}

float** Array1dTo2d(float* array, int length)
{
	float **result = new float*[length];
	int i;
	for (i = 0; i < length; i++)
		result[i] = new float[1]();
	for (i = 0; i < length; i++)
	{
		result[0][i] = array[i];
	}
	return result;
}

bool Array1dAbsLessThan(float* array, float value, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (abs(array[i]) >= value)
			return false;
	}
	return true;
}
