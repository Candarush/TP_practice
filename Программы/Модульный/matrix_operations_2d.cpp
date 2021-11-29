#include <iostream>
#include <math.h>

using namespace std;

/**
 * @brief Сумма двух двумерных массивов.
 * 
 * @param array1 Указатель на двумерный массив в качестве первого слагаемого.
 * @param array2 Указатель на двумерный массив в качестве второго слагаемого.
 * @param cols Количество столбцов в матрицах.
 * @param rows Количество строк в матрицах.
 * @return Указатель двумерный массив, содержащий сумму двух массивов.
 */
float** Array2dSum(float** array1, float** array2, int cols, int rows)
{
	float **arraySum = new float*[rows];
	int i, j;
	for (i = 0; i < rows; i++)
		arraySum[i] = new float[cols]();

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			arraySum[i][j] = array1[i][j] + array2[i][j];
		}
	}
	return arraySum;
}

/**
 * @brief Разность двух двумерных массивов.
 * 
 * @param array1 Указатель на двумерный массив в качестве уменьшаемого.
 * @param array2 Указатель на двумерный массив в качестве вычитаемого.
 * @param cols Количество столбцов в матрицах.
 * @param rows Количество строк в матрицах.
 * @return Указатель двумерный массив, содержащий разность двух массивов.
 */
float** Array2dDiff(float** array1, float** array2, int cols, int rows)
{
	float **arraySum = new float*[rows];
	int i, j;
	for (i = 0; i < rows; i++)
		arraySum[i] = new float[cols]();

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			arraySum[i][j] = array1[i][j] - array2[i][j];
		}
	}
	return arraySum;
}

/**
 * @brief Транспонирование двумерного массива.
 * 
 * @param array Указатель на двумерный массив.
 * @param width Количество столбцов в матрицах.
 * @param height Количество строк в матрицах.
 * @return Указатель на транспонированный массив.
 */
float** Array2dTranspose(float** array, int width, int height)
{
	float **result = new float*[height];
	int i, j;
	for (i = 0; i < width; i++)
		result[i] = new float[height]();
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			result[i][j] = array[j][i];
		}
	}
	return result;
}

/**
 * @brief Произведение двух двумерных массивов.
 * 
 * @param array1 Указатель на первый двумерный массив.
 * @param width1 Количество столбцов в первом массиве.
 * @param height1 Количество строк в первом массиве.
 * @param array2 Указатель на второй двумерный массив.
 * @param width2 Количество столбцов в втором массиве.
 * @param height2 Количество строк в втором массиве.
 * @return Указатель на двумерный массив содержащий произведение двух маатриц.
 */
float** Array2dMult(float** array1, int width1, int height1, float** array2, int width2, int height2)
{
	float **result = new float*[height1];
	int i, j, k;
	for (i = 0; i < height1; i++)
		result[i] = new float[width2]();
	for(i=0; i<height1; ++i)
    	for(j=0; j<width2; ++j)
    		for(k=0; k<width1; ++k)
			{
				result[i][j] += array1[i][k]*array2[k][j];
			}
	return result;
}