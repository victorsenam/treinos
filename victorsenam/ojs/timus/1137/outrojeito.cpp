// WA - Discordo :(
#include <bits/stdc++.h>

using namespace std;

const int N = 103;
const int M = 1007;
const int MAX = 1000007;

int n;
int rts[N][M];
int len[N];
int res[MAX];
int ss;
vector<int> adj[N];
int turn;
int vis[MAX];

int dfs (int u, int t, int ps) { 
    if (vis[u] == turn)
        return 0;
    vis[u] = turn;
    
    if (u == t) {
        ss = ps;
        return 1;
    }

    for (int i = 0; i < adj[u].size(); i++) {
        if (dfs(adj[u][i], t, ps+1)) {
            res[ps] = u;
            return 1;
        }
    }
    return 0;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", len+i);
        scanf("%d", rts[i]);
        for (int j = 1; j <= len[i]; j++) {
            scanf("%d", rts[i]+j);
            adj[rts[i][j-1]].push_back(rts[i][j]);
        }
    }

    ss = 0;
    for (int i = 0; i < len[0]; i++)
        res[ss++] = rts[0][i];

    int att = rts[0][0];   
    for (int i = 1; i < n; i++) {
        turn++;
        dfs(att, rts[i][0], ss);       
        att = rts[i][0];
        for (int j = 0; j < len[i]; j++)
            res[ss++] = rts[i][j];
    }
    turn++;
    dfs(att, rts[0][0], ss);
    
    printf("%d ", ss);
    for (int i = 0; i < ss; i++)
        printf("%d ", res[i]);
    printf("%d\n", rts[0][0]);
}
