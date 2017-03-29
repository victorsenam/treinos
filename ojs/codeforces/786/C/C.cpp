#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;

int a[N];
int n;
int lm[N][2];
set<int> s[4*N];
int v[N], vs;

void build (int u, int l, int r) {
    lm[u][0] = l; lm[u][1] = r;
    if (l == r) return;
    int md = (l+r)/2;
    build(2*u, l, md);
    build(2*u, md+1, r);
}

int get (int l, int r) {
    vs = 0;
    get(1, l, r);
    for (int i = 1; i < vs; i++)
        if (s[v[i]].size() > s[v[0]].size())
            s[v[i]].swap(s[v[0]]);

    s[0].clear();
    for (int i = 1; i < vs; i++) {
        for (int el : s[v[i]]) {
            if (s[v[0]].find(el) == s[v[0]].end())
                s[0].insert(el);
        }
    }
    return s[0].size() + s[v[0]].size();
}

void get (int u, int l, int r) {
    if (l <= lm[u][0] && lm[u][1] <= r)
        v[vs++] = u;
    else if (lm[u][1] < l || r < lm[u][0])
        return;

    int md = (l+r)/2;
    get(2*u, l, md);
    get(2*u, md+1, r);
}

int main () {
    scanf("%d", &n);
    for (int 

}
