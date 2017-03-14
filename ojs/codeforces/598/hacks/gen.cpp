#include <bits/stdc++.h>

using namespace std;

const int N = 1000;
const int K = 100000;

int main () {
    printf("%d %d %d\n", N, N, K);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0 || j == 0 || i == N-1 || j == N-1)
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
    int k = 0;
    for (int i = 1; i < N-1 && k < K; i++) 
        for (int j = 1; j < N-1 && k < K; j++) {
            printf("%d %d\n", i+1, j+1);
            k++;
        }
}
