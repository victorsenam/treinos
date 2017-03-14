#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

int n, d, h;

int main () {
    scanf("%d %d %d", &n, &d, &h);

    if (d == 1) {
        if (n == 2 && h == 1) {
            printf("1 2\n");
        } else {
            printf("-1\n");
        }
        return 0;
    }

    if (n <= d || n <= h || d < h || h+h < d) {
        printf("-1\n");
        return 0;
    }

    for (int i = 2; i <= h+1; i++)
        printf("%d %d\n", i-1, i);
    int ls = 1;
    for (int i = h+2; i <= d+1; i++) {
        printf("%d %d\n", ls, i);
        ls = i;
    }

    for (int i = d+2; i <= n; i++)
        printf("%d %d\n", 1+(d==h), i);
}
