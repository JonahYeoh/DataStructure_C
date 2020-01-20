#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int A[1000000] = { 0 };
int DD1[1000000][3] = { 0 };

void insertD1(int ds[], int size, int value, int data[1000000][3], int index, int d3);
void printSingleArray(int ds[], int size);
void D1(int ds[], int size, int [1000000][3],int d2, int d3);
void printMultiArray(int ds[1000000][3], int d2, int d3);
void refreshSingleArray(int ds[], int size);
int main()
{
	srand(time(NULL));
	int d2 = 1000000;
	int sizeA = sizeof(A) / 4;
	clock_t t;
	t = clock();
	D1(A, sizeA, DD1, d2, 3);
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds 
	printf("took %f seconds to execute \n", time_taken);
	getchar();
	return 0;
}

void refreshSingleArray(int ds[], int size) {
	for (int i = 0; i < size; i++)
		ds[i] = 0;
}
void D1(int ds[], int size, int data[1000000][3], int d2, int d3) {
	int value;
	for (int j = 0; j < d2; j++) {
		//printf("tick(%d)\n", j);
		value = rand() % 10 + 1;
		insertD1(ds, size, value, data, j, d3);
	}
	refreshSingleArray(ds, size);
	int maxC = data[0][1], maxM = data[0][2];
	long totC = 0, totM = 0;
	double avgC = 0, avgM = 0;
	for (int j = 0; j < d2; j++)
	{
		totC += data[j][1];
		totM += data[j][2];
		if (data[j][1] > maxC)
			maxC = data[j][1];
		if (data[j][2] > maxM)
			maxM = data[j][2];
	}
	avgC += (totC / (double)d2);
	avgM += (totM / (double)d2);
	printf("Total Comparison : %ld\n", totC);
	printf("Total Movement : %ld\n", totM);
	printf("Max Comparison : %8d, Max Movement : %8d\n", maxC, maxM);
}

void insertD1(int ds[], int size, int value, int data[1000000][3], int index, int d3) {
	int temp;
	int temptemp;
	int flag = 0;
	data[index][0] = value;
	for (int i = 0; i < size; i++) {
		data[index][1]++;
		if (ds[i] == 0 && flag == 0) {
			ds[i] = value;
			return;
		}
		if (ds[i] > value && flag == 0) {
			temp = ds[i];
			ds[i] = value;
			flag = 1;
			continue;
		}
		if (flag == 1) {
			temptemp = ds[i];
			ds[i] = temp;
			temp = temptemp;
			data[index][2]++;
			data[index][1]--;
			if (temptemp == ds[i + 1] && temptemp == 0)
				break;
		}
	}
}

void printSingleArray(int ds[], int size) {
	for (int i = 0; i < size; i++)
		printf("%2d ", ds[i]);
	puts(""); puts("");
}

void printMultiArray(int ds[1000000][3], int d2, int d3) {
		for (int j = 0; j < d2; j++)
		{
			for (int k = 0; k < d3; k++)
				printf("%2d ", ds[j][k]);
			puts("");
		}
		puts("");
	puts(""); puts("");
}