#line 2 "ChristmasBinaryTree.cpp"
#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int N = 1e2+7;
const ll MOD = 1e9+7;

map<ll, ll> memo[N][N];
vector<int> l[2];
int n;

ll pd (ll s, int a, int b) {
    if (s == 0) {
        return 0;
    } else if (s == 1) {
        return (a == b);
    }

    if (memo[a][b].find(s) != memo[a][b].end())
        return memo[a][b][s];

    ll me = 0;

    for (int x = 0; x < n; x++) {
        ll loc = (pd(s/2, l[0][x], b) + pd(s/2, l[1][x], b))%MOD;
        loc = (pd((s+1)/2, a, x) * loc)%MOD;
        me = (me + loc)%MOD;
    }
    return memo[a][b][s] = me;
}

class ChristmasBinaryTree {
    public:
    int count(long long i_depth, vector <int> i_left, vector <int> i_right) {
        ll mx = 0;
        l[0] = i_left;
        l[1] = i_right;
        n = i_left.size();
        for (int i = 0; i < n; i++) {
            ll vl = 0;
            for (int j = 0; j < n; j++) {
                ll loc = pd(i_depth, i, j);
                loc = (loc*loc)%MOD;
                vl = (vl + loc)%MOD;
            }
            mx = max(mx, vl);
        }
        return (int) mx;
    }
};


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
