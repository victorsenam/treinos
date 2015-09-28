// REALLY CLOSE

#include <bits/stdc++.h>

using namespace std;

const int N = 103;

vector<pair<int, int> > adj[N];
int n, m, a, b, l;
int memo[N][N][2];
int res[N][N][2];
int visi[N][N][2];
int turn;
int obj;
int sol[N];
int ss;

int pd (int u, int p, bool f) {
    if (!f && u == obj) {
        return 0;
    }

    int & me = memo[u][p][f];
    if (visi[u][p][f] == turn)
        return me;
    visi[u][p][f] = turn;

    me = INT_MAX;
    int mini = INT_MAX;
    int scm = INT_MAX;
    for (int i = 0; i < adj[u].size(); i++) {
        if (adj[u][i].first == p) {
            scm = min(scm, adj[u][i].second);
            if (mini > scm)
                swap(mini, scm);
            continue;
        }

        int aux = pd(adj[u][i].first, u, 0);
        aux = max(aux, aux + adj[u][i].second);
        me = min(me, aux);
        if (me == aux)
            res[u][p][f] = adj[u][i].first;
    }

    if (scm != INT_MAX) {
        int aux = pd(p, u, 0);
        aux = max(aux, aux + scm);
        me = min(me, aux);
        if (me == aux)
            res[u][p][f] = p;
    }

    return me;
}

int main () {
    while (scanf("%d %d", &n, &m) != EOF && n != -1) {
        for (int i = 0; i < N; i++)
            adj[i].clear();
        
        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &a, &b, &l);
            a--; b--;
            adj[a].push_back(make_pair(b,l));
            adj[b].push_back(make_pair(a,l));
        }

        int bes = INT_MAX;
        ss = 0;
        for (int i = 0; i < n; i++) {
            turn++;
            obj = i;
            if (pd(i,i,1) < bes) {
                bes = pd(i,i,1);
                ss = 0;
                sol[ss++] = i;
                b = i;
                a = res[i][i][1];
                while (a != i) {
                    sol[ss++] = a;
                    a = res[a][b][0];
                    swap(a,b);
                }
            }
        }

        if (bes == INT_MAX)
            printf("No solution.\n");
        else {
            for (int i = ss; i > 0; i--) {
                printf("%d", sol[i]+1);
                if (i > 1)
                    printf(" ");
            }
            printf("\n");
        }
    }
}
