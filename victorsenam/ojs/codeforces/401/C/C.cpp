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
bool flag;

int main () {
    scanf("%d %d", &m, &n);
    if (m > n+1 || n > 2*(m+1)) {
        printf("-1\n");
        return 0;
    }

    if (m > n) {
        printf("0");
        m--;
    }

    while (n > m && n > 1 && m > 0) {
        printf("110");
        m--;
        n-=2;
    }

    while (n > 0 && n == m) {
        printf("10");
        n--;
        m--;
    }

    while (n > 0) {
        printf("1");
        n--;
    }

    printf("\n");
}
