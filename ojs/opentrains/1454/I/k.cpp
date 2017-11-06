#include <stdlib.h>
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

const long double eps = 1e-10;
const int inf = (1 << 30) - 1;
const long long inf64 = ((long long)1 << 62) - 1;
const long double pi = acos(-1);

template <class T> T sqr (T x) {return x * x;}
template <class T> T abs (T x) {return x < 0 ? -x : x;}

const int MAXN = 300 * 1000 + 100;

vector <int> adj[MAXN];
int num[MAXN];
long double f[MAXN], sum[MAXN];
bool used[MAXN];

class comp {
public:
    bool operator() (int i, int j) {
        if (fabs(f[i] - f[j]) < eps)
            return i < j;
        else
            return f[i] < f[j];
    }
};

set <int, comp> not_opt;
set <int, comp> :: iterator it;

int main () {
//  ios_base::sync_with_stdio(0);
	freopen("kolmogorov.in", "rt", stdin);
	freopen("kolmogorov.out", "wt", stdout);

    int n, m;
    scanf ("%d%d", &n, &m);

    int v1, v2;
    for (int i = 0; i < m; ++i) {
        scanf ("%d%d", &v1, &v2);
        v1--, v2--;
        adj[v1].pb(v2);
        adj[v2].pb(v1);
    }

    f[n - 1] = 0;
    not_opt.insert(n - 1);

    for (int i = 0; i < n; ++i) {
        if (not_opt.empty()) {
            break;
        }

        it = not_opt.begin();
        int v = (*it);
        used[v] = true;
        not_opt.erase(it);

        for (int j = 0; j < sz(adj[v]); ++j) {
            int u = adj[v][j];
            if (!used[u]) {
                not_opt.erase(u);
                num[u]++;
                sum[u] += f[v];
                f[u] = (sum[u] + m) / num[u];
                not_opt.insert(u);
            }
        }
    }

    printf ("%0.10lf\n", (double)f[0]);

	return 0;
}
