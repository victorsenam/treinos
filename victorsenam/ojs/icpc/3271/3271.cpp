#include <bits/stdc++.h>

using namespace std;

typedef unsigned int num;

const int N = 22;
const num M = (1u<<20);

pair<int, int> memo[M];
num obj;
int dest;
int n, m, p;
int hd[N], nx[N*N], to[N*N], es, hw[N*N];
int a, b, l;

pair<int, int> pd (num mask) {
    if ((mask|obj) == mask)
        return make_pair(0, 0);
    
    if (memo[mask].first != -1)
        return memo[mask];

    memo[mask].first = INT_MAX;
    memo[mask].second = INT_MAX;

    for (int i = 0; i < n; i++) {
        if ((mask&(1u<<i)) == 0)
            continue;
        for (int ed = hd[i]; ed != -1; ed = nx[ed]) {
            pair<int, int> loc = pd(mask|(1u<<to[ed]));
            loc.first += hw[ed];
            loc.second++;
            memo[mask] = min(memo[mask], loc);
        }
    }

    return memo[mask];
}

int main () {
    while (scanf("%d %d %d", &n, &dest, &m) != EOF && (n != -1)) {
        es = 0;
        for (int i = 0; i < (1u<<n); i++)
            memo[i].first = -1;
        memset(hd, -1, sizeof hd);

        for (int i = 0; i < m; i++){ 
            scanf("%d %d %d", &a, &b, &l);
            a--; b--;
            nx[es] = hd[a]; hd[a] = es; to[es] = b; hw[es] = l; es++;
            nx[es] = hd[b]; hd[b] = es; to[es] = a; hw[es] = l; es++;
        }

        scanf("%d", &p);
        obj = 0u;
        for (int i = 0; i < p; i++) {
            scanf("%d", &a);
            obj |= (1u<<(a-1));
        }

        printf("%d\n", pd(1u<<(dest-1)).first);
    }
}
