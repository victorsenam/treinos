#include <message.h>
#include "again.h"

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

const ll MOD = 1e9+7;

pii get(int md) {
    pii v(0,0);
    for (ll i = md; i < GetN(); i += NumberOfNodes()) {
        v.first = (v.first + GetA(i))%MOD;
        v.second = (v.second + GetB(i))%MOD;
    }
    return v;
}

int main () {
    int node = MyNodeId();
    int qt = NumberOfNodes();

    if (!node) {
        ll res = 0;
        vector<pii> v;
        v.push_back(get(0));
        for (int i = 1; i < qt; i++) {
            pii curr;

            Receive(i);
            curr.first = GetLL(i);
            Receive(i);
            curr.second = GetLL(i);
            v.push_back(curr);
        }

        for (int i = 0; i < qt; i++)
            for (int j = 0; j < qt; j++)
                if ((i + j) % qt)
                    res = (res + (v[i].first*v[j].second))%MOD;
        printf("%lld\n", res);
    } else {
        pii curr = get(node);
        PutLL(0, curr.first);
        Send(0);
        PutLL(0, curr.second);
        Send(0);
    }
}
