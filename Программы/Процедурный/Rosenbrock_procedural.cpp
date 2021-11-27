#include <iostream>
#include <math.h>

using namespace std;

#define MAX_ITERATIONS 20

float* Rosenbrock(int n, float (*function)(float*), float epsilon, float a, float b, float* delta, float* x1)
{
	float** s = new float*[n];
	for (int i = 0; i < n; ++i)
		s[i] = new float[n]();
	for (int j = 0; j < n; j++)
		for (int i = 0; i < n; i++)
			if (i == j)
				s[i][j] = 1.0f;

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

			// Вывод данных об итерации
			cout << "y = [ ";
			for (int i = 0; i < n; i++){
				cout << y[i];
				if (i != n-1)
					cout << ", ";
			}
			cout << " ]" << endl;
			float f_y = function(y);
			cout << "> f(y) = " << f_y << endl;
			cout << "> delta[" << j <<"] =" << delta[j] << endl;

			// Вычисление шага
			float *step = new float[n]();
			for (int i = 0; i < n; i++)
				step[i] = s[j][i] * delta[j];

			//Прибавление шага к текцщей координате
			y_with_step = new float[n]();
			for (int i = 0; i < n; i++)
				y_with_step[i] = y[i] + step[i];

			//Вывод шага и значения функции в нем
			cout << "y_with_step = [ ";
			for (int i = 0; i < n; i++){
				cout << y_with_step[i];
				if (i != n-1)
					cout << ", ";
			}
			cout << " ]" << endl;
			float f_y_with_step = function(y_with_step);
			cout << "> f(y_with_step) = " << f_y_with_step << endl;

			if (f_y_with_step < f_y) 
			{
				cout << "Step successful." << endl;
				y = y_with_step;
				y_successful = y_with_step;
				delta[j] *= a;
			}
			else
			{
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

		bool y_equalto_y_with_step = true;
		for (int i = 0; i < n; i++)
			if (y[i] != y_with_step[i])
				y_equalto_y_with_step = false;
		if (!y_equalto_y_with_step)
		{
			y = y_successful;
			continue;
		}
	// Шаг 4
		cout << ">>> Step 4" << endl;

		bool abs_delta_lessthan_epsilon = true;
		for (int i = 0; i < n; i++)
			if (abs(delta[i]) >= epsilon)
				abs_delta_lessthan_epsilon = false;
		if (abs_delta_lessthan_epsilon)
		{
			cout << "> Epsilon check successful. Finishing iterations." << endl;
			break;
		}
	// Шаг 5
		cout << ">>> Step 5" << endl;

		// Вычисление новой делты
		delta = new float[n]();
		for (int i = 0; i < n; i++)
			delta[i] = y_successful[i] - x1[j];
		
		cout << "> New delta = [ ";
		for (int i = 0; i < n; i++){
			cout << delta[i];
			if (i != n-1)
				cout << ", ";
		}
		cout << " ]" << endl;

		// Вычисление А
		float** a_array = new float*[n];

		for (int j = 0; j < n; j++)
		{
			float* aj = new float[n]();
			for (int i = j; i < n; i++)
			{
				float* addition = new float[n]();
				for (int m = 0; m < n; m++)
					addition[m] = (s[i])[m] * delta[i];
				for (int m = 0; m < n; m++)
					aj[m] = aj[m] + addition[m];
			}
			a_array[j] = aj;
		}

		// Вычисление В
		float** b_array = new float*[n];
		b_array[0] = a_array[0];
		float a_array0_norm;
		float norm_sum = 0.;
		for (int i = 0; i < n; i++)
		{
			norm_sum += pow(a_array[0][i], 2.0);
		}
		a_array0_norm = sqrt(norm_sum);

		s[0] = new float[n];
		for (int i = 0; i < n; i++)
			s[0][i] = a_array[0][i] / a_array0_norm;

		for (int j = 1; j < n; j++)
		{
			// Перевод одномерного массива a_array[j] в двумерный
			float **A = new float*[n]();
			for (int m = 0; m < n; m++)
				A[m] = new float[1]();
			for (int m = 0; m < n; m++)
			{
				A[0][m] = a_array[j][m];
			}

			//Вычисжегие B[j]
			float **b_sum = new float*[1];
			b_sum[0] = new float[n]();

			for (int i = 0; i < j; i++)
			{
				// Перевод одномерного массива s[i] в двумерный
				float** s_i = new float*[n]();
				for (int m = 0; m < n; m++)
					s_i[m] = new float[1]();
				for (int m = 0; m < n; m++)
				{
					s_i[0][m] = s[i][m];
				}

				//Транспонирование s_i
				float **s_i_transposed = new float*[1];
				int o;
				for (int m = 0; m < n; m++)
					s_i_transposed[m] = new float[1]();
				for (int m = 0; m < n; m++)
					for (o = 0; o < n; o++)
						s_i_transposed[m][o] = s_i[o][m];

				//Умножение A на транспонированую s_i
				float **a_s_transposed_mul = new float*[1]{new float[1]()};
				for(int m=0; m<n; ++m)
					a_s_transposed_mul[0][0] += A[0][m] * s_i_transposed[m][0];

				// Умножаем результат предыдущего умножения на s_i
				float **prod_si_mul = new float*[1]{new float[1]()};
				for(int m=0; m<n; ++m)
					prod_si_mul[0][m] = s_i[0][m] * a_s_transposed_mul[0][0];

				// Прибавляем результат предыдущего умножения к b_sum
				for(int m=0; m<n; ++m)
					b_sum[0][m] += prod_si_mul[0][m];
			}

			float *B = new float[n]();
			for(int m=0; m<n; ++m)
				B[m] = A[0][m] - b_sum[0][m];

			b_array[j] = B;
			float b_norm = 0;
			float b_norm_sum = 0;
			for (int i = 0; i < n; i++)
			{
				b_norm_sum += pow(B[i], 2.0);
			}
			b_norm = sqrt(b_norm_sum);

			// Установка новго направления
			for(int m=0; m<n; ++m)
				s[j][m] = B[m] / b_norm;
		}
		k += 1;
		cout << ">>> Iteration: " << k << endl;
	}

	if (k == MAX_ITERATIONS)
	{
		cout << "Warning: Max iterations exceeded!" << endl;
	}

	cout << "> Finished" << endl;
	cout << "> Iterations:" << k << endl;
	cout << "> Result: [ ";
		for (int i = 0; i < n; i++){
			cout << y[i];
			if (i != n-1)
				cout << ", ";
		}
		cout << " ]" << endl;
	cout << "> Function:" << function(y) << endl;

	return y;
}

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
	Rosenbrock(n1, function1, epsilon, a, b, delta1, x1);
	return 0;
}