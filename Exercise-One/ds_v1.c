#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int A[1000000] = { 0 };
int DD1[1][1000000][3] = { 0 };

void insertD1(int ds[], int size, int value, int data[][1000000][3], int d1, int index, int d3);
void printSingleArray(int ds[], int size);
void D1(int ds[], int size, int data[][1000000][3], int d1, int d2, int d3);
void printMultiArray(int ds[][1000000][3], int d1, int d2, int d3);
void refreshSingleArray(int ds[], int size);
int main()
{
	srand(time(NULL));
	int d1 = 1;
	int d2 = 1000000;
	int sizeA = sizeof(A) / 4;
	D1(A, sizeA, DD1, d1, d2, 3);
	getchar();
	return 0;
}

void refreshSingleArray(int ds[], int size) {
	for (int i = 0; i < size; i++)
		ds[i] = 0;
}
void D1(int ds[], int size, int data[][1000000][3], int d1, int d2, int d3) {
	int value;
	for (int i = 0; i < d1; i++) {
		for (int j = 0; j < d2; j++) {
			printf("tick(%d)\n", j);
			value = rand() % 10 + 1;
			insertD1(ds, size, value, data, i, j, d3);
		}
		//printSingleArray( ds, size );
		refreshSingleArray(ds, size);
	}
	//printMultiArray( data, d1, d2, d3 );
	int maxC = data[0][0][1], maxM = data[0][0][2];
	long totC = 0, totM = 0;
	double avgC = 0, avgM = 0;
	for (int i = 0; i < d1; i++) {
		for (int j = 0; j < d2; j++)
		{
			totC += data[i][j][1];
			totM += data[i][j][2];
			if (data[i][j][1] > maxC)
				maxC = data[i][j][1];
			if (data[i][j][2] > maxM)
				maxM = data[i][j][2];
		}
		avgC += (totC / (double)d2);
		avgM += (totM / (double)d2);
		totC = 0; totM = 0;
	}
	printf("Max Comparison : %8d, Max Movement : %8d\n", maxC, maxM);
	printf("Average Comparison : %3.4lf, Average Movement : %3.4lf\n", avgC / (double)d1 , avgM / (double)d1 );
	printf("Comparison %3.4lf , Movement %3.4lf", avgC * 100 / (double)d1 / (double)d2, avgM * 100 / (double)d1 / (double)d2);
}

void insertD1(int ds[], int size, int value, int data[][1000000][3], int d1, int index, int d3) {
	int temp;
	int temptemp;
	int flag = 0;
	data[d1][index][0] = value;
	for (int i = 0; i < size; i++) {
		data[d1][index][1]++;
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
			data[d1][index][2]++;
			data[d1][index][1]--;
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

void printMultiArray(int ds[][1000000][3], int d1, int d2, int d3) {
	for (int i = 0; i < d1; i++)
	{
		for (int j = 0; j < d2; j++)
		{
			for (int k = 0; k < d3; k++)
				printf("%2d ", ds[i][j][k]);
			puts("");
		}
		puts("");
	}
	puts(""); puts("");
}