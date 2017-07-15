#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 103;
const ll MOD = 1e9+7;

ll memo[N][2][10][10][10][10][2][2];
char str[N];
char inp[N];

ll pd (int i, int f, int a, int b, int c, int d, int l, int ld) {
    if (!str[i])
        return l;

    ll & me = memo[i][f][a][b][c][d][l][ld];
    if (me != -1)
        return me;

    me = 0;
    for (int k = 0; k < 10; k++) {
        if (!f && k > str[i] - '0') break;
        int na = a, nb = b, nc = c, nd = d, nl = l;

        if (k||ld) {
            if (k <= a)
                na = k;
            else if (k <= b)
                nb = k;
            else if (k <= c)
                nc = k;
            else if (k <= d)
                nd = k;
            else
                nl = 1;
        }

        me = (me + pd(i+1, (f||(k<str[i]-'0')), na, nb, nc, nd, nl, ld||k))%MOD;
    }

    return me;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> inp;
    cin >> str;

    memset(memo, -1, sizeof memo);
    ll rs = pd(0, 0, 10, 10, 10, 10, 0, 0);

    for (int i = 0; i < N; i++)
        str[i] = inp[i];
    int n = strlen(str);

    bool cr = 1;
    for (int i = n-1; i >= 0 && cr; i--) {
        if (str[i] == '0') {
            cr = 1;
            str[i] = '9';
        } else {
            cr = 0;
            str[i]--;
        }
    }

    assert(!cr);
    memset(memo, -1, sizeof memo);
    rs = (((rs - pd(0, 0, 10, 10, 10, 10, 0, 0))%MOD) + MOD)%MOD;
    cout << rs << endl;
}

