#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define ff first
#define ss second
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const double eps = 1e-9;
const int inf = INT_MAX;
//////////////0123456789
const int N = 70;
const int modn = 1000000007;

ll memo[N][2];
int visi[N][2], turn;
bool a[N];
ll aux, in, la;
int st;

ll res;

ll pd (int i, bool pre) {
    if (i >= N) return 0;
    ll & me = memo[i][pre];

    if (visi[i][pre] == turn)
        return me;
    visi[i][pre] = turn;

    me = pd(i+1, (pre||a[i]));

    if (pre || a[i]) {
        me += pd(i+1, pre);
        if (pre)
            me += (1ll<<(N-i-1));
        else
            me += in%(1ll<<(N-i-1))+1;
    }
    return me;
}

int main() {
    while (scanf("%lld %lld", &in, &la) != EOF) {
        in--;
        aux = in;
        ++turn;
        st = 0;
        while (st < N) {
            a[N-(++st)] = (aux&1);
            aux >>= 1;
        }

        res = -pd(0, 0);

        in = la;
        aux = in;
        ++turn;
        st = 0;
        while (st < N) {
            a[N-(++st)] = (aux&1);
            aux >>= 1;
        }

        res += pd(0,0);
        printf("%lld\n", res);
    }
}
