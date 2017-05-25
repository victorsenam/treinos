#include "weird_editor.h"
#include <message.h>

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

const int N = 1e7+2;
const ll MOD = 1e9+7;

ll mod (ll x)
{ return (x%MOD); }

ll vl[100][2][11], pot[100][2][11], zr[100][2][11], nx[100][2][11];

int main () {
    int c, idx;
    int n;

    c = NumberOfNodes();
    idx = MyNodeId();

    n = GetNumberLength();

    c = min(c, n);
    if (idx >= c) return 0;

    int jmp = ((n+c-1)/c);

    bool b = 0;
    for (int k = 0; k < 10; k++) {
        vl[idx][b][k] = 0;
        pot[idx][b][k] = zr[idx][b][k] = 1;
        nx[idx][b][k] = k;
    }
    b = !b;
    for (int i = min(n-1, (idx+1)*jmp - 1); i >= idx*jmp; i--) {
        ll cr = GetDigit(i);
        for (ll k = 0; k < 10; k++) {
            if (cr >= nx[idx][!b][k]) {
                vl[idx][b][k] = mod(vl[idx][!b][k] + mod(cr*pot[idx][!b][k]));
                pot[idx][b][k] = mod(pot[idx][!b][k] * 10ll);
                nx[idx][b][k] = cr;
                zr[idx][b][k] = zr[idx][!b][k];
            } else {
                vl[idx][b][k] = vl[idx][!b][k];
                pot[idx][b][k] = pot[idx][!b][k];
                nx[idx][b][k] = nx[idx][!b][k];
                zr[idx][b][k] = mod(zr[idx][!b][k] * 10ll);
            }
        }


        b = !b;
    }

    if (idx == c-1) {
        ll c_vl = vl[idx][!b][0];
        ll c_pot = pot[idx][!b][0];
        ll c_nx = nx[idx][!b][0];
        ll c_zr = zr[idx][!b][0];

        for (int i = c-2; i >= 0; i--) {
            PutLL(i, c_nx);
            Send(i);
            Receive(i);
            ll r_vl = GetLL(i);
            ll r_pot = GetLL(i);
            ll r_nx = GetLL(i);
            ll r_zr = GetLL(i);

            c_vl = mod(c_vl + mod(r_vl*c_pot));
            c_pot = mod(c_pot * r_pot);
            c_nx = r_nx;
            c_zr = mod(c_zr * r_zr);
        }

        c_vl = (c_vl * c_zr)%MOD;

        printf("%lld\n", c_vl);
    } else {
        Receive(c-1);
        ll c_nx = GetLL(c-1);

        PutLL(c-1, vl[idx][!b][c_nx]);
        PutLL(c-1, pot[idx][!b][c_nx]);
        PutLL(c-1, nx[idx][!b][c_nx]);
        PutLL(c-1, zr[idx][!b][c_nx]);
        Send(c-1);
    }
}
