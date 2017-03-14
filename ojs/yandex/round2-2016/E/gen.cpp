#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 200000;

int main () {
    srand(time(NULL));
    printf("%d\n", N);

    for (int i = 0; i < N; i++)
        printf("%d ", rand()%N+1);
    printf("\n");

    for (int i = 1; i < N; i++)
        printf("%d %d\n", i%(N)+1, rand()%i+1);
}
