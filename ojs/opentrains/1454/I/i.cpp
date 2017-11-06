#include <string.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int) n; ++i)
#define ford(i, n) for (int i = (int) n - 1; i >= 0; --i)
#define pdd pair<double, double>
#define mp make_pair
#define pb push_back
#define x first
#define y second

const int NMAX = 300002;
const double eps = 1e-11;

int n, m;
pdd p[NMAX];
vector<pdd> st;

bool remove(const pdd& a, const pdd& b, const pdd& c) {
    return (b.y - a.y) * (c.x - a.x) - (b.x - a.x) * (c.y - a.y) < 0;
}

double calc(const pdd& a, const pdd& b, double x) {
    return a.y + (x - a.x) * (b.y - a.y) / (b.x - a.x);
}

int main () {
    freopen("ito.in", "r", stdin);
    freopen("ito.out", "w", stdout);

    cin >> n >> m;
    forn(i, n) {
        int c, l, r;
        scanf("%d%d%d", &c, &l, &r);
        p[i] = mp(l * 1. / c, (l + r) * 1. / c / 2);
    }
    p[n] = mp(1., 1.);
    n++;
    sort(p, p + n);
    st.pb(p[n - 1]);
    ford(i, n - 1)
        if (p[i].y > st.back().y) {
            while (st.size() > 1 && remove(p[i], st[st.size() - 1], st[st.size() - 2]))
                st.pop_back();
            st.pb(p[i]);
        }
    reverse(st.begin(), st.end());

    forn(i, m) {
        int c, b;
        scanf("%d%d", &c, &b);
        double x = b * 1. / c;

        int idx = lower_bound(st.begin(), st.end(), mp(x - eps, 0.)) - st.begin();
        double ans = 0.;
        if (idx == 0) ans = st[idx].y;
        else ans = calc(st[idx - 1], st[idx], x);
        printf("%.10lf\n", c * ans);
    }

    return 0;
}