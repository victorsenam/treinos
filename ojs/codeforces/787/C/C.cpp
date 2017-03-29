#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 7e3+7;

vector<int> adj[2];
int n;
int res[2][N];
int cn[2][N];

void dfs (int k, int u, int t) {
    if (res[k][u] != -1) return;
    if (!t && u) {
        cn[k][u]--;
        if (cn[k][u])
            return;
    }
    res[k][u] = t;
    for (int j = 0; j < adj[!k].size(); j++)
        dfs(!k, (u-adj[!k][j]+n)%n, !t);
}

int main () {
    scanf("%d", &n);

    for (int j = 0; j < 2; j++) {
        int k;
        scanf("%d", &k);
        for (int i = 0; i < k; i++) {
            int x;
            scanf("%d", &x);
            adj[j].push_back(x);
        }

        for (int i = 0; i < n; i++) {
            cn[j][i] = k;
            res[j][i] = -1;
        }
    }

    res[0][0] = res[1][0] = 0;
    for (int j = 0; j < 2; j++)
        for (int i = 0; i < adj[j].size(); i++)
            dfs(j, n-adj[j][i], 1);

    for (int j = 0; j < 2; j++) {
        for (int i = 1; i < n; i++) {
            int rt = res[j][i];
            if (rt == -1)
                printf("Loop ");
            else if (rt == 1)
                printf("Win ");
            else
                printf("Lose ");
        }
        printf("\n");
    }
}
