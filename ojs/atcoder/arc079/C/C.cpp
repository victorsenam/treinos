#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e5+7;

int adj[N][2];
int n, m;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if (a > b) swap(a,b);

        if (a == 1)
            adj[b][0] = 1;
        if (b == n)
            adj[a][1] = 1;
    }

    for (int i = 2; i < n; i++) {
        if (adj[i][0] && adj[i][1]) {
            cout << "POSSIBLE" << endl;
            return 0;
        }
    }
    cout << "IMPOSSIBLE" << endl;
}
