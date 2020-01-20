#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


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
int hashFunctionHead( int m[40][40], int size, int value)
{
	int factor = 100000;
	int seed = value / factor;
	int x = 0;
	while( seed > 39 )
	{
		seed -= 39;
		x++;
	}
	printf("%d\n", x);
	if( m[x][1] == 0 )
	{
		m[x][1] = value;
		return 1;
	}
	else
	{
		return linearProbing( m, size, x, 1, value);
	}
	return 0;
}
int hashFunctionTail( int m[40][40], int size, int value )
{				 
	int factor = 10000000;
	int seed = value, temp, result, x;
	temp = result = x = 0;
	printf("seed %d : ", seed);
	while( seed >= 10000 )
	{
		seed = seed % factor;
		factor /= 10;
	}
	printf("%d\n", seed);
	while( seed >= size )
	{
		seed -= size;
		x++;
	}
	
	while( x >= size )
	{
		x -= size;
	}
	printf("x : %d \n", x);
	if( m[x][1] == 0 )
	{
		m[x][1] = value;
		return 1;
	}
	else
	{
		return linearProbing( m, size, x, 1, value);
	}
	return 0;
}
int hashFunctionLastTwo(int m[40][40], int size, int value)
{
	int factor = 10000000;
	int seed = value, x = 0;
	// printf("seed %d : ", seed);
	while( seed >= 100 )
	{
		seed = seed % factor;
		factor /= 10;
	}
	printf("%d\n", seed);
	while( seed >= size )
	{
		seed -= size;
	}
	
	if( m[seed][1] == 0 )
	{
		m[seed][1] = value;
		return 1;
	}
	else
	{
		return linearProbing( m, size, seed, 1, value);
	}
	return 0;
}
int linearSearch(int m[40][40], int size, int x, int y, int key, int *comparison )
{
	for(int i = x; i < size; i++ )
	{
		for( int j = y+1; j < size; j++ )
		{
			*comparison += 1;
			//printf("compare %d \n", *comparison);
			if( m[i][j] == key )
			{
				return m[i][j];
			}
		}
	}
	return 0;
}

int searchHead(int m[40][40], int size, int key, int *comparison ){
	*comparison = 0;
	int factor = 100000;
	int seed = key / factor;
	int x = 0;
	while( seed > 39 )
	{
		seed -= 39;
		x++;
	}
	printf("%d\n", x);
	if( m[x][1] == key )
	{
		*comparison += 1;
		//printf("compare %d \n", *comparison);
		return m[x][1];
	}
	else
	{
		return linearSearch(m, size, x, 1, key, comparison);
	}
	return 0;
}

int searchTail(int m[40][40], int size, int key, int *comparison )
{
	*comparison = 0;
	int factor = 10000000;
	int seed = key, x = 0;
	// printf("seed %d : ", seed);
	while( seed >= 10000 )
	{
		seed = seed % factor;
		factor /= 10;
	}
	printf("%d\n", seed);
	while( seed >= size )
	{
		seed -= size;
		x++;
	}
	
	while( x >= size )
	{
		x -= size;
	}
	printf("x : %d \n", x);
	if( m[x][1] == key )
	{
		*comparison++;
		return m[x][1];
	}
	else
	{
		return linearSearch( m, size, x, 1, key, comparison);
	}
	return 0;
}
int searchLastTwo(int m[40][40], int size, int key, int *comparison )
{
	*comparison = 0;
	int factor = 10000000;
	int seed = key, x = 0;
	// printf("seed %d : ", seed);
	while( seed >= 100 )
	{
		seed = seed % factor;
		factor /= 10;
	}
	printf("%d\n", seed);
	while( seed >= size )
	{
		seed -= size;
	}
	
	
	printf("x : %d \n", x);
	if( m[seed][1] == key )
	{
		*comparison++;
		return m[seed][1];
	}
	else
	{
		return linearSearch( m, size, seed, 1, key, comparison);
	}
	return 0;
}
int main(void)
{
	int headMatrix[40][40] = { 0 };
	int tailMatrix[40][40] = { 0 };
	int lastTwoMatrix[40][40] = { 0 };
	int data[31] = { 105514220, 104316219, 105316147, 105316138, 106316127, 105316145, 106316156, 106316105, 106316158, 105313140, 106316137, 106316106, 106316111, 106316115, 106316116, 106316119, 106316152, 106316147, 106316130, 106316136, 105316109, 106316144, 106316120, 106316149, 106316151, 105316143, 106316154, 106316155, 106316143, 106316157, 105316163 };
	int size = sizeof( data ) / 4;
	int head = 0;
	int tail = 0;
	int lastTwo = 0;
	int diff[31] = { 0 };
	double result = 0;
	double enhanced = 0;
	for( int i = 0; i < size; i++ )
	{
		//printf("hashed index : %d\n", hashFunctionSum(matrix, 31, data[i]));
		printf("NO. %d, %d ", i, data[i]);
		printf("%d was %s\n", data[i], ( hashFunctionHead(headMatrix, 40, data[i]) == 1 ) ? "inserted" : "not inserted" );
		printf("%d was %s\n", data[i], ( hashFunctionTail(tailMatrix, 40, data[i]) == 1 ) ? "inserted" : "not inserted" );
		hashFunctionLastTwo(lastTwoMatrix, 40, data[i]);
	}
	for(int i = 0; i < size; i++ )
	{
		printf("Head %d %s at %d comparison\n", data[i], (searchHead(headMatrix, 40, data[i], &head)!=0)?"Found":"Not Found", head);
		printf("Tail %d %d at %d comparison\n", data[i], searchTail(tailMatrix, 40, data[i], &tail), tail);
		printf("LastTwo %d %d at %d comparison\n", data[i], searchLastTwo(lastTwoMatrix, 40, data[i], &lastTwo), lastTwo);
		result += ( head - tail );
		enhanced += ( tail - lastTwo );
	}
	result /= size;
	enhanced /= size;
	printf("avg : %lf\n", result );
	printf("enhanced %lf\n", enhanced );
	if( result > enhanced )
		printf("Tail version is more efficient\n");
	else if ( result < enhanced )
		printf("Enhanced version is more efficient\n");
	else
		printf("Diff is not significant");
		
	getchar();
	return 0;
}
