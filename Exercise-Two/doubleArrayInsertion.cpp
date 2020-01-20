#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insert( int ds[], int size, int value, long *comparison, unsigned long *movement )
{
  int temp, flag = 0;
  for( int i = 0; i < size; i++ )
  {
  	*comparison++;
    if( ds[i] > value && flag == 0 )
    {
      temp = ds[i];
      ds[i] = value;
      flag = 1;
      continue;
    }
    if( flag == 1 )
    {
      *movement++;
      value = ds[i];
      ds[i] = temp;
      temp = value;
      if( temp == 0 )
        break;
      continue;
    }
    if( ds[i] == 0 )
    {
      ds[i] = value;
      break;
    }
  }
}

int a[500000] = { 0 };
int b[500000] = { 0 };
  
int main( void )
{
  
  int temp, flag, r;
  srand( time( NULL ));
  int halfSize = sizeof( a ) / 4;
  long comparison = 0;
  unsigned long movement = 0;
  long start_t, end_t, diff_t;
  start_t = clock();
  for( int m = 0; m < 1000000; m++ )
  {
    r = ( rand() % 1000000 ) + 1;
    //printf("%d ", r);
    flag = 0;
    comparison++;
    if( b[0] != 0 && r >= b[0] )
    {
      //printf(" skip ");
      insert( b, halfSize, temp, &comparison, &movement );
      continue;
    }
    for( int i = 0; i < halfSize; i++ )
    {
      if( a[i] > r && flag == 0)
      {
      	comparison++;
        //printf("insert %d at %d\n", r, a[i]);
        temp = a[i];
        a[i] = r;
        flag = 1;
        if( i == halfSize - 1 )
        {
          comparison++;
          insert( b, halfSize, temp, &comparison, &movement );
          break; 
		}
        continue;
      }
      if( flag == 1 )
      {
      	movement++;
        r = a[i];
        a[i] = temp;
        temp = r;
        //printf("swaping %d \n", temp);
        if( temp == 0 )
        {
          break;
        }
        if( i == halfSize - 1 && temp != 0 )
        {
          comparison++;
          //printf(" send %d over \n", temp);
          insert( b, halfSize, temp, &comparison, &movement );
          break; 
        }
        continue;
      }
      if( a[i] == 0 )
      {
        //printf("direct\n");
        a[i] = r;
        break;
      }
      if( i == halfSize - 1 && a[i] != 0 )
        {
          //printf("add to a2\n");
          insert( b, halfSize, temp, &comparison, &movement );
          break; 
        }
    }
  }
  end_t = clock();
  diff_t = end_t - start_t;
  double timeElapsed = ( double )diff_t / CLOCKS_PER_SEC;
  puts("");
  puts("A");
  /*
  for( int k = 0; k < halfSize; k++ )
  {
    printf("%d ", a[k]);
  }
  puts("");
  puts("B");
  for( int k = 0; k < halfSize; k++ )
  {
    printf("%d ", b[k]);
  }
  */
  printf("\ntotal comparison : %ld\n", comparison);
  printf("total movement : %llu\n", movement);
  printf("time elapsed : %lf\n", timeElapsed);
}

