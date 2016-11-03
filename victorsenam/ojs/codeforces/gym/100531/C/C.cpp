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
deque<int> adj[N];
int es;
int res;

void printdebug (int u) {
    debug("%02d ", u);
    for (int i = 0; i < n; i++)
        if (i < lim[u][0] || i > lim[u][1]) {
            debug("-");
        } else {
            debug("%c", str[i]);
        }
}

void printalista (int u) {
    for (int i : adj[u])
        debug("%d ", i);
}

char solve (int u) {
    if (lim[u][0] == lim[u][1]) {
        printdebug(u);
        debug("\n");
        return str[lim[u][0]];
    }
    bool ok = 1;
    while (adj[u].size() > 1 && ok) {
        int ch = adj[u].front();
        adj[u].pop_front();
        char vv = solve(ch);

        printdebug(u);
        debug(" ");
        printalista(u);

        if (vv == 'X') {
            ok = 0;
        } else if (vv == 'B') {
            if (adj[u].size() >= 3) {
                adj[es].push_front(adj[u].back());
                adj[u].pop_back();

                adj[es].push_front(adj[u].back());
                adj[u].pop_back();

                adj[u].push_back(es);

                es++;
                res++;
                debug("x ");
            } else {
                ok = 0;
            }
        } else if (vv == 'C') {
            if (adj[u].size() >= 3) {
                int a = adj[u].back();
                adj[u].pop_back();
                int b = adj[u].back();
                adj[u].pop_back();
                adj[u].push_back(a);
                adj[u].push_back(b);

                res++;
                debug("x ");
            } else {
                ok = 0;
            }
        } else if (vv == 'K') {
            if (adj[u].size() >= 2) {
                adj[u].pop_back();

                res++;
                debug("x ");
            } else {
                ok = 0;
            }
        } else {
            if (adj[u].size() >= 1) {
                res++;
                debug("x ");
            } else {
                ok = 0;
            }
        }

        debug("-> ");
        printalista(u);
        debug("\n");
    }

    char rr = 'X';
    for (int i : adj[u]) {
        rr = solve(i);
    }

    if (!ok)
        rr = 'X';

    printdebug(u);
    debug(": %c\n", rr);
    return rr;
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

    for (int i = 0; i < es; i++) {
        printdebug(i);
        for (int j : adj[i])
            debug(" %d", j);
        debug("\n");
    }

    debug("\n");

    solve(0);
    printf("%d\n", res);
}
