#include <bits/stdc++.h>

using namespace std;

const int N = 300;
const int M = 5000;
const int D = 10007;

int na, nb, m, d;
int qa[N], qb[N], cost[N], cor[N];
int hd[N], nx[M], to[M], es;
int s[N];
int visi[N];
int seen[N][D][2], memo[N][D][2];
int turn;
int qtd;

inline void connect (int a, int b) 
{ nx[es] = hd[a]; hd[a] = es; to[es] = b; es++; }

void dfs (int u, int c) {
    if (visi[u] == turn)
        return;
    visi[u] = turn;
    cor[u] = c;
    for (int ed = hd[u]; ed != -1; ed = nx[ed])
        dfs(to[ed], c);
}

int dp (int i, int d, bool ty) {
    if (i == qtd)
        return 0;

    if (seen[i][d][ty] == turn)
        return memo[i][d][ty];
    seen[i][d][ty] = turn;
    
    int & me = memo[i][d][ty];
    
    me = 0;
    if (ty) {
        me = dp(i+1, d, ty) + qa[i];
        if (qb[i] > qa[i] && d >= cost[i])
            me = max(me, dp(i+1, d-cost[i], ty) + qb[i]);
    } else {
        me = dp(i+1, d, ty) + qb[i];
        if (qa[i] > qb[i] && d >= cost[i])
            me = max(me, dp(i+1, d-cost[i], ty) + qa[i]);
    }

    return me;
}

int main () {
    while (scanf("%d %d %d %d", &na, &nb, &m, &d) != EOF) {
        memset(hd, -1, sizeof hd);
        for (int i = 0; i < na+nb; i++)
            scanf("%d", s+i);
        
        es = 0;
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            a--; b--;
            connect(a, na+b);
            connect(na+b, a);
        }
        
        qtd = 0;
        turn++;
        for (int i = 0; i < na+nb; i++) {
            if (visi[i] == turn)
                continue;
            dfs(i, qtd++);
        }

        for (int i = 0; i < qtd; i++)
            cost[i] = qa[i] = qb[i] = 0;

        for (int i = 0; i < na+nb; i++) {
            cost[cor[i]] += s[i];
            if (i >= na)
                qb[cor[i]]++;
            else
                qa[cor[i]]++;
        }

        printf("%d %d\n", dp(0, d, 1), dp(0, d, 0));
    }
}
