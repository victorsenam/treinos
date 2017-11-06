#include <stdlib.h>
#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define INT64 "%I64d"
#else
#define INT64 "%lld"
#endif

#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define UNS64 "%I64u"
#else
#define UNS64 "%llu"
#endif
#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <ctime>
#include <cstring>
#include <cassert>
#include <bitset>
#include <sstream>
#include <queue>

#define pb push_back
#define mp make_pair
#define fs first
#define sc second
#define sz(a) ((int) (a).size())
#define eprintf(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

typedef long long int64;
typedef long double ldb;

const long double eps = 1e-9;
const int inf = (1 << 30) - 1;
const long long inf64 = ((long long)1 << 62) - 1;
const long double pi = acos(-1);

template <class T> T sqr (T x) {return x * x;}
template <class T> T abs (T x) {return x < 0 ? -x : x;}

const int MAXN = 6000;
const int MAXNN = 5 * MAXN + 100;

int n, nn;
long long a[MAXN], b[MAXN], sum[MAXN];
vector <long long> x, x_new;
vector <pair < pair <int, int>, int > > edg;
long long d[MAXNN];

long long get_min_dist (int v1, int v2) {
    for (int i = 0; i < nn; ++i) {
        d[i] = inf64;
    }
    d[v1] = 0;

    bool changed;
    for (int i = 0; i < n + 100; ++i) {
        changed = false;

        for (int j = 0; j < sz(edg); ++j) {
            if (d[edg[j].fs.sc] > d[edg[j].fs.fs] + edg[j].sc) {
                changed = true;
                d[edg[j].fs.sc] = d[edg[j].fs.fs] + edg[j].sc;
            } else if (d[edg[j].fs.fs] > d[edg[j].fs.sc] - edg[j].sc) {
                changed = true;
                d[edg[j].fs.fs] = d[edg[j].fs.sc] - edg[j].sc;
            }
        }


        for (int j = nn - 2; j >= 0; --j) {
            if (d[j] > d[j + 1]) {
                d[j] = d[j + 1];
                changed = true;
            }
        }

        if (!changed)
            break;
    }

    long long res = (changed ? -inf64 : d[v2]);
    return res;
}

int main () {
//  ios_base::sync_with_stdio(0);
	freopen("jordan.in", "rt", stdin);
	freopen("jordan.out", "wt", stdout);

    scanf ("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf (INT64 "" INT64 "" INT64, &a[i], &b[i], &sum[i]);
        a[i] *= 2, b[i] *= 2;
        x.pb(a[i]), x.pb(b[i]);
    }

    sort (x.begin(), x.end());
    x.resize(distance(x.begin(), unique(x.begin(), x.end())));

    for (int i = 0; i < sz(x) - 1; ++i) {
        bool key = false;

        for (int j = 0; j < n; ++j) {
            if (a[j] <= x[i] && b[j] >= x[i + 1]) {
                key = true;
                break;
            }
        }

        if (key) {
            x_new.pb((x[i] + x[i + 1]) / 2);
        }
    }

    for (int i = 0; i < sz(x_new); ++i) {
        x.pb(x_new[i]);
    }
    sort(x.begin(), x.end());
    assert(unique(x.begin(), x.end()) == x.end());

    nn = sz(x) + 1;
    for (int i = 0; i < n; ++i) {
        int v1 = (lower_bound(x.begin(), x.end(), a[i]) - x.begin());
        int v2 = (lower_bound(x.begin(), x.end(), b[i]) - x.begin()) + 1;

        edg.pb(mp(mp(v1, v2), sum[i]));
    }

    /*for (int i = 0; i < sz(edg); ++i) {
        cout << edg[i].fs.fs << " " << edg[i].fs.sc << " " << edg[i].sc << endl;
    }*/

    long long max_mu = get_min_dist(0, nn - 1);
    if (max_mu == -inf64) {
        printf ("-1 -1\n");
        return 0;
    }
    long long min_mu = -get_min_dist(nn - 1, 0);

    cout << min_mu << " " << max_mu << endl;

	return 0;
}
