#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define lld I64d
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 500007;

int n;
ll k;
map<ll, int> mp;
map<ll, int>::iterator it;
ll c[N];

ll getless () {
    ll d = 0;

    ll pval = mp.begin()->first;
    while (d < k) {
        it = mp.begin();

        ll mini = it->first;
        ll qt = it->second;
        mp.erase(mp.begin());

        if (mp.size() == 0) {
            return mini + (k-d)/qt;
        }

        it = mp.begin();

        ll tim = (it->first-mini)*qt;
        if (d + tim > k) {
            return mini + (k-d)/qt;
        } else {
            it->second += qt;
            d += tim;
            pval = it->first;
        }
    }

    return pval;
}

int main () {
    scanf("%d %lld", &n, &k);
    ll sum = 0;

    for (int i = 0; i < n; i++) {
        scanf("%lld", c+i);

        mp[c[i]]++;
        sum += c[i];
    }

    ll pval = getless();

    mp.clear();
    for (int i = 0; i < n; i++) {
        mp[-c[i]]++;
    }
    ll rval = -getless();
    DEBUG("%lld %lld\n", pval, rval);

    ll res;
    if (pval >= rval)
        res = (sum%n != 0);
    else
        res = rval-pval;
    printf("%lld\n", res);
}
