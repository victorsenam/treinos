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

#define N 

int n, m;

int main () {
    scanf("%d %d", &n, &m);

    if (n == 1)
        printf("1\n");
    else if (m > n/2)
        printf("%d\n", m-1);
    else
        printf("%d\n", m+1);
}
