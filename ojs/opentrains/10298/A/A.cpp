#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 2e5+7;

pair<ll, int> a[N];
set<pair<ll, int> > s;
ll x, y;
ll q[N];
ll res;
int n;
ll im, m;
int p;

int main () {
    scanf("%d %lld %lld %lld", &n, &im, &x, &y);
    
    for (int i = 0; i < n; i++) {
        scanf("%lld", &(a[i].first));
        a[i].second = i;
        s.insert(a[i]);
    }

    res = a[0].first + y;

    m = im;
    while (m) {
        pair<ll, int> cr = *(s.begin());
        s.erase(cr);
        cr.first += x;
        if (cr.second == 0)
            res = max(res, cr.first);
        s.insert(cr);
        m--;
    }

    s.clear();
    for (int i = 1; i < n; i++)
        s.insert(a[i]);

    for (m = im; m > 0; m--) {
        pair<ll, int> cr = *(s.begin());
        s.erase(cr);


        ll beg = cr.first - (m-1)*x;
        if (beg >= a[0].first) {
            res = max(res, min(a[0].first + y, beg) + m*x);
        }
        cr.first += x;
        s.insert(cr);
    }


    printf("%lld\n", res);
}
