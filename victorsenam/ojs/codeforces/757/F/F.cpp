#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 2e5+7;
const int M = 6e5+7;
const ll INF = 1e16;

int n, m;
ll dist[N];
int visi[N];
int fr[N];
int mrk[M];
int hd[N], nx[M], to[M], es;
ll wg[M];
int dg[N];
vector<int> srt[N];

bool isbad (int ed) {
    return (dist[to[ed^1]] + wg[ed] == dist[to[ed]]);
}

struct sml {
    int sz;
    set<int> st;
    int safe;
};

struct node {
    int u, d, fr;

    bool operator < (const node & ot) const {
        if (d != ot.d) return d > ot.d;
        return u > ot.u;
    }
};

sml x[N];

void djs (int u) {
    priority_queue<node> pq;
    node aux;
    aux.u = u;
    aux.d = 0;
    aux.fr = 0;
    dist[u] = 0;

    pq.push(aux);

    while (!pq.empty()) {
        node att = pq.top();
        pq.pop();
        
        if (visi[att.u]) continue;
        visi[att.u] = 1;
        fr[att.u] = att.fr;
        if (att.fr >= 2) {
            dg[to[att.fr^1]]++;
        }
        mrk[att.fr] = 1;

        //printf("%d : dist %lld from %d\n", att.u+1, att.d, !att.fr?-1:to[att.fr^1]+1);

        for (int ed = hd[att.u]; ed; ed = nx[ed]) {
            node nxt = att;
            nxt.u = to[ed];
            nxt.d += wg[ed];
            nxt.fr = ed;

            if (dist[nxt.u] <= nxt.d) continue;
            dist[nxt.u] = nxt.d;
            pq.push(nxt);
        }
    }
}

int main () {
    int s;
    scanf("%d %d %d", &n, &m, &s);
    s--;
    
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }

    es = 2;
    for (int i = 0; i < m; i++) {
        int a, b;
        ll ww;
        scanf("%d %d %lld", &a, &b, &ww);
        a--; b--;

        nx[es] = hd[a]; to[es] = b; wg[es] = ww; hd[a] = es++;
        nx[es] = hd[b]; to[es] = a; wg[es] = ww; hd[b] = es++;
    }

    djs(s);

    queue<int> qu;
    for (int i = 0; i < n; i++) {
        if (dg[i] == 0)
            qu.push(i);
    }

    for (int i = 2; i < es; i+=2) {
        if (dist[to[i]] + wg[i] == dist[to[i^1]] || dist[to[i^1]] + wg[i] == dist[to[i]]) {
            if (mrk[i] || mrk[i^1]) continue;
            srt[to[i]].push_back(i);
            srt[to[i^1]].push_back(i^1);
        }
    }

    int mx = 0;
    while (!qu.empty()) {
        int u = qu.front();
        qu.pop();

        if (!fr[u]) continue;

        int tm = 0;
        for (int ed : srt[u]) {
            if (isbad(ed) && x[u].st.find(ed^1) != x[u].st.end())
                tm++;
        }

        x[u].sz++;
        //printf("%d : dist %lld sz %d size %d tm %d\n", u+1, dist[u], x[u].sz, (int) x[u].st.size(), tm);

        if (x[u].safe + tm == x[u].st.size())
            mx = max(mx, (int) x[u].sz);

        for (int ed : srt[u]) {
            if (x[u].st.find(ed^1) == x[u].st.end()) {
                x[u].st.insert(ed);
                x[u].safe += !isbad(ed);
            } else {
                x[u].st.erase(ed^1);
                x[u].safe -= !isbad(ed^1);
            }
        }

        int pr = to[fr[u]^1];

        if (x[u].st.size() > x[pr].st.size()) {
            x[u].st.swap(x[pr].st);
            swap(x[u].safe, x[pr].safe);
        }

        x[pr].sz += x[u].sz;
        for (int ed : x[u].st) {
            if (x[pr].st.find(ed^1) == x[pr].st.end()) {
                x[pr].st.insert(ed);
                x[pr].safe += !isbad(ed);
            } else {
                x[pr].st.erase(ed^1);
                x[pr].safe -= !isbad(ed^1);
            }
        }
        x[u].st.clear();

        dg[pr]--;

        if (!dg[pr])
            qu.push(pr);
    }

    printf("%d\n", mx);
}
