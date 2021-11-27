#include <iostream>
#include <sstream>
#include <math.h>

using namespace std;

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 2)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

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
