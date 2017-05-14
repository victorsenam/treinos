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

int c, idx;
ll pot, vl;
int n;

int main () {
    c = NumberOfNodes();
    idx = MyNodeId();

    n = GetNumberLength();

    c = min(c, n);
    if (idx >= c) return 0;

    int jmp = ((n+c-1)/c);

    int st = 0;
    vl = 0;
    ll zr = 1;
    pot = 1;
    for (int i = idx*jmp; i < (idx+1)*jmp && i < n; i++) {
        ll v = GetDigit(i);
        if (v) {
            pot = (pot * 10ll)%MOD;
            vl = (vl * 10ll)%MOD;
            vl = (vl + v)%MOD;
        } else {
            zr = (zr * 10ll)%MOD;
        }
    }

    //printf("%d -> vl = %lld, pot = %lld, zr = %lld\n", idx, vl, pot, zr);

    if (!idx) {
        debug("%d -> vl = %lld\n", 0, vl);
        for (int i = 1; i < c; i++) {
            Receive(i);
            ll pp = GetLL(i);
            ll vv = GetLL(i);
            ll zz = GetLL(i);
            zr = (zr * zz)%MOD;

            vl = (vl * pp)%MOD;
            vl = (vl + vv)%MOD;
            debug("%d -> vl = %lld\n", i, vl);
        }

        vl = (vl * zr)%MOD;

        printf("%lld\n", vl);
    } else {
        PutLL(0, pot);
        PutLL(0, vl);
        PutLL(0, zr);
        Send(0);
    }
}
