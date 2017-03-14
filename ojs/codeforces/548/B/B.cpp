#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 500

map<int, int> mp[N];
map<int, int>::iterator lo, hi;
multiset<int> s;
bool il, jl, jr;
int n, m, q;
int a, b;
int siz;
int c;

int main () {
    scanf("%d %d %d", &n, &m, &q);

    s.insert(0);
    for (int i = 0; i < n; i++) {
        siz = 0;
        for (int j = 0; j <= m; j++) {
            if (j < m) scanf("%d", &c);
            else c = 0;

            if (c)
                siz++;
            else if (siz) {
                mp[i].insert(make_pair(j-siz, siz));
                debug("insert(%d)", siz);
                s.insert(siz);
                siz = 0;
            }
        }
    }

    for (int i = 0; i < q; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        lo = mp[a].lower_bound(b);
        hi = mp[a].upper_bound(b);
        debug("lo (%d, %d)", lo->first, lo->second);
        debug("hi (%d, %d)", hi->first, hi->second);

        il = (lo != mp[a].end() && lo->first <= b && lo->first + lo->second > b);
        jl = (lo != mp[a].end() && lo->first <= b && lo->first + lo->second == b);
        jr = (hi != mp[a].end() && hi->first > b && hi->first == b + 1);

        if (il) {
            s.erase(lo->second);
            s.insert(lo->second - b - 1);
            s.insert(b - lo->first);

            debug("remove(%d, %d)", lo->first, lo->second);
            debug("insert(%d, %d)", lo->first, lo->second-b-1);
            debug("insert(%d, %d)", b, b - lo->first);

            mp[a].insert(make_pair(b+1, lo->second - b - 1));
            lo->second = b - lo->first;
        } else if (jl && jr) {
            s.erase(hi->second);
            s.erase(lo->second);
            debug("remove(%d, %d)", hi->first, hi->second);
            debug("remove(%d, %d)", lo->first, lo->second);
            lo->second += hi->second + 1;
            s.insert(lo->second);
            debug("insert(%d, %d)", lo->first, lo->second);
            mp[a].erase(hi);
        } else if (jl) {
            s.erase(lo->second);
            debug("remove(%d, %d)", lo->first, lo->second);
            lo->second++;
            s.insert(lo->second);
            debug("insert(%d, %d)", lo->first, lo->second);
        } else if (jr) {
            s.erase(hi->second);
            debug("remove(%d, %d)", hi->first, hi->second);
            s.insert(hi->second+1);
            debug("insert(%d, %d)", b, hi->second+1);
            mp[a].insert(make_pair(b, hi->second+1));
            mp[a].erase(hi->first);
        } else {
            mp[a].insert(make_pair(b, 1));
            s.insert(1);
            debug("insert(%d, %d)", b, 1);
        }

        printf("%d\n", *(s.rend()));
    }
}
