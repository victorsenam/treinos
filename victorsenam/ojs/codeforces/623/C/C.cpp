#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;

int n;
ll ix[N], iy[N], x[N], py[N], gy[N];
ll ip[N], ig[N], fp[N], fg[N];
int p[N];

bool cmp_a (int i, int j) {
    return ix[i] < ix[j];
}

inline ll dist(ll a, ll b) {
    return (b-a)*(b-a);
}
inline ll calc(int i, ll mi, ll ma) {
    return dist(min(mi,accmin[i]), max(ma,accmax[i]));
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", ix+i, iy+i);
        p[i] = i;
    }

    sort(p, p+n, cmp_a);

    int m = 1;
    x[1] = ix[p[1]];
    py[1] = gy[1] = iy[p[1]];
    
    for (int i = 0; i < n; i++) {
        if (x[m] == ix[p[i]]) {
            py[m] = min(iy[p[i]], py[m]);
            gy[m] = max(iy[p[i]], gy[m]);
        } else {
            x[++m] = ix[p[i]];
            py[m] = gy[m] = iy[p[i]];
        }
    }

    ll res = dist(x[m-1], x[0]);
    ip[0] = fp[m+1] = LLONG_MAX;
    ig[0] = fg[m+1] = LLONG_MIN;

    for (int i = 1; i <= m; i++) {
        ip[i] = min(py[i], ip[i-1]);
        ig[i] = max(gy[i], ig[i-1]);

        fp[m+1-i] = min(py[i], fp[m+2-i]);
        fg[m+1-i] = min(gy[i], fg[m+2-i]);
    }
}
