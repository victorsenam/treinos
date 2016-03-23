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
    int id[M], p[M], c[M];
    int qu[M], qi, qf;
    int f[M], g[M];
    char aux[M];

    void init () {
        es = 2;
        memset(id, 0, sizeof id);
        memset(nx, 0, sizeof nx);
    }

    void insert (int r, char * s, int idx) {
        if (!s[0]) {
            id[r] = idx;
            return;
        }

        if (!nx[r][s[0]-'a']) {
            p[es] = r;
            c[es] = s[0];
            nx[r][s[0]-'a'] = es++;
        }
        insert(nx[r][s[0]-'a'], s+1, idx);            
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

                if (id[f[v]])
                    g[v] = f[v];
                else
                    g[v] = g[f[v]];

                qu[qf++] = v;
            }
        }
    }

    void print (int u, int i) {
        aux[i] = 0;
        printf("[%d:%d] %s -> [%d,%d]\n", u, id[u], aux, f[u], g[u]);
        for (int j = 0; j < A; j++) {
            if (!nx[u][j]) continue;
            aux[i] = j+'a';
            print(nx[u][j], i+1);
        }
    }

    void printstr (int u) {
        if (u == 1)
            return;
        printstr(p[u]);
        putchar(c[u]);
    }

    void get (char * s, int * st, int & sz) {
        int u = 1;
        for (int i = 0; s[i]; i++) {
            while (u > 1 && !nx[u][s[i]-'a'])
                u = f[u];
            if (nx[u][s[i]-'a'])
                u = nx[u][s[i]-'a'];
            int v = u;
            while (g[v]) {
                v = g[v];
                st[sz++] = v;
            }
            if (id[u])
                st[sz++] = u;
        }
    }
};

int n, ps;
int st[N], ss;
char str[M], tmp[N];
trie tree;
int hd[N], sz[N], visi[N], turn, es;
int nx[4000007], to[4000007];

int dfs (int u) {
    if (visi[u] == turn)
        return sz[u];
    visi[u] = turn;
    sz[u] = 1;
    for (int ed = hd[u]; ed; ed = nx[ed])
        sz[u] = max(sz[u], 1+dfs(to[ed]));
    return sz[u];
}

int main () {
    while (scanf("%d", &n) != EOF && n) {
        turn++;
        memset(hd, 0, sizeof hd);
        tree.init();
        ps = 0;
        for (int i = 0; i < n; i++) {
            scanf(" %s", str+ps);
            tree.insert(1,str+ps,i+1);
            ps += strlen(str+ps)+1;
        }
        tree.build();

        ps = 0;
        es = 2;
        for (int i = 0; i < n; i++) {
            ss = 0;
            tree.get(str+ps, st, ss);
            int u = tree.id[st[ss-1]]-1;
            for (int j = 0; j < ss-1; j++) {
                int v = tree.id[st[j]]-1;
                nx[es] = hd[u]; to[es] = v; hd[u] = es++;
            }

            ps += strlen(str+ps)+1;
        }
        
        int maxi = 0;
        for (int i = 0; i < n; i++)
            maxi = max(maxi, dfs(i));
        printf("%d\n", maxi);
    }
}
