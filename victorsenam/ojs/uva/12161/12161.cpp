#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

struct point {
    ll dm, ln;

    bool operator < (const point & ot) const{
        if (dm == ot.dm)
            return ln > ot.ln;
        return dm < ot.dm;
    }
};

const int N = 70007;
int hd[N], to[N], nx[N], es;
ll dm[N], ln[N];
int n, m;
int ts;
set<point> s[N];
set<point>::iterator it, jt, tmp;
point sh[N], aux;
int ss;

ll dfs (int fr) {
    int u = to[fr];

    int tp = ss++;
    s[tp].clear();
    sh[tp].dm = sh[tp].ln = 0;
    s[tp].insert(sh[tp]); // it's just a null guy

    ll res = 0;
    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if ((ed|1) == (fr|1))
            continue;

        res = max(res, dfs(ed));

        sh[tp+1].dm += dm[ed];
        sh[tp+1].ln += ln[ed];

        aux.dm = m - sh[tp+1].dm;
        aux.ln = LLONG_MIN;

        if (s[tp].size() < s[tp+1].size()) {
            s[tp].swap(s[tp+1]);
            swap(sh[tp], sh[tp+1]);
        }

        for (it = s[tp+1].begin(); it != s[tp+1].end(); ++it) {
            aux.dm = m - sh[tp].dm - sh[tp+1].dm - it->dm;
            aux.ln = LLONG_MIN;

            jt = s[tp].upper_bound(aux);
            if (jt != s[tp].begin()) {
                --jt;
                res = max(sh[tp].ln + sh[tp+1].ln + it->ln + jt->ln, res);
            }
        }

        for (it = s[tp+1].begin(); it != s[tp+1].end(); ++it) {
            aux = *it;
            aux.dm += sh[tp+1].dm - sh[tp].dm;
            aux.ln += sh[tp+1].ln - sh[tp].ln;

            jt = s[tp].upper_bound(aux);

            if (jt != s[tp].begin()) {
                --jt;
                if (jt->ln >= aux.ln) {
                 //   DEBUG("(%d,%d) useless\n", aux.dm, aux.ln);
                    continue;
                }
                ++jt;
            }
            s[tp].insert(jt, aux); // c++11
            // s[tp].insert(jt, aux); // c++98
            // ++jt; // c++98

            while (jt != s[tp].end()) {
                tmp = jt;
                ++jt;
                if (tmp->ln <= aux.ln) {
                 //   DEBUG("(%d,%d) covers (%d,%d)\n", aux.dm, aux.ln, tmp->dm, tmp->ln);
                    s[tp].erase(tmp);
                } else
                    break;
            }
        }
        ss--;
    }

    DEBUG("%d  (%d,%d)\n", u+1, sh[tp].dm, sh[tp].ln);
    //for (it = s[tp].begin(); it != s[tp].end(); ++it) {
    //    DEBUG("(%d,%d)\n", it->dm+sh[tp].dm, it->ln+sh[tp].ln);
    //}

    return res;
}

int main () {
    scanf("%d", &ts);
    for (int tt = 1; tt <= ts; tt++) {
        scanf("%d %d", &n, &m);
        es = 2;
        memset(hd, 0, sizeof hd);

        for (int i = 1; i < n; i++) {
            scanf("%d %d %d %d", &to[es], &to[es+1], &dm[es], &ln[es]);
            to[es]--; to[es+1]--;
            dm[es+1] = dm[es]; ln[es+1] = ln[es];
            nx[es] = hd[to[es^1]]; hd[to[es^1]] = es; es++;
            nx[es] = hd[to[es^1]]; hd[to[es^1]] = es; es++;
        }

        to[0] = 0;
        ss = 0;

        printf("Case %d: %lld\n", tt, dfs(0));
    }
}
