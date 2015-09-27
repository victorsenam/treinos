// WA

#include <bits/stdc++.h>

using namespace std;

const int N = 103;
const int M = 10007;
const int MAX = 1000007;

int n;
int k;
int turn;
vector<int> adj[M];
int a, b;
int visi[M];
int used[M];
int sol[MAX];
int ss;
int att;
bool needs[M];
int togo[M];
int tt;


bool dfs(int u, int d) {
    if (u == d)
        return 1;
    if (visi[u] == turn)
        return 0;
    visi[u] = turn;

    sol[ss++] = u;
    used[u]++;
    for (int i = 0; i < adj[u].size(); i++) {
        if (dfs(adj[u][i], d))
            return 1;
    }
    ss--;
    used[u]--;
    return 0;
}

int main () {
    scanf("%d", &n);
    int maxl = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &k);
        scanf("%d", &a);
        a--;

        for (int j = 0; j < k; j++) {
            scanf("%d", &b);
            b--;
            if (!needs[b]) {
                needs[b] = 1;
                togo[tt++] = b;
            }
            adj[a].push_back(b);
            a = b;
        }
    }


    att = togo[0];
    for (int i = 0; i <= tt; i++) {
        if (i != tt && used[togo[i%tt]])
            continue;

        turn++;
        if (!dfs(att, togo[i%tt])) {
            printf("0\n");
            return 0;
        }

        att = togo[i%tt];
    }

    printf("%d", ss);
    for (int i = 0; i < ss; i++)
        printf(" %d", sol[i]+1);
    printf(" %d\n", togo[0]+1);
}
