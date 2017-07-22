#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 212345;

ll a[N]; int l[N];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int i, n, j; ll m;
    cin >> n >> m;
    ll sum = 0;
    vector<int> v0, v1;
    for(i = 0; i < n; i++) {
        cin >> a[i] >> l[i];
        if(l[i] == 0) v0.pb(i);
        else v1.pb(i), sum += a[i];
    }
    sort(v0.begin(), v0.end(), [](int i, int j) { return a[i] > a[j]; });
    sort(v1.begin(), v1.end(), [](int i, int j) { return a[i] > a[j]; });
    pii best(INT_MAX, INT_MAX);
    j = v1.size();
    while(j && sum - a[v1[j - 1]] >= m)
        sum -= a[v1[--j]];
    if(sum >= m) best = pii(j, 0);
    for(i = 0; i < v0.size(); i++) {
        sum += a[v0[i]];
        while(j && sum - a[v1[j - 1]] >= m)
            sum -= a[v1[--j]];
        if(sum >= m)
            best = min(best, pii(i + j + 1, i + 1));
    }
    int l0 = best.second;
    int l1 = best.first - best.second;
    cout << best.first << ' ' << l1 << '\n';
    for(i = 0; i < l0; i++) cout << v0[i] + 1 << ' ';
    for(i = 0; i < l1; i++) cout << v1[i] + 1 << ' ';
    cout << '\n';
}
