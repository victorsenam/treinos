#include <bits/stdc++.h>


using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

const int N = 100007;

int n, d[2];
int adj[N][2];
bool visi[N];
bool cor[N];
int v[N];
int pre[N];
int pos[N];

void dfs(int v, int c) {
    if (v >= n) 
        return;
    if (visi[v]) {
        if (cor[v] == c)
            return;
        printf("NO\n");
        exit(0);
    }

    visi[v] = 1;
    cor[v] = c;

    for (int j = 0; j < 2; j++)
        dfs(adj[v][j], c);
}

int main () {
    scanf("%d %d %d", &n, d, d+1);

    for (int i = 0; i < n; i++) {
        scanf("%d", v+i);
        pre[i] = v[i];
    }

    sort(v, v+n);

    for (int i = 0; i < n; i++)
        pos[i] = lower_bound(v, v+n, pre[i]) - v;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            adj[i][j] = lower_bound(v, v+n, d[j]-v[i]) - v;
            if (adj[i][j] >= n || v[adj[i][j]] != d[j]-v[i]) 
                adj[i][j] = n;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            if (adj[i][j] >= n && adj[i][j^1] < n) dfs(i, j^1);
            else if (adj[i][j] >= n && adj[i][j^1] >= n) {
                dfs(i, j);
                dfs(i, j^1);
            }
        }
    }

    for (int i = 0; i < n; i++)
        if (!visi[i]) dfs(i, 1);

    printf("YES\n");
    for (int i = 0; i < n; i++)
        printf("%d ", cor[pos[i]]);
    printf("\n");
}
