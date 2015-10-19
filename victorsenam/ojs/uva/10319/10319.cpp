#include <bits/stdc++.h>

using namespace std;

const int N = 200;
const int M = N*N;

int s, a, m, t, x, y;
int s1, a1, s2, a2;
int hd[N], to[M], nx[M], es;
int comp[N], cs;
int open[N], close[N], turn;
int pre[N], ret[N], os;
int st[N], ss;

void connect(int a, int b) {
    nx[es] = hd[a]; hd[a] = es; to[es] = b; es++;
    nx[es] = hd[b]; hd[b] = es; to[es] = a; es++;
}

int dfs (int u) {
    if (close[u] == turn)
        return INT_MAX;
    if (open[u] == turn)
        return pre[u];

    open[u] = turn;
    pre[u] = ret[u] = os++;
    
    for (int ed = hd[u]; ed != -1; ed = nx[ed]) {
        ret[u] = min(ret[u], dfs(to[ed]));
    }

    close[u] = turn;
    st[ss++] = u;

    if (ret[u] == pre[u]) {
        while (ss)
            comp[st[--ss]] = cs;
        cs++;
    }

    return ret[u];
}

int main () {
    scanf("%d", &t);

    while (t--) {
        memset(hd, -1, sizeof hd);
        
        scanf("%d %d %d", &s, &a, &m);

        for (int i = 0; i < m; i++) {
            scanf("%d %d %d %d", &s1, &a1, &s2, &a2);
            s1--; a1--; s2--; a2--;
            
            if (s1 > s2) {
                swap(s1, s2);
                swap(a1, a2);
            }

            if (a1 < a2) {
                connect((((s1<<1))|1), (((s<<1)+(a1<<1))));
                connect((((s1<<1))|1), ((s2<<1)));
                connect((s<<1)+(((a2<<1))|1), (((s<<1)+(a1<<1))));
                connect((s<<1)+(((a2<<1))|1), ((s2<<1)));
                
                connect((((s2<<1))|1), (((s<<1)+(a2<<1))));
                connect((((s2<<1))|1), ((s1<<1)));
                connect((s<<1)+(((a1<<1))|1), (((s<<1)+(a2<<1))));
                connect((s<<1)+(((a1<<1))|1), ((s1<<1)));
            } else {
                connect((((s1<<1))|1), (((s<<1)+(a1<<1))|1));
                connect((((s1<<1))|1), ((s2<<1)|1));
                connect(((s<<1)+((a2<<1)|1)), (((s<<1)+(a1<<1))|1));
                connect((s<<1)+(((a2<<1))|1), ((s2<<1)|1));
                
                connect((((s2<<1))), (((s<<1)+(a2<<1))));
                connect((((s2<<1))), ((s1<<1)));
                connect((s<<1)+(((a1<<1))), (((s<<1)+(a2<<1))));
                connect((s<<1)+(((a1<<1))), ((s1<<1)));
            }
        }

        turn++;
        for (int i = 0; i < ((s+a)<<1); i++)
            dfs(i);

        bool ok = 1;
        for (int i = 0; ok && i < (s+a); i++)
            ok = (comp[i<<1] != comp[(i<<1)|1]);

        if (ok)
            printf("Yes\n");
        else
            printf("No\n");
    }
}
