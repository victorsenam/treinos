#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<int, int> pii;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 2e5+7;
const int M = 1e3+7;

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
