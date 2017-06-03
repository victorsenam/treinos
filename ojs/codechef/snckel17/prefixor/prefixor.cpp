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
typedef unsigned long long int ui;

const int N = 2e6+7;
const int B = 33;

int n, q;
ui a[N];
int v[N];
int memo[N][B][4];

bool testa (int i, int j) {
    if (j > n) return 0;
    ui acc = a[i];

    for (int k = i+1; k < j; k++) {
        if (acc > (acc^a[k]))
            return 0;
        acc ^= a[k];
    }
    
    return 1;
}

int pd (int i, int b, int ty) {
    if (i >= n) return n;
    if (b < 0) return n;

    int & me = memo[i][b][ty];
    if (me != -1)
        return me;

    me = n;
    
    if (ty == 2) { // next one
        if (a[i]&(1u<<b))
            me = i;
        else
            me = pd(i+1, b, ty);
    } else if (ty == 1) { // starts with 1
        me = pd(i+1,b,2);
    } else { // starts with a[i]&(1u<<b)
        if (pd(i,b-1,0) < pd(i,b,2)) { // caga antes de mudar o valor desse bit
            me = pd(i,b-1,0);
        }

        for (int j = 0; j < b; j++) {
            if (pd(i,j,2) < pd(i,b,2) && pd(pd(i,j,2) + 1,j,2) > pd(i,b,2))
                me = min(me, pd(pd(i,b,2),j,2));
        }
        me = min(me, pd(pd(i,b,2),b-1,0));
        me = min(me, pd(pd(i,b,2)+1,b,2));
    }

    return me;
}

int main () {
    memset(memo, -1, sizeof memo);

    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n; i++) {
        v[i] = pd(i, B-1, 0);
        if (!testa(i, v[i]))
            cout << "nao e [" << i << "," << v[i] << ")" << endl;
        if (testa(i, v[i]+1))
            cout << "e [" << i << "," << v[i]+1 << ")" << endl;
        assert(testa(i, v[i]));
        assert(!testa(i, v[i]+1));
        cout << v[i] << " ";
    }
    cout << endl;
}
