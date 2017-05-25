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

const int N = 1e6+8;

int n;
ll v[3][2];
ll a[N];
int q;

ll z[N][2];

int brute (int i, ll x, ll y, int ty = 1) {
    if (x >= v[1][0] && y >= v[1][1]) return 0;
    if (!ty) return N;
    if (i > q) return N;
    ll a = 1;
    ll b = 1;

    int rs = N;
    for (int k = 0; k <= z[i][1] && k <= rs; k++) {
        a = 1;
        b = 1;
        for (int j = 0; j < k; j++)
            b *= z[i][0];
        for (int j = 0; j <= k; j++) {
            rs = min(rs, brute(i+1, x*a, y*b, (k == z[i][1])) + k);

            a *= z[i][0];
            b /= z[i][0];
        }
    }
    return rs;
}

int solve () {
    v[2][0] = v[0][0];
    v[2][1] = v[0][1];

    int i = n-1;
    for (int k = 0; k < 2; k++) {
        while (i >= 0 && v[2][k] < v[1][k]) {
            v[2][k] *= a[i];
            i--;
        }
    }

    if (i == n-1)
        return 0;

    q = 0;
    
    z[q][0] = a[n-1];
    z[q][1] = 1;

    for (int j = n-2; j > i; j--) {
        if (z[q][0] == a[j]) {
            z[q][1]++;
        } else {
            q++;
            z[q][0] = a[j];
            z[q][1] = 1;
        }
    }

    return brute(0, v[0][0], v[0][1]);
}

int main () {
    for (int i =1 ; i >= 0; i--)
        for (int j = 0; j < 2; j++)
            scanf("%lld", &v[i][j]);

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%lld", &a[i]);

    sort(a, a+n);

    int rs = solve();
    swap(v[0][0], v[0][1]);
    rs = min(rs, solve());

    if (rs == N) rs = -1;
    printf("%d\n", rs);
}
