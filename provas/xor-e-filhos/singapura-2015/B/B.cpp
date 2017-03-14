#include <bits/stdc++.h>

using namespace std;
int n = 98;

int main () {
	printf("200\n");
	for (int i = 0; i < 98; i++)
		printf("v");
	for (int i = 0; i < 99; i++)
		printf("^");
	printf("<");
	printf("v");
	printf("\n");
	
	for (int i = 0; i < 200; i++)
		printf("#");
	printf("\n");
	for (int i = 0; i < 198; i++) {
		printf("#");
		for (int j= 0; j < 197; j++)
			printf(".");

		if (i)
			printf(".");
		else
			printf("R");
		printf("#\n");
	}
	for (int i = 0; i < 200; i++)
		printf("#");
	printf("\n");
}
