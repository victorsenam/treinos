#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6;

int visi[N];
int val[N];

int n;

void dfs (int u) {
    if (visi[u] == 1) {
        cout << "IMPOSSIBLE" << endl;
        exit(0);
    } else if (visi[u] == 2) {
        return;
    }

    visi[u] = 1;
    for (int v : adj[u])
        dfs(v);
    visi[u] = 2;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cout << "POSSIBLE" << endl;

    for (int i = 0; i < n; i++)

}
