#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int matrix[40][40] = { 0 };

int linearProbing( int m[40][40], int size, int x, int y, int value)
{
	for(int i = x; i < size; i++ )
	{
		for( int j = y+1; j < size; j++ )
		{
			if( m[i][j] == 0 )
			{
				m[i][j] = value;
				return 1;
			}
		}
	}
	return 0;
}

int hashFunctionSum(int m[40][40], int size, int value)
{
	int factor = 100000;
	int seed = value / factor;
	factor /= 10;
	int t = 0;
	int result = 0;
	printf("%d ", seed);
	while( factor != 1 )
	{
		factor /= 10;
		t = seed/factor;
		printf("%d ", t);
		seed -= t * factor;
		result += t;
	}
	return result;
}
int hasFunctionModDiv( int m[40][40], int size, int value)
{
	int factor = 100000;
	int seed = value / factor;
	int x = 0, y;
	while( seed > 39 )
	{
		seed -= 39;
		x++;
	}
	y = seed;
	printf("%d, %d\n", x, y);
	if( m[x][y] == 0 )
	{
		m[x][y] = value;
		return 1;
	}
	else
	{
		return linearProbing( m, size, x, y, value);
	}
	return 0;
}

int main(void)
{
	int data[31] = { 105514220, 104316219, 105316147, 105316138, 106316127, 105316145, 106316156, 106316105, 106316158, 105313140, 106316137, 106316106, 106316111, 106316115, 106316116, 106316119, 106316152, 106316147, 106316130, 106316136, 105316109, 106316144, 106316120, 106316149, 106316151, 105316143, 106316154, 106316155, 106316143, 106316157, 105316163 };
	int size = sizeof( data ) / 4;
	for( int i = 0; i < size; i++ )
	{
		//printf("hashed index : %d\n", hashFunctionSum(matrix, 31, data[i]));
		printf("%d was %s\n", data[i], ( hasFunctionModDiv(matrix, size, data[i]) == 1 ) ? "inserted" : "not inserted" );
	}		
	getchar();
	return 0;
}
