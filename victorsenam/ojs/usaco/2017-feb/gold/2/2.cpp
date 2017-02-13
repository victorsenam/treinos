#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e3+7;

int memo[N][10];
int visi[N][10];
vector<int> adj[N];
int v[2][N];

int n;

int pd (int i, int k) {
    int & me = memo[i][k];

    if (visi[i][k]) return me;
    visi[i][k] = 1;

    me = 0;
    for (int j = i+1; j < n; j++)
        for (int x = 0; x < adj[j].size(); x++)
            if (adj[j][x] > adj[i][k])
                me = max(me, pd(j,x) + 1);

    return me;
}

int main () {
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);
    scanf("%d", &n);

    for (int k = 0; k < 2; k++)
        for (int i = 0; i < n; i++)
            scanf("%d", &v[k][i]);
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (abs(v[0][i] - v[1][j]) <= 4)
                adj[i].push_back(j);

    int res = 0;
    for (int i = 0; i < n; i++)
        res = max(res, pd(i,0)+1);

    printf("%d\n", res);
}
