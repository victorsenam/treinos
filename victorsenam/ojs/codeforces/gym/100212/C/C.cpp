#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 2e3+1;

int v[N];
ll ac[N];
ll pd[N][N];
int s[N][N];
int n;
bitset<N> rr[N];

void build (int l, int r, int k) {
    if (l == r) {
        return;
    }

    for (int i = l; i <= r; i++) {
        rr[i][k] = (i > s[l][r]);
        v[i] = k;
    }
    build(l, s[l][r], k+1);
    build(s[l][r] + 1, r, k+1);
}

int main () {
#ifdef ONLINE_JUDGE
    freopen("codes.in", "r", stdin);
    freopen("codes.out", "w", stdout);
#endif

    scanf("%d", &n);

    ac[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", v+i);
        ac[i] = ac[i-!!i] + v[i];
        s[i][i] = i;
    }



    for (int t = 1; t < n; t++) {
        for (int i = 1; i + t <= n; i++) {
            s[i][i+t] = i;
            pd[i][i+t] = pd[i][i] + pd[i+1][i+t];
            for (int k = s[i][i+t-1]; k <= s[i+1][i+t] && k < i+t; k++) {
                ll loc = pd[i][k] + pd[k+1][i+t];
                if (loc <= pd[i][i+t]) {
                    pd[i][i+t] = loc;
                    s[i][i+t] = k;
                }
            }

            pd[i][i+t] += ac[i+t] - ac[i-1];
        }
    }

    for (int i = 1; i <= n; i++)
        v[i] = -1;
    build(1, n, 0);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= v[i]; j++)
            printf("%d", (int) rr[i][j]);
        printf("\n");
    }
}
