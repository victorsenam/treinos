#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stdout, __VA_ARGS__);}

const int N = 3e5+7;

ll bit[N];

void add (int i, ll x) {
    for (i += 2; i > 0; i-=(i&-i))
        bit[i] += x;
}

ll get (int i) {
    ll x = 0;
    for (i += 2; i < N; i+=(i&-i))
        x += bit[i];
    return x;
}

ll getval (int i) {
    return get(i);
}

set<int> s;
set<int>::iterator it;
multiset<int> pq;
multiset<int>::iterator jt;
ll a[N];
int n;
int m;

void tira (int x) {
    jt = pq.find(x);
    if (jt == pq.end()) assert(false);
    pq.erase(jt);
}

void rm (int i) {
    it = s.lower_bound(i);
    if (!i || *it != i)
        return;
    s.erase(it++);

    int r = *it;
    --it;
    int l = *it;
    tira(r-i);
    tira(i-l);
    pq.insert(r-l);
}

void update (int i) {
    it = s.lower_bound(i);
    if (!i || *it == i) return;

    int r = *it;
    --it;
    int l = *it;

    bool isc = 0;
    if (l == i-1) {
        if (getval(i) - getval(i-1) == 0)
            isc = 1;
    } else {
        ll a = getval(i-2);
        ll b = getval(i-1);
        ll c = getval(i);
        if ((c-b)*(b-a) < 0)
            isc = 1;
    }

    if (isc) {
        tira(r-l);
        s.insert(i);
        pq.insert(r-i);
        pq.insert(i-l);
    }
}

void pp () {
    printf("== ");
    for (int x : s) {
        printf("%d ", x);
    }
    printf("\n");
}

int main () {
    scanf("%d", &n);

    int ls = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        add(i-1, -a[i]);
        add(i, a[i]);

        bool isc = 0;
        if (!i) isc = 1;
        else if (ls == i-1) {
            if (a[i] - a[i-1] == 0)
                isc = 1;
        } else {
            if ((a[i] - a[i-1])*(a[i-1] - a[i-2]) < 0)
                isc = 1;
        }

        if (isc) {
            s.insert(i);
            pq.insert(i - ls);
            ls = i;
        }
    }
    s.insert(n);
    pq.insert(n-ls);

    pp();
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int l, r;
        ll d;
        scanf("%d %d %lld", &l, &r, &d);
        l--; r--;
        debug("[%d %d]\n", l, r);

        rm(l); rm(l+1);
        rm(r); rm(r+1);
        pp();

        add(r, d);
        add(l-1, -d);

        update(l); update(l+1);
        update(r); update(r+1);
        pp();

        printf("%d\n", *pq.rbegin());
    }

}
