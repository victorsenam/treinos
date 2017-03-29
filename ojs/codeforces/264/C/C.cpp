#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pii;
#define pb push_back

const int N = 1e5+8;
const int K = 8;

int n, q;
ll v[N], c[N];
ll bs[2];
ll r[N], w[N];

int main () {
    scanf("%d %d", &n, &q);

    for (int i = 0; i < n; i++)
        scanf("%lld", &v[i]);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &c[i]);
        c[i]--;
    }

    while (q--) {
        ll a, b;
        scanf("%lld %lld", &a, &b);

        ll res = 0;

        bs[0] = bs[1] = n;
        for (int i = 0; i < n; i++)
            r[i] = w[i] = 0;
        r[n] = 0;

        for (int i = 0; i < n; i++) {
            ll aux = 0, curr = v[i]*b;

            if (w[c[i]])
                curr = max(curr, r[c[i]] + v[i]*a);

            int k = 0;
            if (bs[k] == c[i])
                k++;
            curr = max(curr, r[bs[k]] + v[i]*b);

            if (w[c[i]])
                r[c[i]] = max(r[c[i]], curr);
            else
                r[c[i]] = curr;
            w[c[i]] = 1;

            if (bs[0] != c[i]) {
                if (r[c[i]] > r[bs[1]])
                    bs[1] = c[i];
                if (r[bs[1]] > r[bs[0]])
                    swap(bs[0], bs[1]);
            }


            res = max(res, curr);
        }

        printf("%lld\n", res);
    }
}
