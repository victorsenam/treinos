#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 3e5+7;

ll w[N], t[N];
struct node {
    int u;

    bool operator < (const node & ot) const {
        if (w[u] - t[u] != w[ot.u] - t[ot.u])
            return w[u] - t[u] < w[ot.u] - t[ot.u];
        return u < ot.u;
    }
};

int p[N];
int n;
node aux;
set<node> s;

bool cmp_t (int i, int j) {
    return t[i] > t[j];
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &t[i], &w[i]);
        p[i] = i;
    }

    sort(p+1, p+n, cmp_t);

    int l = 1;
    int res = 0;

    while (l < n && t[p[l]] > t[0]) {
        aux.u = p[l++];
        s.insert(aux);
    }
    res = s.size();

    debug("[%d]\n", res+1);

    while (t[0] && s.size()) {
        aux = *s.begin();
        s.erase(s.begin());

        ll cs = w[aux.u] - t[aux.u] + 1;

        t[0] -= cs;
        if (t[0] < 0) break;

        while (l < n && t[p[l]] > t[0]) {
            aux.u = p[l++];
            s.insert(aux);
        }

        res = min(res, (int) s.size());
    }

    printf("%d\n", res+1);
}
