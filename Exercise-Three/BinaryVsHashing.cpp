#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int overflowSpace(int d[], int value)
{
	int available = 10;
	
}

int hashFunction(int d[], int prefix, int value)
{
	int bucket = 3;
	int slot = 30;
	int index = 1;
	printf("value : %d\n", value);
	int seed = ( value - prefix );
	while ( seed >= slot )
	{
		seed /= slot;
	}
	printf("%d\n", seed);
	if( d[seed] == 0 )
	{
		d[seed] = value;
		return 1;
	}
	else{
		while(index<bucket)
		{
			if( d[seed+index] == 0 )
			{
				d[seed+index] = value;
				return 1;
			}
			index++;
		}
		return overflowSpace(d, value);
	}
}
int main( void )
{
	int A[1000] = { 0 };
	int B[1000] = { 0 };
	
	int r, cA, cB;
	cA = cB = 0;
	int size = sizeof( B ) / sizeof(1);
	B[0] = 500;
	for(int i = 1; i < size; i++ )
		B[i] = B[i-1] + ( rand() % 3 ) + 1;
	hashFunction(A, B[0], B[500]);
	
	getchar();
	return 0;
}

 
