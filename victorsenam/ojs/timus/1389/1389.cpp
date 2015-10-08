#include <bits/stdc++.h>

using namespace std;

const int N = 100000;

int memo[N][2];
int res[N][2];
int hd[N], nx[2*N], to[2*N], es;
int a, b;
int n, m;
int toout[N], os;

int pd (int v, bool u, int p) {
    int & me = memo[v][u];
    if (me != -1)
        return me;

    int sum = 0;
    me = 0;
    
    for (int ed = hd[v]; ed != -1; ed = nx[ed]) {
        if (to[ed] == p)
            continue;
        sum += pd(to[ed], 0, v);
    }

    me = sum;
    res[v][u] = -1;
    if (!u) {
        for (int ed = hd[v]; ed != -1; ed = nx[ed]) {
            if (to[ed] == p)
                continue;
            int loc = sum - pd(to[ed], 0, v) + pd(to[ed], 1, v) + 1;
            if (loc > me) {
                res[v][u] = ed;
                me = loc;
            }
        }
    }

    return me;
}

void build (int v, bool u, int p) {
    if (res[v][u] == -1) {
        for (int ed = hd[v]; ed != -1; ed = nx[ed])
            if (to[ed] != p)
                build(to[ed], 0, v);
    } else {
        for (int ed = hd[v]; ed != -1; ed = nx[ed]) {
            if (to[ed] == p)
                continue;
            if (res[v][u] == ed) {
                toout[os++] = ed;
                build(to[ed], 1, v);
            } else {
                build(to[ed], 0, v);
            }
        }
    }
}

int main () {
    memset(memo, -1, sizeof memo);
    memset(hd, -1, sizeof hd);
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        nx[es] = hd[a]; hd[a] = es; to[es] = b; es++;
        nx[es] = hd[b]; hd[b] = es; to[es] = a; es++;
    }

    printf("%d\n", pd(0, 0, -1));
    build(0, 0, -1);
    for (int i = 0; i < os; i++)
        printf("%d %d\n", to[toout[i]]+1, to[toout[i]^1]+1);
}
