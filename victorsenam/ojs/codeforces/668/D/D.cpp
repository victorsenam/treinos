#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;

struct fenwick {
    int n;
    vector<int> v;

    int build (int siz) {
        v.resize(siz+3, 0);
        n = siz;
    }

    void insert (int i, int x) {
        for (i+=2; i < n+3; i += (i&-i)) {
            v[i] += x;
        }
    }

    int get (int i) {
        int res = 0;
        for (i+=2; i > 0; i -= (i&-i))
            res += v[i];
        return res;
    }
};

map<int, set<int> > mp;
map<int, set<int> >::iterator it;
fenwick bit[N];
vector<int> vals;
vector<int> times[N];
int n;
int qr[N][3];

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < 3; k++)
            scanf("%d", &qr[i][k]);

        mp[qr[i][2]].insert(qr[i][1]);
    }

    for (it = mp.begin(); it != mp.end(); ++it) {
        for (int tim : it->second)
            times[vals.size()].push_back(tim);
        bit[vals.size()].build(times[vals.size()].size());
        vals.push_back(it->first);
    }
        

    for (int i = 0; i < n; i++) {
        int vl = lower_bound(vals.begin(), vals.end(), qr[i][2]) - vals.begin();
        int tm = lower_bound(times[vl].begin(), times[vl].end(), qr[i][1]) - times[vl].begin();
        if (qr[i][0] == 1)
            bit[vl].insert(tm, 1);
        else if (qr[i][0] == 2)
            bit[vl].insert(tm, -1);
        else
            printf("%d\n", bit[vl].get(tm));
            
    }
}
