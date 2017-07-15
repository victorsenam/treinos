#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define GNU __gnu_pbds

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

namespace GNU { typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; }
using GNU::ordered_set;

const int N = 1e6;

ordered_set s[N];
int n, m, k;
ll b[N];
ll v[N][3];
ll w[N][3];
int uf[N];
int p[N], q[N];
ll res[N];

int find (int i) {
    if (uf[i] == i) return i;
    return uf[i] = find(uf[i]);
}

void add (int i) {
    int a = find(v[i][0]), b = find(v[i][1]);
    if (a == b) return;
    if (s[a].size() < s[b].size())
        swap(a,b);

    while (!s[b].empty()) {
        s[a].insert(*(s[b].begin()));
        s[b].erase(s[b].begin());
    }

    uf[b] = a;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
        cin >> b[i];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 3; j++)
            cin >> v[i][j];
        v[i][0]--; v[i][1]--;
        p[i] = i;
    }

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < 3; j++)
            cin >> w[i][j];
        w[i][0]--;
        q[i] = i;
    }

    sort(p, p+m, [] (int i, int j) {
        return v[i][2] < v[j][2];
    });

    sort(q, q+k, [] (int i, int j) {
        return w[i][1] < w[j][1];
    });

    for (int i = 0; i < n; i++) {
        s[i].insert(pii(b[i],i));
        uf[i] = i;
    }

    int _j = 0;
    for (int _i = 0; _i < k; _i++) {
        int i = q[_i];

        while (_j < m && v[p[_j]][2] <= w[i][1])
            add(p[_j++]);

        int x = find(w[i][0]);

        if (s[x].size() < w[i][2])
            res[i] = -1;
        else
            res[i] = (s[x].find_by_order(s[x].size() - (w[i][2]))->first);
    }

    for (int i = 0; i < k; i++)
        cout << res[i] << endl;

}

