#include <iostream>
#include <math.h>
#include "matrix_operations_1d.cpp"
#include "matrix_operations_2d.cpp"
#include "matrix_printing.cpp"

using namespace std;

#define MAX_ITERATIONS 20

/**
 * @brief Найти минимум при помощи алгоритма Розенброка с дискретным шагом.
 * 
 * @param n Количество переменных целевой функции.
 * @param function Указатель на целевую функцию.
 * @param epsilon Точность алгоритма.
 * @param a Коэффициент растяжения.
 * @param b Коэффициент сжатия.
 * @param delta Начальные длины направлений.
 * @param x1 Начальная точка.
 * @return Минимальная точка функции. В случае если превышено максимальное количество итераци - точка на послейдней итерации.
 */
float* Rosenbrock(int n, float (*function)(float*), float epsilon, float a, float b, float* delta, float* x1)
{
	float** s = new float*[n];
	for (int i = 0; i < n; ++i)
		s[i] = new float[n]();
	for (int j = 0; j < n; j++)
		for (int i = 0; i < n; i++)
			if (i == j)
				s[i][j] = 1.0f;
				
	cout << "Initial parameters:" << endl;
	cout << "> Dimension [n] = " << n << endl;
	cout << "> Accuracy [epsilon] = " << epsilon << endl;
	cout << "> Strech ratio [a] = " << a << endl;
	cout << "> Compression ratio [b] = " << b << endl;
	cout << "> Starting direction vector [s]:" << endl << String2dArray(s, n, n) << endl;
	cout << "> Starting delta [delta]:" << endl << String1dArray(delta, n) << endl;
	cout << "> Starting point [x1]:" << endl << String1dArray(x1, n) << endl;

	float* y = x1;
	int k = 1;
	int j = 0;
	float *y_with_step;
	float* y_successful = y;
	cout << ">>> Iteration: 1" << endl;
	while (k < MAX_ITERATIONS)
	{
		for (j = 0; j < n; j++)
		{
	// Шаг 1
			cout << ">>> Step 1" << endl;
			cout << "> y:" << endl << String1dArray(y, n) << endl;
			float f_y = function(y);
			cout << "> f(y) = " << f_y << endl;
			cout << "> s" << j << " =" << String1dArray(s[j], n) << endl;
			cout << "> delta" << j << " =" << delta[j] << endl;
			y_with_step = Array1dSum(y, Array1dScalarMult(s[j], delta[j], n), n);
			cout << "> yjs = yj + delta[j] * s[j]:" << endl << String1dArray(y_with_step, n) << endl;
			float f_y_with_step = function(y_with_step);
			cout << "> f(yjs) = " << f_y_with_step << endl;
			if (f_y_with_step < f_y) {
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
		cout << "> y = " << String1dArray(y, n) << endl;
		cout << "> y_with_step = " << String1dArray(y_with_step, n) << endl;
		if (!Array1dIsEqual(y, y_with_step, n))
		{
			y = y_successful;
			continue;
		}
	// Шаг 4
		cout << ">>> Step 4" << endl;

		if (Array1dAbsLessThan(delta, epsilon, n))
		{
			break;
		}
	// Шаг 5
		cout << ">>> Step 5" << endl;

		delta = Array1dDiff(y_successful, x1, n);
		
		cout << " > New delta: = " << String1dArray(delta, n) << endl;

		float** a_array = new float*[n];

		for (int j = 0; j < n; j++)
		{
			float* aj = new float[n]();
			for (int i = j; i < n; i++) {
				float* addition = Array1dScalarMult(s[i], delta[i], n);
				aj = Array1dSum(aj, addition, n);
			}
			a_array[j] = aj;
		}
		cout << "a: " << endl << String2dArray(a_array, n, n) << endl;
		
		float** b_array = new float*[n];
		b_array[0] = a_array[0];
		s[0] = Array1dScalarMult(a_array[0], 1.0 / Array1dNorm(a_array[0], n), n);

		for (int j = 1; j < n; j++)
		{
			float** A = Array1dTo2d(a_array[j], n);
			cout << "A[" << j << "] = " << String2dArray(A, n, 1) << endl;

			float **b_sum = new float*[1];
			b_sum[0] = new float[n]();

			for (int i = 0; i < j; i++) {
				float** s_i = Array1dTo2d(s[i], n);
				float **s_i_transposed = Array2dTranspose(s_i, n, 1);
				float **a_s_transposed_mul = Array2dMult(A, n, 1, s_i_transposed, 1, n);
				float **prod_si_mul = Array2dMult(a_s_transposed_mul, 1, 1, s_i, n, 1);
				b_sum = Array2dSum(b_sum, prod_si_mul, n, 1);
			}

			float *B = Array2dDiff(A, b_sum,n, 1)[0];
			b_array[j] = B;
			s[j] = Array1dScalarMult(B, 1.0 / Array1dNorm(B, n), n);
		}

		k += 1;
		cout << ">>> Iteration: " << k << endl;
	}

	cout << "Finished" << endl;
	cout << "> Iterations:" << k << endl;
	cout << "> Result:" << endl << String1dArray(y, n) << endl;
	cout << "> Function:" << function(y) << endl;
	
	return y;
}