#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define ff first
#define ss second
using namespace std;

typedef unsigned long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const double eps = 1e-9;
const int inf = INT_MAX;
//////////////0123456789
const int N = 200007;
const int modn = 1000000007;

int hd[N], to[N], nx[N], es;
ll res[N], pro[N], sec[N];
ll n, m;
ll aux, ans;
ll maxi, acc[N];

ll dfs (int u, int fr, ll up) {
    res[u] = max(up, pro[u]);
    ll ans = res[u];
    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if (fr == (ed^1))
            continue;
        ll temp = pro[u];
        if (temp == pro[to[ed]]+1)
            temp = sec[u];
        ans += dfs(to[ed], ed, max(temp, up)+1);
    }
    return ans;
}

ll prof (int u, int fr) {
    pro[u] = 0, sec[u] = 0;
    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if (fr == (ed^1))
            continue;

        ll temp = prof(to[ed], ed)+1;
        
        if (temp > pro[u]) {
            sec[u] = max(sec[u], pro[u]);
            pro[u] = temp;
        } else {
            sec[u] = max(sec[u], temp);
        }
    }
    return pro[u];
}

int main() {
    while (scanf("%lld %lld", &n, &m) != EOF) {
        memset(hd, 0, sizeof hd);
        es = 2;
        for (int i = 0; i < n+m-2; i++) {
            scanf("%d %d", to+es, to+es+1);
            to[es]--;
            to[es+1]--;
            if (i >= n-1) {
                to[es] += n;
                to[es+1] += n;
            }
            nx[es] = hd[to[es+1]]; hd[to[es+1]] = es;
            nx[es+1] = hd[to[es]]; hd[to[es]] = es+1;
            es += 2;
        }

        prof(0, -1);
        prof(n, -1);
        
        maxi = 0;
        for (int i = 0; i < n+m; i++)
            maxi = max(maxi, pro[i]);

        dfs(0, -1, 0);
        dfs(n, -1, 0);

        ans = 0;
        sort(res, res+n);
        sort(res+n, res+n+m);
        
        acc[m] = 0;
        for (int i = m-1; i >= 0; i--)
            acc[i] = acc[i+1] + res[i+n];
        
        //printf("-- %lld\n", maxi);

        for (int i = 0; i < n; i++) {
            if (maxi < res[i]+1) {
                ans += acc[0] + m*(res[i]+1);
            } else {
                ll hi = upper_bound(res+n, res+n+m, maxi-res[i]-1) - res - n;
             //   printf("%lld - > %lld\n", hi, acc[hi]);
                ans += hi*maxi + acc[hi] + (m-hi)*(res[i]+1);
            }
        }

        double vass = 1.*ans/double(n*m);
        vass = ((ll)(1e3*vass + .5))/1e3;
        printf("%.3lf\n", vass); 
    }
}

