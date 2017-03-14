#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = (1<<17);

int n;
int d[N], x[N];
int qu[N], qi, qf;
int res[N][2], rs;

int main () {
    scanf("%d", &n);

    qi = qf;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", d+i, x+i);
        if (d[i] == 1)
            qu[qf++] = i;
    }

    rs = 0;
    while (qi < qf) {
        int u = qu[qi++];
        if (!d[u]) continue;

        res[rs][0] = u;
        res[rs][1] = x[u];
        rs++;
        d[x[u]]--;
        x[x[u]] ^= u;
        if (d[x[u]] == 1)
            qu[qf++] = x[u];
    }

    printf("%d\n", rs);
    for (int i = 0; i < rs; i++) {
        printf("%d %d\n", res[i][0], res[i][1]);
    }
}

