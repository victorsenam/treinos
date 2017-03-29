#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 7e3+7;

vector<int> adj[N];
int n;
int memo[2][N];
int visi[2][N];

int dfs (int b, int u) {
    if (u == 0) return 0;
    if (visi[b][u] == 1)
        return 2;
    if (visi[b][u] == 2)
        return memo[b][u];

    visi[b][u] = 1;

    memo[b][u] = 0;
    for (int v : adj[b]) {
        int rt = dfs(!b, (u+v)%n);
        if (!rt) {
            memo[b][u] = 1;
            break;
        } else if (rt == 1) {
            memo[b][u] = 2;
        }
    }

    visi[b][u] = 2;
    return memo[b][u];
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < 2; i++) {
        int k;
        scanf("%d", &k);

        for (int j = 0; j < k; j++) {
            int a;
            scanf("%d",&a);
            adj[i].push_back(a);

        }

        for (int j = 0; j < n; j++)
            memo[i][j] = -1;
    }
    
    for (int j = 0; j < 2; j++) {
        for (int i = 1; i < n; i++) {
            int rt = dfs(j,i);
            if (rt == 1) {
                printf("Win ");
            } else if (rt == 2) {
                printf("Loop ");
            } else {
                printf("Lose ");
            }
        }
        printf("\n");
    }
}
