#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pii;
#define pb push_back

const int N = 2e6+7;

int n, m;
ll v[N], p[N], q[N];
ll c[N][2];

ll bit[N];
multiset<pii> s;

ll get (int i) {
    ll x = 0;
    for (i += 2; i > 0; i -= (i&-i))
        x += bit[i];
    return x;
}

void add (int i, ll x) {
    for (i += 2; i < N; i += (i&-i))
        bit[i] += x;
}

ll solve () {
    ll res = 0;

    for (auto it = s.begin(); it != s.end(); it = s.lower_bound(pii(get(it->second), it->second+1)) ) {
        //printf("try %lld-th element (valued %lld)\n", it->second, it->first);
        if (it->first >= get(it->second-1)) {
            res++;
        }
    }
    
    return res;
}

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &v[i]);
        p[i] = i;
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%lld %lld", &c[i][0], &c[i][1]);

        p[i+n] = i+n;
        v[i+n] = c[i][1];
    }

    sort(p, p+n+m, [] (ll i, ll j) {
        return v[i] < v[j];
    });

    for (int i = 0; i < n+m; i++) {
        q[p[i]] = i;
    }

    for (int i = 0; i < n; i++) {
        s.insert(pii(v[i],q[i]));
        //printf(" + %lld %lld\n", v[i], q[i]);
        add(q[i], v[i]);
    }
    
    printf("%lld\n", solve());
    for (int j = 0; j < m; j++) {
        int i = c[j][0]-1;
        s.erase(s.find(pii(v[i],q[i])));
        add(q[i], -v[i]);
        //printf(" - %lld %lld\n", v[i], q[i]);
        q[i] = q[j+n];
        v[i] = v[j+n];
        //printf(" + %lld %lld\n", v[i], q[i]);
        s.insert(pii(v[i],q[i]));
        add(q[i], v[i]);

        printf("%lld\n", solve());
    }
}
