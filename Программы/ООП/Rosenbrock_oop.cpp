#include <iostream>
#include <math.h>
#include "MatrixOperations1d.cpp"
#include "MatrixOperations2d.cpp"
#include "MatrixString.cpp"

using namespace std;

#define MAX_ITERATIONS 20

class RosenbrockAlgorithm
{
private:
	float epsilon;
	float a;
	float b;
	int n;

	static float** GetIdentityMatrix(int size)
	{
		float** result = new float*[size];
		for (int i = 0; i < size; ++i)
			result[i] = new float[size]();
		for (int j = 0; j < size; j++)
			for (int i = 0; i < size; i++)
				if (i == j)
					result[i][j] = 1.0f;
		return result;
	}

	float** FindArrayA(float** s, float* delta)
	{
		float** result = new float*[n];
		for (int j = 0; j < n; j++)
		{
			float* aj = new float[n]();
			for (int i = j; i < n; i++) {
				float* addition = MatrixOperations1d::Array1dScalarMult(s[i], delta[i], n);
				aj = MatrixOperations1d::Array1dSum(aj, addition, n);
			}
			result[j] = aj;
		}
		return result;
	}

	float** FindArrayB(float** s, float** a_array)
	{
		float** b_array = new float*[n];
		b_array[0] = a_array[0];

		for (int j = 1; j < n; j++)
		{
			float** A = MatrixOperations1d::Array1dTo2d(a_array[j], n);

			float **b_sum = new float*[1];
			b_sum[0] = new float[n]();

			for (int i = 0; i < j; i++) {
				float** s_i = MatrixOperations1d::Array1dTo2d(s[i], n);
				float **s_i_transposed = MatrixOperations2d::Array2dTranspose(s_i, n, 1);
				float **a_s_transposed_mul = MatrixOperations2d::Array2dMult(A, n, 1, s_i_transposed, 1, n);
				float **prod_si_mul = MatrixOperations2d::Array2dMult(a_s_transposed_mul, 1, 1, s_i, n, 1);
				b_sum = MatrixOperations2d::Array2dSum(b_sum, prod_si_mul, n, 1);
			}

			float *B = MatrixOperations2d::Array2dDiff(A, b_sum,n, 1)[0];
			b_array[j] = B;
		}
		return b_array;
	}

public:

	RosenbrockAlgorithm(float iepsilon, float ia, float ib)
	{
		epsilon = iepsilon;
		a = ia;
		b = ib;
	}

	void SetEpsilon(float iepsilon) { epsilon = iepsilon; }
	void SetA(float ia) { a = ia; }
	void SetB(float ib) { b = ib; }


	float* FindMinimum(float (*function)(float*), int in, float* x1, float* delta)
	{
		n = in;
		float **s = GetIdentityMatrix(n);
		float* y = x1;
		int k = 1;
		int j = 0;
		float* y_with_step;
		float* y_successful = y;

		cout << ">>> Iteration: 1" << endl;
		while (k < MAX_ITERATIONS)
		{
			for (j = 0; j < n; j++)
			{
		// Шаг 1
				cout << ">>> Step 1" << endl;
				cout << "> y:" << endl << MatrixString::String1dArray(y, n) << endl;
				float f_y = function(y);
				cout << "> f(y) = " << f_y << endl;
				cout << "> s[" << j << "] =" << MatrixString::String1dArray(s[j], n) << endl;
				cout << "> delta[" << j << "] =" << delta[j] << endl;
				y_with_step = MatrixOperations1d::Array1dSum(y, MatrixOperations1d::Array1dScalarMult(s[j], delta[j], n), n);
				cout << "> yjs = yj + delta[j] * s[j]:" << endl << MatrixString::String1dArray(y_with_step, n) << endl;
				float f_y_with_step = function(y_with_step);
				cout << "> f(yjs) = " << f_y_with_step << endl;
				if (f_y_with_step < f_y) 
				{
					cout << "Step successful." << endl;
					y = y_with_step;
					y_successful = y_with_step;
					delta[j] *= a;
				}
				else {
					cout << "Step unsuccessful." << endl;
					delta[j] *= b;
				}
				cout << "> delta[" << j << "] = " << delta[j] << endl;
		// Шаг 2
				cout << ">>> Step 2" << endl;
				cout << "> j = " << j << endl;
			}
			j = 0;

		// Шаг 3
			cout << ">>> Step 3" << endl;
			cout << "y = " << MatrixString::String1dArray(y, n) << endl;
			cout << "y_with_step = " << MatrixString::String1dArray(y_with_step, n) << endl;
			if (!MatrixOperations1d::Array1dIsEqual(y, y_with_step, n))
			{
				y = y_successful;
				continue;
			}
		// Шаг 4
			cout << ">>> Step 4" << endl;

			if (MatrixOperations1d::Array1dAbsLessThan(delta, epsilon, n))
			{
				break;
			}
		// Шаг 5
			cout << ">>> Step 5" << endl;

			delta = MatrixOperations1d::Array1dDiff(y_successful, x1, n);
			
			cout << " > New delta: = " << MatrixString::String1dArray(delta, n) << endl;

			float **a_array = FindArrayA(s, delta);

			float **b_array = FindArrayB(s, a_array);

			for (int j = 0; j < n; j++)
				s[j] = MatrixOperations1d::Array1dScalarMult(b_array[j], 1.0 / MatrixOperations1d::Array1dNorm(b_array[j], n), n);

			k += 1;
			cout << ">>> Iteration: " << k << endl;
		}

		cout << "Finished" << endl;
		cout << "> Iterations:" << k << endl;
		cout << "> Result:" << endl << MatrixString::String1dArray(y, n) << endl;
		cout << "> Function:" << function(y) << endl;

		return y;
	}
	
};

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
	RosenbrockAlgorithm *method = new RosenbrockAlgorithm(epsilon, a, b);
	method->FindMinimum(function1, 2, x1, delta1);
	return 0;
}