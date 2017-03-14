#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef ull num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 

num n;
num res;
num prox;
int dig;

int main () {
    scanf("%I64u", &n);
    res = 0;
    dig = 1;
    prox = 1;
    while (prox <= n) {
        prox *= 10;
        dig++;
    }

    prox /= 10;
    dig--;

    res += (n - prox + 1)*dig;

    while (prox > 0) {
        prox /= 10;
        dig--;

        res += 9*prox*dig;
    }

    printf("%I64u\n", res);
}
