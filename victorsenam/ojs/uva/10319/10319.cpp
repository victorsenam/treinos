// INCOMPLETO
#include <bits/stdc++.h>

using namespace std;

const int N = 100000;
const int M = 100000;

int hd[N], to[M], nx[M], es;
int na, nb, m;
int a[2], b[2];
int open[N], clse[N], turn;
int pre[N], low[N], cnt;
int cmp[N], cs;
int st[N], ss;

inline void connect (int a, int b)
{ nx[es] = hd[a]; hd[a] = es; to[es] = b; es++; }

void conds (int a1, int a2, int b1, int b2) {
    connect(a1^1, a2);
    connect(a1^1, b1);
}

int dfs (int u) {
    if (clse[u] == turn)
        return INT_MAX;
    if (open[u] == turn)
        return pre[u];

    open[u] = turn;
    pre[u] = low[u] = cnt++;
    st[ss++] = u;
    
    for (int ed = hd[u]; ed != -1; ed = nx[ed])
        low[u] = min(low[u], dfs(to[ed]));

    clse[u] = turn;

    if (pre[u] == low[u]) {
        while (st[ss] != u) {
            cmp[st[--ss]] = cs;
        }
        cs++;
    }

    return low[u];
}

int main () {
    int t;
    scanf("%d", &t);
    while (t--) {
        memset(hd, -1, sizeof hd);

        scanf("%d %d %d", &na, &nb, &m);
        
        for (int i = 0; i < m; i++) {
            for (int k = 0; k < 2; k++) {
                scanf("%d %d", a+k, b+k);
                a[k]--; b[k] += na - 1;
                a[k] <<= 1; b[k] <<= 1;
            }
            
            if (a[0] < a[1])
            { b[0] ^= 1; b[1] ^= 1; }

            if (b[0] < b[1])
            { a[0] ^= 1; a[1] ^= 1; }


            if (a[0] == a[1]) {
                connect(a[0]^1, a[0]);
            } else if (b[0] == b[1]) {
                connect(b[0]^1, b[0]);
            } else {
                conds(a[0], a[1], b[0], b[1]);
                conds(a[1], a[0], b[1], b[0]);
                conds(b[0], b[1], a[0], a[1]);
                conds(b[1], b[0], a[1], a[0]);
            }
        }

/*
        for (int i = 0; i < (na+nb)<<1; i++) {
            printf("%d:", i);
            for (int ed = hd[i]; ed != -1; ed = nx[ed])
                printf(" %d", to[ed]);
            printf("\n");
        }
*/

        cnt = cs = ss = 0;
        cs++;
        turn++;
        for (int i = 0; i < (na+nb)<<1; i++)
            dfs(i);
        
        bool ok = 1;
        for (int i = 0; (ok|1) && i < (na+nb)<<1; i += 2) {
            if (cmp[i] == cmp[i+1])
                ok = 0;
        }

        if (ok)
            printf("Yes\n");
        else
            printf("No\n");
    }
}
