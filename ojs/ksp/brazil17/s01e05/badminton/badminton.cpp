#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
typedef long double num;
#define pb push_back

const ll tot = 1e9;

ll s, r;
num p, q, lp, lq;
int visi[32][32][3][3][2];
num memo[32][32][3][3][2];

num pd (int w, int l, int a, int b, int k) {
    num & me = memo[w][l][a][b][k];
    if (visi[w][l][a][b][k])
        return me;
    visi[w][l][a][b][k] = 1;

    if (a == 2) return me = 1.L;
    if (b == 2) return me = 0.L;
    
    if ((w >= 21 && w >= l+2) || w == 30)
        return me = pd(0,0,a+1,b,0);
    if ((l >= 21 && l >= w+2) || l == 30)
        return me = pd(0,0,a,b+1,1);

    if (k == 0)
        me = p*pd(w+1,l,a,b,0) + lp*pd(w,l+1,a,b,1);
    else
        me = q*pd(w+1,l,a,b,0) + lq*pd(w,l+1,a,b,1);

    return me;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> s >> r;
    p = num(s)/num(tot);
    lp = num(tot-s)/num(tot);
    q = num(r)/num(tot);
    lq = num(tot-r)/num(tot);
    cout << setprecision(20) << pd(0,0,0,0,0) << endl;
}

