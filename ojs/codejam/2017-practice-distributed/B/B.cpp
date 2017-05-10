#include "air_show.h"
#include <message.h>

#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef __int128 num;
typedef pair<ll,ll> pii;
#define pb push_back

ll n, nds, node, jum, l;
ll d;

void printa (ll p) {
    //printf("%lld %lld %lld\n", p%(1<<20), (p>>20)%(1<<20), (p>>40));
}

bool testDis (ll c, ll a, ll b, ll t, ll s) {
    ll m = (1<<20)-1;

    num res = 0;
    for (int i = 0; i < 2; i++) {
        num x = (c&m)*num(t);
        x -= num(a&m)*num(t-s);
        x -= num(b&m)*num(s);

        res += num(x)*num(x);

        a >>= 20;
        b >>= 20;
        c >>= 20;
    }

    bool r = (res < num(d)*num(d)*num(t)*num(t));
    //printf("%d\n", r);
    return r;
}

int main () {
    d = GetSafeDistance();
    n = GetNumSegments();
    nds = NumberOfNodes() - 1;
    node = MyNodeId();
    nds = min(n, nds);

    jum = (n+nds-1)/nds;
    l = jum*node;
    
    if (node > nds) return 0;
    if (node == nds) {
        int r[2] = {0,0};
        vector<vector<ll> > v(2, vector<ll>(nds+1, 0));
        
        for (int i = 0; i < nds; i++) {
            Receive(i);
            for (int j = 0; j < 2; j++) {
                v[j][i+1] = GetLL(i) + v[j][i];
            }
        }

        for (int k = 0; k < 2; k++) {
            int j = 0;
            for (int i = 0; i < nds; i++) {
                while (j < nds && v[!k][j+1] <= v[k][i])
                    j++;
                PutInt(i, j);
                PutLL(i, v[k][i]);
                PutLL(i, v[!k][j]);
                Send(i);
            }
        }

        r[0] = r[1] = -testDis(GetPosition(0, 0), GetPosition(1, 0), GetPosition(1, 0), 1, 0);

        for (int k = 0; k < 2; k++) {
            for (int i = 0; i < nds; i++) {
                Receive(i);
                r[k] += GetLL(i);
            }
        }
        printf("%d %d\n", r[0], r[1]);
    } else {
        for (int k = 0; k < 2; k++) {
            ll x = 0;
            for (int i = l; i < l + jum && i < n; i++)
                x += GetTime(k, i);
            PutLL(nds, x);

            //printf("[%d] [%lld..%lld[ = %lld\n", k, l, l+jum, x);
        }
        Send(nds);

        for (int k = 0; k < 2; k++) {
            Receive(nds);
            int rs = 0;
            int j = GetInt(nds);
            ll a = GetLL(nds); // o dos criticos (i, k)
            ll b = GetLL(nds); // o outro (j, !k)

            for (int i = l; i < l + jum && i < n; i++) {
                while (j < n && b + GetTime(!k, j) < a)
                    b += GetTime(!k, j);
                rs += testDis(GetPosition(k, i), GetPosition(!k, j), GetPosition(!k, j+1), GetTime(!k, j), a-b);
                //printf("[%d] %d[%lld] -> %d[%lld] = %d\n", k, i, a, j, b, rs);
                a += GetTime(k, i);
            }

            PutLL(nds, rs);
            Send(nds);
        }
    }
}
