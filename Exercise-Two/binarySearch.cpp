#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int ds[1000000] = { 0 };
int binarySearch(int ds[], int size, int t, long *tracker)
{
	//printf("Searching for %d\n", t);
	int left, right, mid, eos = 0;
	int currentIndex = size;
	
	left = 0;
	right = size;
	currentIndex = (right - left ) / 2;
	while( eos == 0 )
	{
		*tracker = *tracker + 1;
		//printf("Round %ld\n", *tracker);
		//printf("currentIndex : %d\n", currentIndex);
		//printf("current value : %d\n", ds[currentIndex]);
		if( ds[currentIndex] == t )
		{
			return 1;
		}
		if( ds[currentIndex] > t )
		{
			//puts("too big");
			//getchar();
			right = currentIndex;
			//currentIndex = ( right - left ) / 2 + left;
			//continue;
		}
		if( ds[currentIndex] < t )
		{
			//puts("too small");
			//getchar();
			left = currentIndex;
			
			//continue;
		}
		if( currentIndex == 0 || currentIndex == size-1 || left == right - 1)
		{
			eos = 1;
			//puts("xx");
			return 0;
		}
		currentIndex = ( right - left ) / 2 + left;
	}

}
int main( void )
{
	srand(time(NULL));
	int t, output;
	// unsigned long start_t, end_t;
	// unsigned long comparison, movement;
	long tracker = 0;
	int loopSize = 1000;
	int size = sizeof( ds ) / 4;
	ds[1] = 1;
	for(int i = 0; i < size; i++ )
		ds[i] = ds[i-1] + ( rand() % 10 ) + 1;
	for( int k = 0; k < loopSize; k++ )
	{
		t = ( rand() % 10000 ) + 1;
		output = binarySearch( ds, size, t, &tracker );
		printf("%d was %s\n", t, (output==1)?"found":"not found");
	}
	printf("Called binarySearch function %d times\n", loopSize);
	printf("%ld comparision made and average about %lf made on each search\n", tracker, (double)tracker/loopSize);
	getchar();
	return 0;
}
