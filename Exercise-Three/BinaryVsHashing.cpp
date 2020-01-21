#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int overflowSpace(int d[], int value)
{
	int available = 10;
	while ( available )
	{
		if( d[1000-available]==0 )
		{
			d[1000-available] = value;
			return 2;
		}
		available--;
	}
	int index = 0;
	while( index < 1000 )
	{
		if( d[index] == 0)
		{
			d[index] = value;
			return 3;
		}
		index--;
	}
	return 0;
}

int hashFunction(int d[], int prefix, int value)
{
	int bucket = 3;
	int slot = 330;
	int index = 1;
	int seed = ( value - prefix ) % slot * bucket;
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
int linearProbing(int d[], int size, int key, int *comparison )
{
	int available = 10;
	while ( available )
	{
		*comparison += 1;
		if( d[1000-available] == key )
			return 1000-available;
		available--;
	}
	int index = 0;
	while( index < 1000 )
	{
		*comparison += 1;
		if( d[index] == key )
			return index;
		index--;
	}
	return 0;
}
int hashSearch(int d[], int prefix, int size, int key, int *comparison )
{
	int bucket = 3;
	int slot = 330;
	int index = 1;
	int seed = ( key - prefix ) % slot * bucket;
	*comparison = 0;
	if( d[seed] == key ){
		*comparison += 1;
		return seed;
	}
	else
	{
		while( index<bucket )
		{
			*comparison += 1;
			if( d[seed+index] == 0 )
				return seed;
			index++;
		}
		return linearProbing(d, size, key, comparison );
	}
}


int binarySearch(int ds[], int size, int t, long *tracker)
{
	int left, right, currentIndex, eos;
	*tracker = 0;
	left = eos = 0;
	right = size;
	currentIndex = (right - left ) / 2;
	while( eos == 0 )
	{
		*tracker = *tracker + 1;
		if( ds[currentIndex] == t )
		{
			return 1;
		}
		if( ds[currentIndex] > t )
		{
			right = currentIndex;
		}
		if( ds[currentIndex] < t )
		{
			left = currentIndex;
		}
		if( currentIndex == 0 || currentIndex == size-1 || left == right - 1)
		{
			eos = 1;
			return 0;
		}
		currentIndex = ( right - left ) / 2 + left;
	}
}

int main( void )
{
	int A[1000] = { 0 };
	int B[1000] = { 0 };
	int output = 0;
	int failure = 0;
	int success = 0;
	int r, cA, cB;
	cA = cB = 0;
	int size = sizeof( B ) / sizeof(1);
	srand(time(NULL));
	double data[4] = { 0 };
	for(int k = 0; k < size; k++ )
	{
		printf("tick() %d\n", k);
		for(int i = 1; i < size; i++ )
		{
			if( i == 0 )
			{
				B[i] = 500;
			}
			else
			{
				B[i] = B[i-1] + ( rand() % 3 ) + 1;
			}
			output = hashFunction(A, B[0], B[i]);
			if( output == 2 )
				cA++;
			else if( output == 3 )
				cB++;
			else if( output == 0 )
				failure++;
			else if( output == 1 )
				success++;
		}
		data[0] += cA;
		cA = 0;
		data[1] += cB;
		cB = 0;
		data[2] += failure;
		failure = 0;
		data[3] += success;
		success = 0;
		if( k != 999 )
		{
			for(int i = 0; i < size; i++ )
			{
				A[i] = 0;
			}
		}
	}
	
	printf("freeSpace : %lf\n", data[0]/size);
	printf("openSpace : %lf\n", data[1]/size);
	printf("failure   : %lf\n", data[2]/size);
	printf("successed : %lf\n", data[3]/size);
	
	int compare = 0;
	long bin = 0;
	cA = 0;
	cB = 0;
	for(int i = 0; i < size; i++ )
	{
		r = rand() % size;
		output = hashSearch(A, 500, 1000, data[r], &compare );
		cA += compare;
		binarySearch(B, size,data[r], &bin);
		cB += bin;		
	}	
	
	printf("Average score by hashSearch : %lf\n", (double)cA/size);
	printf("Average score by binary search : %lf\n", (double)cB/size);
	
	getchar();
	return 0;
	
}

 
