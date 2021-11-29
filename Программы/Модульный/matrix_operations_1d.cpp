#include <math.h>

using namespace std;


/**
 * @brief Суммирование двух одномерных масивов.
 * 
 * @param array1 Указатель на одномерный массив в качестве первого слагаемого.
 * @param array2 Указатель на одномерныймассив в качестве второго слагаемого.
 * @param length Длина массивов
 * @return Указатель одномерный массив, содержащий сумму двух массивов.
 */
float* Array1dSum(float* array1, float* array2, int length)
{
	float *arraySum = new float[length]();
	for (int i = 0; i < length; i++)
	{
		arraySum[i] = array1[i] + array2[i];
	}
	return arraySum;
}

/**
 * @brief Проверка на равенство двух одномерных массивов.
 * 
 * @param array1 Указатель на первый одномерный массив.
 * @param array2 Указатель на второй одномерный массив.
 * @param length Длина массивов.
 * @return Истина, если матрицы равны поэлементно. Ложь, если матрицы отличаются хотябы одним элементом.
 */
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

/**
 * @brief Умножение одномерного массива на скаляр.
 * 
 * @param array Указатель на одномерный массив.
 * @param scalar Скаляр, на который будет умножен каждыйы элемент одномерного массива.
 * @param length Длина одномерного массива.
 * @return Указатель на одномерный массив, содержащий результат умножения.
 */
float* Array1dScalarMult(float* array, float scalar, int length)
{
	float *resultArray = new float[length]();
	for (int i = 0; i < length; i++)
	{
		resultArray[i] = array[i] * scalar;
	}
	return resultArray;
}

/**
 * @brief Разность двух одномерных массивов.
 * 
 * @param array1 Указатель на одномерный массив в качестве уменьшаемого.
 * @param array2 Указатель на одномерный массив в качестве вычитаемого.
 * @param length Длина массивов.
 * @return Указатель на одномерный массив, содержащий результат разности.
 */
float* Array1dDiff(float* array1, float* array2, int length)
{
	float *arraySum = new float[length]();
	for (int i = 0; i < length; i++)
	{
		arraySum[i] = array1[i] - array2[i];
	}
	return arraySum;
}

/**
 * @brief Норма одномерного массива
 * 
 * @param array Указатель на одномерный массив, для которого быдет вычисляться норма.
 * @param length Длина массива.
 * @return Скаляр, содержащий ному одномерного массива.
 */
float Array1dNorm(float* array, int length)
{
	float sum = 0.;
	for (int i = 0; i < length; i++)
	{
		sum += pow(array[i], 2.0);
	}
	return sqrt(sum);
}

/**
 * @brief Перевод одномерного масива в двумерный.
 * 
 * @param array Указатель на одномерный массив.
 * @param length Длина массива.
 * @return Указатель на двумерный массив размера 1×length, содержащий элементы одномерного.
 */
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

/**
 * @brief Сравнение каждого элемента массива со значением.
 * 
 * @param array Указатель на одномерный массив.
 * @param value Значение с которым будут сравниваться элементы одномерного массива.
 * @param length Длина массива.
 * @return Истина, если каждый элемент одномерного массива меньше скаляра. Ложь, если хотябы один элемент одномерного массива больше или равен скаляру.
 */
bool Array1dAbsLessThan(float* array, float value, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (abs(array[i]) >= value)
			return false;
	}
	return true;
}
