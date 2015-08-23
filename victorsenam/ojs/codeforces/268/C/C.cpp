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

    printf("%d\n", min(n, m)+1);

    for (int i = 0; i <= min(n, m); i++)
        printf("%d %d\n", i, min(n,m)-i);
}
