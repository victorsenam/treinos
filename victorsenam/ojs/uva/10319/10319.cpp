// WA
#include <bits/stdc++.h>

using namespace std;

const int N = 1000;
const int M = N*N;

int s, a, m, t, x, y;
int sp[2], ap[2];
int hd[N], to[M], nx[M], es;
int comp[N], cs;
int open[N], setup[N], turn;
int pre[N], ret[N], os;
int st[N], ss;

inline void connect(int a, int b) {
    nx[es] = hd[a]; hd[a] = es; to[es] = b; es++;
}

inline int node (int ind, bool type, bool val) {
    return (type?(s<<1):0) + ((ind<<1)|(val));
}

int dfs (int u) {
    if (open[u] == turn)
        return ret[u];

    open[u] = turn;
    pre[u] = ret[u] = os++;
    st[ss++] = u;
    
    for (int ed = hd[u]; ed != -1; ed = nx[ed]) {
        int aux = dfs(to[ed]);
        ret[u] = min(ret[u], aux);
    }


    if (ret[u] == pre[u]) {
        comp[u] = -1;
        while (comp[u] == -1) {
            ret[st[ss-1]] = INT_MAX;
            comp[st[--ss]] = cs;
        }
        cs++;
    }

    return ret[u];
}

int main () {
    scanf("%d", &t);

    while (t--) {
        memset(hd, -1, sizeof hd);
        
        scanf("%d %d %d", &s, &a, &m);
        es = 0;

        for (int i = 0; i < m; i++) {
            scanf("%d %d %d %d", sp, ap, sp+1, ap+1);
            for (int k = 0; k < 2; k++) {
                sp[k]--;
                ap[k]--;
            }

            if (ap[0] == ap[1] && sp[0] == sp[1])
                continue;
            
            int a1 = node(ap[0], 0, (sp[0]<sp[1]));
            int a2 = node(ap[1], 0, (sp[0]<sp[1]));
            int s1 = node(sp[0], 1, (ap[0]<ap[1]));
            int s2 = node(sp[1], 1, (ap[0]<ap[1]));
            
            if (a1 == a2)
                connect(a1^1, a1);
            else if (s1 == s2)
                connect(s1^1, s1);
            else {
                connect(a1^1, s1);
                connect(a1^1, a2);
                connect(s2^1, s1);
                connect(s2^1, a2);

                connect(s1^1, s2);
                connect(s1^1, a1);
                connect(a2^1, s2);
                connect(a2^1, a1);
            }
        }

        turn++;
        cs = 0;
        ss = 0;
        os = 0;
        for (int i = 0; i < ((s+a)<<1); i++)
            dfs(i);

        bool ok = 1;
        for (int i = 0; ok && i < (s+a); i++) {
 //           printf("%d: %d[%d] %d[%d]\n", i, comp[i<<1], (i<<1), comp[((i<<1)|1)], ((i<<1)|1));
            ok = (comp[i<<1] != comp[((i<<1)|1)]);
        }

        if (ok)
            printf("Yes\n");
        else
            printf("No\n");
    }
}
