#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

int n;
ll x[N], y[N];
ll ac[2][N];
int p[N];
ll in[2][N];
ll d;
priority_queue<ll> poi;

multiset<ll> s[2][2]; // s[vem de][vale em] 0: baixo, 1: cima

ll calc (ll x, ll y) {
    ll p = lower_bound(in[0], in[0] + n, x) - in[0];
    ll q = lower_bound(in[1], in[1] + n, y) - in[1];

    ll r = (p+p-n)*x - 2ll*ac[0][p] + ac[0][n];
    r += (q+q-n)*y - 2ll*ac[1][q] + ac[1][n];

    return r;
}

int checkboundary (ll p, ll l, ll r, bool b) {
    for (int i = 0; i < n; i++) {
        if (b && abs(p - x[i]) + abs(l - 1 - y[i]) > d)
            return i;
        if (!b && abs(p - x[i]) + abs(r + 1 - y[i]) > d)
            return i;
    }
    return -1;
}

ll solve (ll x) {
    ll l = 0;
    ll r = 4e9;

    if (s[0][0].size())
        r = min(r, *(s[0][0].begin()) + x);
    if (s[1][0].size())
        r = min(r, *(s[1][0].begin()) - x);

    if (s[0][1].size())
        l = max(l, *(s[0][1].rbegin()) + x);
    if (s[1][1].size())
        l = max(l, *(s[1][1].rbegin()) - x);

    ll il = l, ir = r;


    while (l + 4 < r) {
        ll q1 = (l + l + r)/3;
        ll q2 = (l + r + r)/3;

        if (calc(x,q1) < calc(x,q2))
            r = q2;
        else
            l = q1;
    }

    ll ans = LLONG_MAX;
    for (ll i = l; i <= r; i++)
        ans = min(ans, calc(x,i));
    return ans;
    cout << x << " [" << il << "," << ir << "] ";
    if (il <= ir) {
        cout << ans << " ";
    }
    cout << checkboundary(x, il, ir, 0) << " " << checkboundary(x,il,ir,1) << endl;
}

void putpoi (ll l, ll r, ll x) {
    for (ll i = max(l, x-1); i <= min(r, x+1); i++)
        poi.push(-i);
}

void putpoi (ll l, ll r) {
    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            if (s[a/2][a%2].empty() || s[b/2][b%2].empty()) continue;
            ll x = *(s[a/2][a%2].begin());
            ll y = *(s[b/2][b%2].begin());
            putpoi(l,r,abs(x-y)/2ll);

            y = *(s[b/2][b%2].rbegin());
            putpoi(l,r,abs(x-y)/2ll);

            x = *(s[a/2][a%2].rbegin());
            putpoi(l,r,abs(x-y)/2ll);
        }
    }
}

ll go () {
    sort(p, p+n, [] (int i, int j) {
        return in[0][i] < in[0][j];
    });

    for (int i = 0; i < n; i++) {
        x[i] = in[0][p[i]];
        y[i] = in[1][p[i]];

        s[0][0].insert(y[i] + d - x[i]);
        s[1][0].insert(y[i] + d + x[i]);

        s[0][1].insert(y[i] - d - x[i]);
        s[1][1].insert(y[i] - d + x[i]);
    }

    /*for (int j = 0; j < 2; j++)
        for (int i = 0; i < 2; i++)
            cout << i << " " << j << ": " << *s[i][j].begin() << " " << *s[i][j].rbegin() << endl;
        */

    sort(in[0], in[0]+n);
    sort(in[1], in[1]+n);
    
    for (int i = 0; i < n; i++) {
        ac[0][i+1] = ac[0][i] + in[0][i];
        ac[1][i+1] = ac[1][i] + in[1][i];
    }

    ll res = LLONG_MAX;

    //putpoi(x[n-1] - d, x[0] + d, 0ll);
    putpoi(x[n-1] - d, x[0] + d, x[n-1] - d);
    putpoi(x[n-1] - d, x[0] + d, x[0] + d);

    for (int i = 0; i < n; i++)
        putpoi(x[n-1] - d, x[0] + d, x[i]);
    putpoi(x[n-1] - d, x[0] + d);

    ll ls = -1e9;
    while (!poi.empty()) {
        ll ps = -poi.top();
        poi.pop();
        if (ps <= ls) continue;

        res = min(res, solve(ps));
        ls = ps;
    }

    return res;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> in[0][i] >> in[1][i];
        p[i] = i;
    }
    cin >> d;

    ll res = go();
    for (int i = 0; i < n; i++) {
        in[0][i] = y[i];
        in[1][i] = x[i];
    }
    res = min(res, go());


    if (res == LLONG_MAX)
        cout << "impossible" << endl;
    else
        cout << res << endl;
}
