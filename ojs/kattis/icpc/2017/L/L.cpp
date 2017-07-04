#include <bits/stdc++.h>
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug if(true)
#else
#define debug if(false)
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e5+7;

int n;

struct corn {
    bool cl;
    int id;
    int l, c;
};

corn v[N];
int to[N];
int rs[N];

void fail () {
    cout << "syntax error" << endl;
    exit(0);
}

int main () {
    cin >> n;

    for (int i = 0; i < n+n; i++) {
        cin >> v[i].l >> v[i].c;
        v[i].cl = !(i < n);
        v[i].id = i%n;
    }

    sort(v, v+n+n, [] (corn a, corn b) {
        if (a.c != b.c)
            return a.c < b.c;
        if (a.l != b.l)
            return a.l < b.l;
        return a.cl < b.cl;
    });

    map<int, int> mp;
    for (int i = 0; i < n+n; i++) {
        if (!v[i].cl) {
            if (mp.find(v[i].l) == mp.end()) {
                mp[v[i].l] = i;
            } else {
                fail();
            }
        } else {
            auto it = mp.upper_bound(v[i].l);
            if (it == mp.begin())
                fail();
            --it;

            to[it->second] = i;
            to[i] = it->second;

            mp.erase(it);
        }
    }

    map<int, vector<pii> > br[2];
    multiset<int> t;
    for (int i = 0; i < n+n; i++) {
        int l = v[i].l;
        int r = v[to[i]].l;
        if (l > r) swap(l,r);

        if (v[i].cl) {
            t.erase(t.find(l));
            t.erase(t.find(r));
            debug cout << "close [" << l << ".." << r << "]" << endl;
        } else {
            debug cout << "open " << v[i].id << " with " << v[to[i]].id << endl;
            rs[v[i].id] = v[to[i]].id + 1;
            
            br[0][v[i].l].push_back(pii(v[i].c, v[to[i]].c));
            if (v[i].l != v[to[i]].l)
                br[0][v[to[i]].l].push_back(pii(v[i].c, v[to[i]].c));

            br[1][v[i].c].push_back(pii(v[i].l, v[to[i]].l));
            if (v[i].c != v[to[i]].c)
                br[1][v[to[i]].c].push_back(pii(v[i].l, v[to[i]].l));
        }

        auto it = t.lower_bound(l);
        if (it != t.end() && *it <= r)
            fail();
        
        if (!v[i].cl) {
            debug cout << "open [" << l << ".." << r << "]" << endl;
            t.insert(l);
            t.insert(r);
        }
    }

    for (int k = 0; k < 2; k++) {
        for (pair<int, vector<pii> > cr : br[k]) {
            vector<pii> & v = cr.second;
            sort(v.begin(), v.end());
            for (int i = 1; i < v.size(); i++)
                if (v[i-1].second >= v[i].first)
                    fail();
        }
    }

    for (int i = 0; i < n; i++)
        cout << rs[i] << endl;
}
