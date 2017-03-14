#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e7;

int v[N];
int r[N];
int n;

int main () {
    scanf("%d", &n);
    int ans = n;

    int m = 2;
    int gt = 4;
    bool a = 0;

    printf("%d\n", ans);
    while (m <= n && gt <= n) {
        int diff = n/m - (gt-1)/m;
        printf("%d %d\n", m, gt);
        printf("%d = %d - %d\n", diff, n/m, (gt-1)/m);
        if (a) {
            ans += diff;
        } else {
            ans -= diff;
        }
        a = !a;

        m *= 2;
        gt *= 2;
        gt += 2;
    }

    printf("%d\n", ans);
}
