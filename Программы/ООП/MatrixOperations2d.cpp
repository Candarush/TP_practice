#include <math.h>

using namespace std;

class MatrixOperations2d
{
	public:
	
	static float** Array2dSum(float** array1, float** array2, int cols, int rows)
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

	static float** Array2dDiff(float** array1, float** array2, int cols, int rows)
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

	static float** Array2dTranspose(float** array, int width, int height)
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

	static float** Array2dMult(float** array1, int width1, int height1, float** array2, int width2, int height2)
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
};
