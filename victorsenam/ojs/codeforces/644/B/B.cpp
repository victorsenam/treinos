#include <bits/stdc++.h>

using namespace std;

const int N = 200007;

int qu[N], qi, qf;
int n, b;
int t[N], d[N], r[N];
int nx;

int main () {
    scanf("%d %d", &n, &b);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", t+i, d+i);
        r[i] = -1;
    }
    t[n] = INT_MAX; d[n] = 0;
    r[n] = -1;

    nx = 0;
    for (int i = 0; i <= n; i++) {
        qu[qf++] = i;
        while (nx <= t[i] && qi < qf) {
            nx += d[qu[qi]];
            r[qu[qi]] = nx;
            qi++;
        }
        while (qf - qi > b) qf--;
    }

    for (int i = 0; i < n; i++) {
        printf("%d\n", r[i]);
    }
}
