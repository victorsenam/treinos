#include <bits/stdc++.h>
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

ll n, d[2];

ll b[N], c[N];
char t[N];

int s[2][N], q[2];

multiset<int> ms;

int main () {
    scanf("%lld %lld %lld", &n, &d[0], &d[1]);

    ll r[2] = {0,0};

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %c", &b[i], &c[i], &t[i]);
        t[i] -= 'C';
        if (c[i] <= d[t[i]]) {
            r[t[i]] = max(r[t[i]], b[i]);
            s[t[i]][q[t[i]]++] = i;
        }
    }

    ll rs = 0;
    if (r[0] && r[1])
        rs = r[0] + r[1];

    for (int t = 0; t < 2; t++) {
        ms.clear();
        sort(s[t], s[t]+q[t], [] (int i, int j) { return c[i] < c[j]; });

        for (int _i = 0; _i < q[t]; _i++) {
            int i = s[t][_i];
            ms.insert(b[i]);
        }

        int _j = q[t] - 1;
        for (int _i = 0; _i < q[t]; _i++) {
            int i = s[t][_i];
            while (_j >= 0 && c[s[t][_j]] + c[i] > d[t]) {
                ms.erase(ms.find(b[s[t][_j]]));
                _j--;
            }

            if (c[i] + c[i] <= d[t])
                ms.erase(ms.find(b[i]));

            if (ms.size())
                rs = max(rs, b[i] + *(ms.rbegin()));

            if (c[i] + c[i] <= d[t])
                ms.insert(b[i]);
        }
    }

    printf("%lld\n", rs);
}
