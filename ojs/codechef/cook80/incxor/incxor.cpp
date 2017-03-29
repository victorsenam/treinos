#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef unsigned int ui;
typedef pair<int, int> pii;
#define pb push_back

const int N = 6;
const ll MOD = 1e9+7;

int ts;
int n;
ui a[N];
ll memo[40][(1<<6)][(1<<6)];

ll pd (int i, int st, int pr) {
    if (i < 0) return 1;
    
    ll & me = memo[i][st][pr];
    if (me != -1) return me;

    me = 0;
    for (int msk = 0; msk < (1<<n); msk++) {
        bool ok = 1;
        int nst = st;
        int npr = pr;
        for (int j = 0; ok && j < n-1; j++) {
            bool bf = (!!(msk&(1u<<j)));
            bool bs = (!!(msk&(1u<<(j+1))));
            if (!(pr&(1u<<j)) && (bs < bf)) {
                ok = 0;
            } else if (bs > bf) {
                npr |= (1u<<j);
            }
        }
        for (int j = 0; ok && j < n-1; j++) {
            bool bf = ((!!(a[j]&(1u<<i)))^(!!(msk&(1u<<j))));
            bool bs = ((!!(a[j+1]&(1u<<i)))^(!!(msk&(1u<<(j+1)))));
            if (!(st&(1u<<j)) && (bs < bf)) {
                ok = 0;
            } else if (bs > bf) {
                nst |= (1u<<j);
            }
        }

        if (!ok) continue;
        me = (me + pd(i-1, nst, npr))%MOD;
    }

    return me;
}

int main () {
    scanf("%d", &ts);

    while (ts--) {
        memset(memo, -1, sizeof memo);

        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%u", &a[i]);
        printf("%lld\n", pd(30, 0, 0));
    }

}
