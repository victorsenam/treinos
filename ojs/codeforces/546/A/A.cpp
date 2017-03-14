#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%d| ", __LINE__); fprintf(stderr, __VA_ARGS__)
#else
#define debug(...) //
#endif

using namespace std;

#define N 

typedef unsigned long long int num;

int main () {
    num n, k, w;

    scanf("%I64u %I64u %I64u", &k, &w, &n);

    if (k*n*(n+1)/2 < w) printf("0\n");
    else printf("%I64u\n", k*n*(n+1)/2-w);
}
