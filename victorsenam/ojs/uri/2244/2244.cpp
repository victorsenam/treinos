#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef double num;

const int N = 1e5+7;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {}/*{fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); }*/
#else
#define DEBUG(...) {}
#endif

struct cvx {
    num sa[N], sb[N], st[N], id[N];
    int ss;
    int lsi;

    inline num numdiv (num a, num b)
    { return a/b; }

    inline num inter (int i) {
        if (!i)
            return -1./0.; // MIN: LLONG_MAX

        return numdiv(sb[i]-sb[i-1], sa[i-1]-sa[i]);
    }

    void insert (num a, num b, int idx) {
        if (ss && sa[ss-1] == a) {
            if (sb[ss-1] >= b) // MIN: <=
                return;

            ss--;
        }

        sa[ss] = a;
        sb[ss] = b;
        id[ss] = idx;
        st[ss] = inter(ss);

        while (ss && st[ss] <= st[ss-1]) { // MIN: >=
            sa[ss-1] = sa[ss];
            sb[ss-1] = sb[ss];
            id[ss-1] = id[ss];
            ss--;
            st[ss] = inter(ss);
        }

        DEBUG("insert (%lld,%lld) at %lld\n", a, b, st[ss]);
        ss++;
    }

    inline void reset()
    { ss = 0; }

    num get (num x) { // da pra deixar linear se os x forem ordenados
        int l = upper_bound(st, st+ss, x) - st - 1; // MIN: comparar decrescente
        lsi = id[l];
        DEBUG("get %d (%lld,%lld) for %lld\n", l, sa[l], sb[l], x);
        return sa[l]*x + sb[l];
    }
};

cvx v[2];
int n;
num inp[N][4];
int p[N];
int cmp_k;
set<int> s;
double pr;

bool cmp_t (int i, int j) {
    for (int k = 0; k < 4; k++) {
        int nk = (k+cmp_k)%4;
        if (inp[i][nk] != inp[j][nk])
            return inp[i][nk] < inp[j][nk];
    }
    return 0;
}

bool iseq (int i, int j) {
    for (int k = 0; k < 2; k++) {
        int nk = (k+cmp_k)%4;
        if (inp[i][nk] != inp[j][nk])
            return 0;
    }
    return 1;
}

void go (int i, num x) {
    if (x < 0) return;
    if (inp[i][0]*x + inp[i][1] != v[0].get(x)) return;
    if (inp[i][2]*x + inp[i][3] != v[1].get(x)) return;
    s.insert(i);
}

int main () {
    srand(time(NULL)); rand(); rand();
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i] = i;
        for (int j = 0; j < 4; j++)
            scanf("%lf", &inp[i][j]);
        inp[i][2] = -inp[i][2];
        inp[i][3] = -inp[i][3];
    }

    for (cmp_k = 0; cmp_k < 4; cmp_k += 2) {
        sort(p, p+n, cmp_t);

        for (int _i = 0; _i < n; _i++) {
            int i = p[_i];

            v[cmp_k/2].insert(inp[i][cmp_k], inp[i][cmp_k+1], i);              

            if (_i) {
                if (iseq(i, p[_i-1])) {
                    s.insert(i);
                    s.insert(p[_i-1]);
                }
            }
        }
    }

    int hc = s.size();
    for (int j = 0; j < 2; j++) {
        bool ok = 1;
        for (int i = 1; i < v[j].ss; i++) {
            if (v[j].st[i] <= 0.) continue;
            pr = double(rand())/double(INT_MAX);
            go(v[j].id[i-1], pr*(v[j].st[i] + max(0., v[j].st[i-1])));
        }
        go(v[j].id[v[j].ss-1], max(v[j].st[v[j].ss-1], 0.) + 1.);
    }

    printf("%d\n", int(s.size()) - hc);
}
