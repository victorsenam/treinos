#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const ll N = 1e3+7;
const ll L = 507;
const ll MX = L*L*N;

int t[N];
int n;
int l;
int ac[N];
int c;
int tc;

ll memo[N][L];
int visi[N][L];

ll pd (int i, int q) {
    if (i == n)
        return 0;
    if (q == 0)
        return MX;

    ll & me = memo[i][q];
    if (visi[i][q] == tc)
        return me;
    visi[i][q] = tc;

    me = MX;
    ll tt = 0;
    for (int j = i; j < n; j++) {
        tt += t[j];
        ll cs;
        if (l < tt)
            break;
        else if (l == tt)
            cs = 0;
        else if (l - tt <= 10)
            cs = -c;
        else {
            cs = l - tt - 10;
            cs = cs*cs;
        }

        me = min(me, cs + pd(j+1, q-1));
    }
    return me;
}

int main () {
    while (scanf("%d", &n) != EOF && n) {
        scanf("%d %d", &l, &c);

        int curr = 0;
        int res = 1;
        for (int i = 0; i < n; i++) {
            scanf("%d", &t[i]);
            curr += t[i];
            if (curr > l) {
                res++;
                curr = t[i];
            }
        }
        
        if (tc)
            printf("\n");
        printf("Case %d:\n", ++tc);
        printf("Minimum number of lectures: %d\n", res);
        printf("Total dissatisfaction index: %lld\n", pd(0, res));
    }
}
