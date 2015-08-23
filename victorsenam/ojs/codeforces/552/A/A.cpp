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

int n;
int res;
int ar;
int xa, xb, ya, yb;

int main () {
    scanf("%d", &n);
    res = 0;
    while (n--) {
        scanf("%d %d %d %d", &xa, &ya, &xb, &yb);
        if (xb - xa + 1 > 0) ar = xb-xa+1;
        else ar = xa-xb+1;

        if (yb - ya + 1 > 0) ar *= (yb-ya+1);
        else ar *= (ya-yb+1);

        res += ar;
    }

    printf("%d\n", res);
}
