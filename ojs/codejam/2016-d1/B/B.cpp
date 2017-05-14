#include "oops.h"
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

int c, my, n;

int main () {
    c = NumberOfNodes();
    my = MyNodeId();

    n = GetN();
    c = min(c, n);
    if (my >= c) return 0;
    int jmp = (n+c-1)/c;

    ll mn = 1e18;
    ll mx = -1e18;

    for (int i = my*jmp; i < n && i < (my+1)*jmp; i++) {
        ll a = GetNumber(i);
        mn = min(mn, a);
        mx = max(mx, a);
    }

    if (my == 0) {
        for (int nd = 1; nd < c; nd++) {
            Receive(nd);
            mn = min(mn, GetLL(nd));
            mx = max(mx, GetLL(nd));
        }

        printf("%lld\n", mx-mn);
    } else {
        PutLL(0, mn);
        PutLL(0, mx);
        Send(0);
    }

}
