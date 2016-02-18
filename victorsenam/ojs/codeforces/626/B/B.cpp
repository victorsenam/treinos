#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

int r, b, g;
int n;
char c;

int main () {
    scanf("%d", &n);
    r = b = g = 0;
    for (int i = 0; i < n; i++) {
        scanf(" %c", &c);
        if (c == 'R')
            r++;
        else if (c == 'B')
            b++;
        else
            g++;
    }
    if ((r && b && g) || (r > 1 && g > 1) || (b > 1 && g > 1) || (r > 1 && b > 1)) {
        r = b = g = 1;
    } else if (r == b) {
        g = 1; r = b = 0;
    } else if (g == r) {
        b = 1; g = r = 0;
    } else if (b == g) {
        r = 1; b = g = 0;
    } else if (r > 1) {
        r = 0; g = b = 1;
    } else if (g > 1) {
        g = 0; r = b = 1;
    } else {
        b = 0; g = r = 1;
    }

    if (b)
        printf("B");
    if (g)
        printf("G");
    if (r)
        printf("R");
    printf("\n");
}
