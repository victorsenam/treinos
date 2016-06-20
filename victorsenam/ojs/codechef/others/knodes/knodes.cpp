#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

vector<int> adj[N];
int ant[N][18];
int hei[N];
int que[N];
int n, m, k, t, a, b, ss;
int max1, max2, lc, mini;

void dfs(int v, int p, int h) {
    hei[v] = h;

    ant[v][0] = p;
    for (int i = 1; i < 18; i++)
        ant[v][i] = ant[ant[v][i-1]][i-1];

    for (int i = 0; i < adj[v].size(); i++) {
        if (adj[v][i] == p)
            continue;
        dfs(adj[v][i], v, h+1);
    }
}

int getLca(int v, int u) {
    if (hei[v] > hei[u]) swap(u, v);

    if (hei[u] > hei[v]) {
        for (int i = 17; i >= 0; i--) {
            if (hei[ant[u][i]] >= hei[v])
                u = ant[u][i];
        }
    }

    if (v == u) return v;

    for (int i = 17; i >= 0; i--) {
        if (ant[v][i] != ant[u][i]) {
            v = ant[v][i];
            u = ant[u][i];
        }
    }
            
    return ant[v][0];
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            adj[i].clear();
            hei[i] = -1;
            for (int j = 0; j < 18; j++)
                ant[i][j] = 0;
        }

        for (int i = 0; i < n-1; i++) {
            scanf("%d %d", &a, &b);
            a--;
            b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        
        dfs(0, 0, 0);

        scanf("%d", &m);
        while (m--) {
            scanf("%d", &k);

            max1 = max2 = mini = -1;
            for (int i = 0; i < k; i++) {
                scanf("%d", que+i);
                que[i]--;
                if (max1 == -1 || hei[que[i]] > hei[max1])
                    max1 = que[i];
                if (mini == -1 || hei[que[i]] < hei[mini])
                    mini = que[i];
            }

            if (k < 3) {
                printf("Yes\n");
                continue;
            }

            for (int i = 0; i < k; i++) {
                if (que[i] == max1 || getLca(que[i], max1) == que[i])
                    continue;
                if (max2 == -1 || hei[que[i]] > hei[max2])
                    max2 = que[i];
            }

            if (max2 == -1) {
                printf("Yes\n");
                continue;
            }

            lc = getLca(max1, max2);

 //           printf("max1 %d max2 %d mini %d lc %d\n", max1, max2, mini, lc);

            if (hei[mini] < hei[lc]) {
                printf("No\n");
                continue;
            }
            
            int ss;
            for (ss = 0; ss < k; ss++)
                if (getLca(que[ss], max1) != que[ss] && getLca(que[ss], max2) != que[ss])
                    break;

            if (ss == k)
                printf("Yes\n");
            else
                printf("No\n");
        }
    }
}
