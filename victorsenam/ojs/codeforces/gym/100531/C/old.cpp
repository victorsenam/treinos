#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 3e4+7;

char str[N];
int n;
stack<int> st;
int lim[N][2];
list<int> adj[N];
int es;
int res;
int lt[N];

bool leaf(int u) { return lim[u][0] == lim[u][1]; }

void printalista (int u) {
    if (lim[u][0] == lim[u][1]) {
        debug("%c", str[lim[u][0]]);
    } else {
        for (int i : adj[u]) {
            if (lim[i][0] != lim[i][1])
                debug("(");
            printalista(i);
            if (lim[i][0] != lim[i][1])
                debug(")");
        }
    }
}

char solve (int u) {
    if (lt[u]) return lt[u];
    if (lim[u][0] == lim[u][1]) {
        return str[lim[u][0]];
    }
    printf("EU %02d\n", u);
    bool ok = 1;

    while (adj[u].size() > 1 && ok) {
        int ch = adj[u].front();
        adj[u].pop_front();
        while(!leaf(ch)) {
            adj[u].splice(adj[u].begin(), adj[ch]);
            ch = adj[u].front();
            adj[u].pop_front();
        }
        char vv = solve(ch);
        debug("=== %02d === (%d)\n%c", u, (int) adj[u].size(), vv);
        printalista(u);
        debug("\n");

        if (vv == 'X') {
            ok = 0;
        } else if (vv == 'B') {
            if (adj[u].size() >= 3) {
                adj[es].push_front(adj[u].back());
                adj[u].pop_back();

                adj[es].push_front(adj[u].back());
                adj[u].pop_back();

                adj[u].push_back(es);

                lim[es++][0] = -1;
                res++;
            } else {
                ok = 0;
            }
        } else if (vv == 'C') {
            if (adj[u].size() >= 3) {
                int z = adj[u].back();
                adj[u].pop_back();
                int y = adj[u].back();
                adj[u].pop_back();

                adj[es].swap(adj[u]);

                adj[u].push_back(es);
                adj[u].push_back(y);

                adj[es].push_back(z);
                lim[es++][0] = -1;

                res++;
            } else {
                ok = 0;
            }
        } else if (vv == 'K') {
            if (adj[u].size() >= 2) {
                adj[u].pop_back();

                res++;
            } else {
                ok = 0;
            }
        } else {
            if (adj[u].size() >= 1) {
                res++;
            } else {
                ok = 0;
            }
        }
        if (!ok)
            adj[u].push_front(ch);
        printalista(u);
        debug("\n");
    }

    lt[u] = 'X';
    for (int i : adj[u]) {
        lt[u] = solve(i);
    }

    if (!ok)
        lt[u] = 'X';

    return lt[u];
}

int main () {
    int i;
    scanf(" %s", str);
    n = strlen(str);

    st.push(0);
    lim[0][1] = n;
    es = 1;
    for (i = n-1; i >= 0; i--) {
        if (str[i] == ')') {
            lim[es][1] = i;
            st.push(es++);
        } else if (str[i] == '(') {
            int v = st.top();
            st.pop();
            lim[v][0] = i;

            int u = st.top();
            adj[u].push_front(v);
        } else {
            lim[es][0] = i;
            lim[es][1] = i;
            int u = st.top();
            adj[u].push_front(es++);
        }
    }

    lim[0][0] = -1;

    solve(0);
    printf("%d\n", res);
}
