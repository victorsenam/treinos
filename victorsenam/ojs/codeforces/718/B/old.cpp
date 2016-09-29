#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define GNU __gnu_pbds

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<int, int> pii;
namespace GNU { typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; } 
using GNU::ordered_set;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 2e5+7;
const int M = 1e3+7;

ll t[N];
ll st[N];
ll qr[N];
ll res[N];
int p_qr[N];
int p[N];
int nx;
int n, m;
int curr;
ordered_set s[M];
priority_queue<pair<int, int> > pq;
ll tim;

ll get (ll tt) {
    ll rs = 0;
    for (ll i = 1; i < M; i++) {
        rs += s[i].order_of_key(tt%i);
        rs += (tt/i + 0)*s[i].size();
    }
    return rs;
}

ll query (ll tt) {
    return get(tt) - get(tim);
}

void insert () {
    s[t[p[curr]]].insert(st[p[curr]]%t[p[curr]]);
}

bool cmp_qr (ll i, ll j) {
    return qr[i] < qr[j];
}

bool cmp_t (int i, int j) {
    return st[i] < st[j];
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%lld", &t[i]);
        p[i] = i;
    }
    p[n] = n;

    sort(t, t+n);

    for (int i = 0; i < m; i++) {
        scanf("%lld", &qr[i]);
        p_qr[i] = i;
    }

    sort(p_qr, p_qr+m, cmp_qr);

    int cr = 1;
    st[0] = 0;
    pq.push(pii(-t[0], 0));

    while (!pq.empty()) {
        pii att = pq.top();
        pq.pop();

        st[cr] = -att.first;
        att.first -= t[cr];
        att.second = cr++;
    }

    st[n] = 1e18;
    sort(p, p+n+1, cmp_t);

    curr = 0;
    ll sum = 0;
    for (int _i = 0; _i < m; _i++) {
        int i = p_qr[_i];

        while (curr < n && sum + query(st[p[curr]]) <= qr[i]) {
            sum += query(st[p[curr]]);
            insert();
            tim = st[p[curr]];
            curr++;
        }
        
        ll lo = tim;
        ll hi = st[p[curr]];

        while (lo < hi) {
            ll mid = (lo+hi)/2;
            if (sum + query(mid) >= qr[i])
                hi = mid;
            else
                lo = mid+1;
        }

        res[i] = lo;
    }

    for (int i = 0; i < m; i++) {
        printf("%lld\n", res[i]);
    }
}
