#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+2;

int n, k;
int v[N][2];
vector<int> qt[N];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> k >> n;

    for (int i = 0; i < k; i++) {
        cin >> v[i][0];
        if (v[i][0] == -1)
            v[i][0] = 1;
        qt[v[i][0]].pb(i);
    }

    queue<int> sm, lr;
    for (int i = 1; i <= n; i++) {
        if (qt[i].size() == k/n) {
            for (int j : qt[i])
                v[j][1] = v[j][0];
        } else if (qt[i].size() < k/n) {
            sm.push(i);
        } else {
            lr.push(i);
        }
    }

    while (!sm.empty()) {
        int a = sm.front(), b = lr.front();
        sm.pop(); lr.pop();

        for (int j : qt[a])
            v[j][1] = b;

        int ll = k/n - qt[a].size();
        while (ll--) {
            int z = qt[b].back();
            v[z][1] = a;
            qt[b].pop_back();
        }
        
        if (qt[b].size() == k/n) {
            for (int j : qt[b])
                v[j][1] = v[j][0];
        } else if (qt[b].size() < k/n) {
            sm.push(b);
        } else {
            lr.push(b);
        }

    }

    for (int i = 0; i < k; i++)
        cout << v[i][0] << " " << v[i][1] << endl;
}
