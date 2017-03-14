#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e6+7;
map<ll, ll> mp[N];
ll diff[N][2];
ll deg[N], pr[N];
ll wg[N];
ll n, k;
ll re[N];
ll qu[N], qi, qf;
ll ans;

int find (int i) {
    if (i == re[i]) return i;
    return re[i] = find(re[i]);
}

void join (int i, int j) {
    ll a, b;
    i = find(i);
    j = find(j);
    if (mp[i].size() > mp[j].size())
        swap(i, j);

    for (pair<ll,ll> it : mp[i]) {
        a = k - diff[j][0] - diff[i][0] - it.first;
        b = it.second + diff[i][1] + diff[j][1];
        if (mp[j].count(a)) {
            b += mp[j][a];
            ans = min(b, ans);
        }
    }

    for (pair<ll,ll> it : mp[i]) {
        a = it.first + diff[i][0] - diff[j][0];
        b = it.second + diff[i][1] - diff[j][1];

        if (mp[j].count(a) == 0) {
            mp[j][a] = b;
        } else {
            mp[j][a] = min(mp[j][a], b);
        }
    }

    re[i] = j;
}

int main() {
    scanf("%lld %lld", &n, &k);

    qi = qf = 0;

    for (int i = 0; i < n; i++) {
        re[i] = i;
        diff[i][0] = diff[i][1] = 0;
        deg[i] = 0;
        mp[i][0] = 0;
    }

    for (int i = 1; i < n; i++) {
        scanf("%lld %lld", pr+i, wg+i);
        pr[i]--;
        deg[pr[i]]++;
    }

    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            qu[qf++] = i;
        }
    }

    ans = LLONG_MAX;

    while (qi < qf) {
        int u = qu[qi++];
        int t = find(u);

        if (mp[t].count(k - diff[t][0])) {
            ans = min(mp[t][k-diff[t][0]] + diff[t][1], ans);
        }

        if (!u) continue;

        diff[t][0]++;
        diff[t][1] += wg[u];

        join(u, pr[u]);
        deg[pr[u]]--;
        if (deg[pr[u]] == 0) {
            qu[qf++] = pr[u];
        }
    }

    if (ans == LLONG_MAX) ans = -1;
    printf("%lld\n", ans);

}
