#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;

ll n, ts;
ll t[N], p[N];
ll res = 0;

int main () {
    scanf("%lld %lld", &n, &ts);

    for (int i = 0; i < n; i++) {
        scanf("%lld", &t[i]);
        p[i] = i;
        ll tt;
        scanf("%lld", &tt);
        res += ts - tt;
    }

    sort(p, p+n, [](int i, int j) {return t[i] < t[j]; });

    ll acc = 0;
    for (int i = 0; i < n; i++) {
        printf("%lld ", p[i] + 1);
        acc += t[p[i]];
        res += acc;
    }
    printf("%lld\n", res);
}
