#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;
int n, q;

ll v[N], c[N];
int p[2][N];
int ord[N];

int main () {
    scanf("%d %d", &n, &q);

    for (int i = 0; i < n; i++)
        scanf("%lld", &v[i]);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &c[i]);
        p[0][i] = p[1][i] = i;
    }

    sort(p[0], p[0]+n, [] (int i, int j) {
        if (c[i] != c[j]) c[i] < c[j];
        return v[i] < v[j];
    });

    for (int _i = 0; _i < n; _i++) {
        int i = p[0][_i];
        if (_i) {
            int j = p[0][_i-1];

            if (c[i] == c[j])
                ord[i] = ord[j] + 1;
            else
                ord[i] = 0;
        } else {
            ord[i] = 0;
        }
    }

    sort(p[1], p[1]+n, [] (int i, int j) {
        if (ord[i] != ord[j]) return ord[i] < ord[j];
        if (c[i] != c[j]) return c[i] < c[j];
        return v[i] > v[j];
    });

    ll a, b;
    while (q--) {
        scanf("%lld %lld", &a, &b);
        ll res = 0;
        for (int k = 0; k < 2; k++) {
            int ls = -1;
            ll curr = 0;
            for (int _i = 0; _i < n; _i++) {
                int i = p[k][_i];
                if (i == -1) 
                    break;

                if (ls == c[i])
                    curr += a*v[i];
                else
                    curr += b*v[i];
                ls = c[i];
            }

            res = max(res, curr);
        }
    }
}
