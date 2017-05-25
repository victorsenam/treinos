#include "todd_and_steven.h"
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

const ll MOD = 1e9+7;

inline ll mod (ll x) {
    return (x%MOD);
}

ll c, idx, n[2], jmp;
ll mm[101][2][2];

ll GetV (int k, int i) {
    //if (mm[idx][k][0] = i)
        //return mm[idx][k][1];
    mm[idx][k][0] = i;
    if (i >= n[k])
        mm[idx][k][1] = LLONG_MAX;
    else if (k)
        mm[idx][k][1] = GetStevenValue(i);
    else
        mm[idx][k][1] = GetToddValue(i);
    return mm[idx][k][1];
}

void findPos (int p, int & a, int & b) {
    int lo = 0, hi = p;

    while (lo < hi) {
        int mid = (lo + hi + 1)/2;

        ll va = GetV(0, mid);
        ll vb = GetV(1, p-mid);

        if (vb > va) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    a = lo;

    lo = 0, hi = p;

    while (lo < hi) {
        int mid = (lo + hi + 1)/2;
        ll va = GetV(0, a);
        ll vb = GetV(1, mid);

        if (vb < va)
            lo = mid;
        else
            hi = mid-1;
    }

    b = lo;
}

int main () {
    c = NumberOfNodes();
    ll idx = MyNodeId();

    n[0] = GetToddLength();
    n[1] = GetStevenLength();

    c = min(c, n[0] + n[1]);
    if (idx >= c) return 0;

    jmp = (n[0] + n[1] + c - 1)/c;

    ll stp = jmp*idx;
    int l[2];
    findPos(stp, l[0], l[1]);

    printf("%d -> %lld %lld\n", stp, l[0], l[1]);

    ll fin = min(jmp*(idx+1), n[0]+n[1]);

    ll rs = 0;
    
    while (stp < fin) {
        if (GetV(0, l[0]) < GetV(1, l[1])) {
            rs = mod(rs + (stp^GetV(0,l[0])));
            l[0]++;
            stp++;
        } else {
            rs = mod(rs + (stp^GetV(1,l[1])));
            l[1]++;
            stp++;
        }
    }

    if (idx) {
        PutLL(0,rs);
        Send(0);
    } else {
        for (int i = 1; i < c; i++) {
            Receive(i);
            rs = mod(rs + GetLL(i));
        }
        printf("%lld\n", rs);
    }

}
