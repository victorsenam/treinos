#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 40007;
const int M = 4000007;
const int A = 27;

struct trie {
    int n;
    int nx[M][A], es;
    int mark[M], p[M], c[M];
    int qu[M], qi, qf;
    int f[M], g[M];
    char aux[M];
    int visi[M], memo[M], turn;

    void init () {
        es = 2;
        memset(nx[1], 0, sizeof nx[1]);
        turn++;
    }

    void insert (int r, char * s) {
        if (!s[0]) {
            mark[r] = turn;
            return;
        }

        if (!nx[r][s[0]-'a']) {
            p[es] = r;
            c[es] = s[0];
            memset(nx[es], 0, sizeof nx[es]);
            nx[r][s[0]-'a'] = es++;
        }
        insert(nx[r][s[0]-'a'], s+1);
    }

    void build () {
        qi = qf = 0;

        for (int i = 0; i < A; i++) {
            if (!nx[1][i]) continue;
            qu[qf] = nx[1][i];
            f[qu[qf]] = 1;
            g[qu[qf]] = 0;
            qf++;
        }

        while (qi < qf) {
            int u = qu[qi++];
            for (int i = 0; i < A; i++) {
                if (!nx[u][i]) continue;
                int v = nx[u][i];

                f[v] = f[u];
                while (f[v] != 1 && !nx[f[v]][c[v]-'a'])
                    f[v] = f[f[v]];
                if (nx[f[v]][c[v]-'a'])
                    f[v] = nx[f[v]][c[v]-'a'];

                if (mark[f[v]] == turn)
                    g[v] = f[v];
                else
                    g[v] = g[f[v]];

                qu[qf++] = v;
            }
        }
    }

    int dp (int u) {
        if (u == 1)
            return 0;
        int & me = memo[u];
        if (visi[u] == turn)
            return me;
        visi[u] = turn;
        me = 0;
        me = max(dp(p[u]), dp(f[u]));
        me = max(me, dp(g[u]));
        me += (mark[u] == turn);
        return me;
    }
};

int n, ps;
int st[N], ss;
char str[M], tmp[N];
trie tree;

int main () {
    while (scanf("%d", &n) != EOF && n) {
        tree.init();
        ps = 0;
        for (int i = 0; i < n; i++) {
            scanf(" %s", str+ps);
            tree.insert(1,str+ps);
            ps += strlen(str+ps)+1;
        }
        tree.build();

        int maxi = 0;
        for (int i = 1; i < tree.es; i++)
            maxi = max(maxi, tree.dp(i));
        printf("%d\n", maxi);
    }
}
