#include <iostream>
#include <sstream>
#include <math.h>

using namespace std;

/**
 * @brief Перевод дробого десятичного числа в стоку.
 * 
 * @tparam T Тип значения.
 * @param a_value Значение.
 * @param n Количество цифр после запятой.
 * @return Строка, содержащая число с n цифор после зхапятой.
 */
template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 2)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

/**
 * @brief Перевод одномерного массива в строку.
 * 
 * @param array Указатель на одномерный массив.
 * @param length Длина одномерного массива.
 * @return Строка, содержащая элементы мыссива.
 */
string String1dArray(float* array, int length)
{
	string str = "";
	str += "[ ";
	for (int i = 0; i < length; i++)
	{
		str += to_string_with_precision(array[i], 2);
		if (i != length-1)
			str += ", ";
	}
	str += " ]";
	return str;
}

/**
 * @brief Перевод двумерного массива в строку.
 * 
 * @param array Указатель на двумерный массив.
 * @param cols Количество столбцов.
 * @param rows Количество строк.
 * @return Строка, содержащая элементы двумерного массива. Строки массива разделены знаком новой строки '\\n'.
 */
string String2dArray(float** array, int cols, int rows)
{
	string str = "";
	for (int i = 0; i < rows; i++)
	{
		str += String1dArray(array[i], cols);
		if (i != rows-1)
			str += "\n";
	}
	return str;
}
