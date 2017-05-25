#include "pancakes.h"
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

int c, idx;
ll d, n;

int main () {
    c = NumberOfNodes();
    idx = MyNodeId();

    d = GetNumDiners();
    n = GetStackSize();

    c = min(ll(c), n);
    if (idx >= c) return 0;

    int jmp = ((n+c-1)/c);

    ll st = -1;
    ll fn = -1;
    ll res = 0;
    for (int i = idx*jmp; i < (idx+1)*jmp && i < n; i++) {
        ll a = GetStackItem(i);
        if (st == -1)
            st = a;

        if (fn > a)
            res++;
        fn = a;
    }

    if (idx) {
        PutLL(0, st);
        PutLL(0, fn);
        PutLL(0, res);
        Send(0);
    } else {
        for (int i = 1; i < c; i++) {
            Receive(i);
            ll a = GetLL(i);
            if (fn > a)
                res++;
            fn = GetLL(i);
            res += GetLL(i);
        }

        printf("%lld\n", res+1);
    }
}
