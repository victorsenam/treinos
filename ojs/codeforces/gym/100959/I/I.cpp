#include <bits/stdc++.h>
#define debug(...) {fprllf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

const ll N = 1e5+7;

struct evt {
    ll a, b;
    ll t;

    bool operator < (const evt & ot) const {
        if (t != ot.t) return t < ot.t;
        if (a != ot.a) return a < ot.a;
        return b < ot.b;
    }
};

map<pii, ll> mp[2];
map<pii, ll>::iterator it;

ll n, t;
ll p[N][2];
char d[N];
ll st[N];
char vs[600][N];


pii getpos (ll i, ll t) {
    if (d[i] == 'U')
        return pii(p[i][0], p[i][1]+(t-st[i]));
    if (d[i] == 'D')
        return pii(p[i][0], p[i][1]-(t-st[i]));
    if (d[i] == 'L')
        return pii(p[i][0]-(t-st[i]), p[i][1]);
    if (d[i] == 'R')
        return pii(p[i][0]+(t-st[i]), p[i][1]);
    assert(false);
}

ll getnext (ll i, ll t) {
    //prllf("call %d %d\n", i, t);
    if (d[i] == 'U') {
        it = mp[0].upper_bound(getpos(i,t));
        if (it == mp[0].end())
            return -1;
        ll j = it->second;
        if (p[j][0] != p[i][0])
            return -1;
        return j;
    } else if (d[i] == 'D') {
        it = mp[0].lower_bound(getpos(i,t));
        if (it == mp[0].begin())
            return -1;
        --it;
        ll j = it->second;
        if (p[j][0] != p[i][0])
            return -1;
        return j;
    } else if (d[i] == 'R') {
        pii aux = getpos(i,t);
        it = mp[1].upper_bound(pii(aux.second, aux.first));
        if (it == mp[1].end())
            return -1;
        ll j = it->second;
        if (p[j][1] != p[i][1])
            return -1;
        return j;
    } else if (d[i] == 'L') {
        pii aux = getpos(i,t);
        it = mp[1].lower_bound(pii(aux.second, aux.first));
        if (it == mp[1].begin())
            return -1;
        --it;
        ll j = it->second;
        if (p[j][1] != p[i][1])
            return -1;
        return j;
    }
    assert(false);
}

ll dist (pii a, pii b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main () {
    scanf("%lld %lld", &n, &t);

    for (ll i = 0; i < n; i++) {
        scanf("%lld %lld %c", &p[i][0], &p[i][1], &d[i]);
        mp[0][pii(p[i][0], p[i][1])] = i;
        mp[1][pii(p[i][1], p[i][0])] = i;
        st[i] = t;
    }
    
    evt att;
    set<evt> pq;
    st[0] = 0;
    att.a = 0;
    att.b = getnext(0, 0);
    if (att.b != -1) {
        att.t = dist(pii(p[0][0], p[0][1]), pii(p[att.b][0], p[att.b][1]));
        pq.insert(att);
    }

    while (!pq.empty()) {
        att = *(pq.begin());
        pq.erase(pq.begin());

        //prllf("[%d] : %d <-> %d\n", att.t, att.a, att.b);
    
        if (vs[d[att.a]][att.b]) continue;
        vs[d[att.a]][att.b] = 1;

        assert(st[att.b] == t || st[att.b] <= att.t);
        st[att.b] = min(st[att.b], att.t);
        
        ll j = getnext(att.a, att.t);
        //prllf("%d hits %d\n", att.a, j);
        if (j != -1) {
            evt nxt = att;
            nxt.b = j;
            nxt.t += dist(getpos(nxt.a, att.t), pii(p[nxt.b][0], p[nxt.b][1]));

            if (nxt.t < t)
                pq.insert(nxt);
        }

        j = getnext(att.b, att.t);
        //prllf("%d hits %d\n", att.b, j);
        if (j != -1) {
            evt nxt = att;
            nxt.a = att.b;
            nxt.b = j;
            nxt.t += dist(getpos(nxt.a, att.t), pii(p[nxt.b][0], p[nxt.b][1]));

            if (nxt.t < t)
                pq.insert(nxt);
        }
    }

    for (ll i = 0; i < n; i++) {
        pii aux = getpos(i, t);
        //prllf("%d: ", st[i]);
        printf("%lld %lld\n", aux.first, aux.second);
    }
}
