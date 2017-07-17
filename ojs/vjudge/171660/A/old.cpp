#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 3123;

int h[N], a[N], b[N], x[N], y[N], r[N];
vector<int> adj[N]; int pr[N], mrk[N], deg[N];

queue<int> q;

ll solve(deque<int> &ret) {
    printf("solve(");
    queue<int> q2 = q;
    while(!q2.empty()) printf("%d ", q2.front() + 1), q2.pop();
    puts(")");
    if(q.empty()) return 0;
    int i = q.front(); q.pop();
    if(pr[i] != -1 && --deg[pr[i]] == 0)
        q.push(pr[i]);
    ll ans = solve(ret);
    printf("addin %d (%d)\n", i + 1, a[i] + b[i]);
    if(a[i] + b[i] >= 0) {
        ans += (a[i] + b[i]) * int(h[i] / 2);
        if(a[i] >= 0 && !ret.empty() && (h[i] & 1)) {
            ans += a[i];
            swap(i, ret.front());
            ret.push_front(i);
        } else if(a[i] >= a[i] + b[i] && !ret.empty() && !(h[i] & 1)) {
            ans -= b[i];
            swap(i, ret.front());
            ret.push_front(i);
        } else ret.push_front(i);
    } else {
        if(a[i] >= 0 && !ret.empty()) {
            ans += a[i];
            swap(i, ret.back());
            ret.push_back(i);
        } else ret.push_back(i);
    }
    return ans;
}

void dfs(int i, int h) {
    ::h[i] = h;
    for(int j : adj[i])
        dfs(j, h + 1);
}

inline ll sq(ll x) { return x * x; }

// is i inside j?
inline bool inside(int i, int j) {
    return r[j] > r[i] && sq(x[i] - x[j]) + sq(y[i] - y[j]) < sq(r[j] - r[i]);
}

int p[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t, i, n, j;
    cin >> t;
    while(t--) {
        cin >> n;
        for(i = 0; i < n; i++) {
            adj[i].clear(); mrk[i] = 0;
            cin >> x[i] >> y[i] >> r[i] >> a[i] >> b[i];
            p[i] = i; pr[i] = -1; deg[i] = 0;
        }
        sort(p, p + n, [](int i, int j) { return r[i] < r[j]; });
        for(int i_ = 0; i_ < n; i_++) {
            i = p[i_];
            for(j = 0; j < n; j++)
                if(!mrk[j] && inside(j, i)) {
                    mrk[j] = 1;
                    adj[i].pb(j);
                    deg[i]++;
                    pr[j] = i;
                }
        }
        for(i = 0; i < n; i++)
            for(int j : adj[i])
                printf("%d->%d\n", i, j);
        for(i = 0; i < n; i++)
            if(pr[i] == -1)
                dfs(i, 0);
        deque<int> P;
        for(i = 0; i < n; i++)
            if(deg[i] == 0)
                q.push(i);
        printf("%lld\n", solve(P));
        printf("sz %d\n", P.size());
        for(i = 0; i < n; i++)
            printf("%d%c", P[i] + 1, " \n"[i == n - 1]);
    }
}
