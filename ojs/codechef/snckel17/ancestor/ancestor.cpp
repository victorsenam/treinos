#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e6+7;

int ts, n;
vector<int> adj[2][N];
int vl[N][2], ord;
int bit[N];
int rs[N];

void add (int p, int x) {
    for (int i = p+2; i < N; i+=(i&-i))
        bit[i] += x;
}

int get (int p) {
    int x = 0;
    for (int i = p+2; i > 0; i-=(i&-i))
        x += bit[i];
    return x;
}

int dfs (int u, int p) {
    vl[u][0] = ord++;

    for (int v : adj[0][u]) {
        if (v == p) continue;
        dfs(v, u);
    }

    vl[u][1] = ord++;
}

int go (int u, int p) {
    rs[u] = get(vl[u][0]);

    add(vl[u][0], 1);
    add(vl[u][1], -1);

    for (int v : adj[1][u]) {
        if (v == p) continue;
        go(v, u);
    }

    add(vl[u][0], -1);
    add(vl[u][1], 1);
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> ts;

    while (ts--) {
        cin >> n;

        for (int k = 0; k < 2; k++)  {
            for (int i = 0; i < n; i++)
                adj[k][i].clear();

            for (int i = 0; i < n-1; i++) {
                int a, b;
                cin >> a >> b;
                a--; b--;
                
                adj[k][a].push_back(b);
                adj[k][b].push_back(a);
            }
        }

        ord = 0;
        dfs(0, 0);
        go(0, 0);

        for (int i = 0; i < n; i++)
            cout << rs[i] << " ";
        cout << endl;
    }
}
