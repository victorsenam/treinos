#include <bits/stdc++.h>

using namespace std;

const int N = 107;
const int M = 3007;
const int MAX = 100007;

bool vis[N];
int pv[N*M], nx[N*M], cyc[N], to[N*M], es;
int a, b;
int m, n, r;

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &m);
        scanf("%d", &a);
        nx[es] = pv[es] = cyc[i] = es;
        to[es++] = a;
        for (int j = 0; j < m-1; j++) {
            scanf("%d", &a);
            nx[es] = cyc[i];
            pv[es] = pv[cyc[i]];
            pv[cyc[i]] = es;
            to[es++] = b;
        }
        scanf("%d", &a);
    }

    
}
