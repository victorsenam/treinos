#include "rps.h"
#include <message.h>

#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int k, c, id, cs;
deque<pii> qu;

inline char win (char a, char b) {
    if (a > b) swap(a,b);

}

int main () {
    k = GetN();
    c = GetNumberOfNodes() - 1;
    id = MyNodeId();
    n = (1<<k);
    
    if (id == c) {
        cs = 0;

        qu.push_back(pii(0, n-1));

        while (qu.size() < c) {
            pii at = qu.front();
            if (at.first == at.second) break;
            qu.pop_front();

            pii lr = at, rg = at;
            int md = (at.first + at.second)/2;

            lr.second = md;
            rg.first = md+1;

            qu.push(lr);
            qu.push(rg);
        }

        int qq = qu.size();
        for (int i = 0; i < qq; i++) {
            pii at = qu[i];
            PutInt(i, at.first);
            PutInt(i, at.second);
            Send(i);
        }
        for (int i = qq; i < c; i++) {
            PutInt(i, -1);
            Send(i);
        }
    } else {
        Receive(c);
        int l = GetInt(c);
        if (l == -1) return 0;
        int r = GetInt(c);

        deque<char> dq;
        for (int i = l; i <= r; i++) {
            char c = GetFavoriteMove(i);
            dq.push_back(c);
        }

        while (dq.size() > 1) {
            char a = dq.front();
            dq.pop_front();
            char b = dq.front();
            dq.pop_front();

            dq.push_back(win(a, b));
        }

        PutInt(c, qd.front());
        Send(c);
    }
}
