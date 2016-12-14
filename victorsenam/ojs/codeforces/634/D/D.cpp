#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 2e6+7;

ll x[N], p[N];
int pr[N];
ll bs;
ll res;
ll d, n, m;
ll tot;
map<ll, ll> mp;

void fail () {
    printf("-1\n");
    exit(0);
}

bool cmp_t (int i, int j) {
    if (x[i] != x[j]) return x[i] < x[j];
    return i < j;
}

int main () {
    scanf("%lld %lld %lld", &d, &n, &m);
    tot = n;
    mp[0] = n;

    for (int i = 0; i < m; i++) {
        scanf("%lld %lld", &x[i], &p[i]);
        pr[i] = i;
    }
    x[m] = d;
    p[m] = 0;
    pr[m] = m;
    m++;
    sort(pr, pr+m, cmp_t);

    bs = INT_MAX;
    res = 0;

    int _c = 0;
    ll ps = 0;
    for (int _c = 0; _c < m; _c++) {
        int c = pr[_c];
        
        while (ps < x[c]) {
            if (mp.empty()) 
                fail();

            ll var = min(x[c] - ps, mp.begin()->second);
            ps += var;
            n -= var;
            res += var*mp.begin()->first;
            mp.begin()->second -= var;
            if (mp.begin()->second == 0)
                mp.erase(mp.begin());
        }

        mp[p[c]] += tot-n;
        n = tot;
        while (!mp.empty() && mp.rbegin()->first > p[c]) {
            ll var = mp.rbegin()->second;
            mp.erase(mp.find(mp.rbegin()->first));
            mp[p[c]] += var;
        }
    }

    printf("%lld\n", res);
}
