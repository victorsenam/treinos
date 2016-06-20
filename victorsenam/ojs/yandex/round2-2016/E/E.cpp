#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define GNU __gnu_pbds

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
namespace GNU { typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; }
using GNU::ordered_set;

#ifdef ONLINE_JUDGE
#define lld I64d
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 400007;

ordered_set s[N], ss;
int n;
int v[N];
int a, b;
int hd[N], to[N], nx[N], es, deg[N], fr[N], ref[N];
int qu[N], qi, qf;
int siz[N];

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", v+i);
    }

    es = ss = 1;
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;

        nx[es] = hd[a]; to[es] = b; hd[a] = es++;
        nx[es] = hd[b]; to[es] = a; hd[b] = es++;
        deg[a]++; deg[b]++;
    }

    for (int i = 0; i < n; i++)
        if (deg[i] == 1)
            qu[qf++] = i;

    while (qi < qf) {
        int u = qu[qi++];

        for (fr[u] = hd[u]; fr[u] && deg[fr[u]] > 1; fr[u] = nx[fr[u]]);

        addTo(ref[u], v[u]);

        
    }
}