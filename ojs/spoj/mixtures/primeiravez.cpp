/*
Eu resolvi passar esse problema de novo
Esse é o código da primeira vez que eu passei :)
*/

#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 100

int cost[N][N];
int res[N+1];
int n;

inline int getVal(int a) {
    return (a+100)%100;
}

int pd (int i, int j) {
    if (cost[i][j] != -1) return cost[i][j];
    
    int a = INT_MAX;
    for (int k = i; k < j; k++)
        a = min(pd(i, k) + pd(k+1, j) + getVal(res[k+1]-res[i])*getVal(res[j+1]-res[k+1]), a);
    
    cost[i][j] = a;
    return a;
}

int main () {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cost[i][j] = -1;

        res[0] = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", res+i+1);
            res[i+1] += res[i];
            res[i+1] %= 100;
            cost[i][i] = 0;
        }

        printf("%d\n", pd(0, n-1));
    }
}
