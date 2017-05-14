#include "rps.h"
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

struct inst {
    int l, r;

    inst (int a, int b) : l(a), r(b) {}
};

struct pl {
    char m; int p;

    pl (int x) {
        p = x;
        m = GetFavoriteMove(p);
    }
};

int c, idx;

pl wins (pl a, pl b) {
    if (a.m == b.m || 
        (a.m == 'R' && b.m == 'S') ||
        (a.m == 'P' && b.m == 'R') ||
        (a.m == 'S' && b.m == 'P')
    ) return a;
    return b;
}

pl solve (int l, int r) {
    if (l == r)
        return pl(p);
    else
        return wins(solve(l, (l+r)/2), solve((l+r+1)/2, r));
}

int main () {
    c = NumberOfNodes();
    idx = MyNodeId();

    int k = GetN();
    int n = (1<<k);
    c = min(c, n);

    if (idx == c - 1) {
        int curr = 0;
        
        deque<inst> qu;
        qu.push_back(inst(0, n-1));

        while (qu.size() < c) {
            inst a = qu.front();
            qu.pop_front();

            qu.push_back(a.l, (a.l+a.r)/2);
            qu.push_back((a.l+a.r+1)/2, a.r);
        }

        int curr = 0;
        for (inst a : qu) {
            PutInt(curr, a.l);
            PutInt(curr, a.r);
            Send(curr);
            curr++;
        }
    }
    
    Receive(c-1);
    pl wn = solve(GetInt(c-1), GetInt(c-1));
    PutInt(c-1, wn.p);
    PutChar(c-1, wn.m);
    Send(c-1);

    if (idx == c-1) {
        ss(0, n-1);
        for (inst a : 
    }
}
