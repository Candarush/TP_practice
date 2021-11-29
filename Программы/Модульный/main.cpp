#include <iostream>
#include <math.h>
#include "Rosenbrock_modular.cpp"

float function1(float* x)
{
	return 9 * pow(x[0], 2) + 16 * pow(x[1], 2) - 90 * x[0] - 128 * x[1];
}

float function2(float* x)
{
	return pow(x[0], 2) + 2 * x[0] * x[1] + 2 * pow(x[1], 2) + pow(x[2], 2) - x[1] * x[2] + x[0] + 3 * x[1] - x[2];
}

int main() {
	float epsilon = 0.01;
	float a = 3.0;
	float b = -0.5;
	int n1 = 2;
	int n2 = 3;
	float* x1 = new float[n1] {2.5f, 2.5f};
	float* x2 = new float[n2] {2.5f, 2.5f, 2.5f};
	float* delta1 = new float[n1] {0.5f, 0.5f};
	float* delta2 = new float[n2] {0.5f, 0.5f, 0.5f};
	Rosenbrock(n2, function2, epsilon, a, b, delta2, x2);
	return 0;
}