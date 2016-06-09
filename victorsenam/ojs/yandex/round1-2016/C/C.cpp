#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 10;
const int pt[30] = {100, 75, 60, 50, 45, 40, 36, 32, 29, 26, 24, 22, 20, 18, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

int df[N];
int cnt;

int main () {
    for (int i = 0; i < 10; i++)
        scanf("%d", df+i);

    int k;
    bool ok = 0;
    for (k = 29; k >= 0; k--) {
        int p = 0;
        for (int i = 9; !ok && i >= 0; i--) {
            if (p == k) p++;
            if (df[i] + pt[p++] - pt[k] < 0)
                ok = 1;
        }
        if (ok) break;
    }

    printf("%d\n", k+1);
}
