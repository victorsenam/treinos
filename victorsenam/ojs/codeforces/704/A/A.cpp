#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 300007;

int fr[N], rd[N][2];
int v[N], lo, vs;
int n, q;
int res;
int t, x;

int main () {
    scanf("%d %d", &n, &q);

    res = 0;
    lo = vs = 0;

    for (int i = 0; i < q; i++) {
        scanf("%d %d", &t, &x);
        if (t == 1) {
            res++;
            fr[x]++;
            v[vs++] = x;
        } else if (t == 2) {
            res -= fr[x] - max(rd[x][0], rd[x][1]);
            rd[x][0] = fr[x];
        } else {
            int a = x;
            while (lo < a) {
                x = v[lo];

                if (rd[x][1] >= rd[x][0]) {
                    res--;
                }

                rd[x][1]++;
                lo++;
            }
        }
        printf("%d\n", res);
    }
}
