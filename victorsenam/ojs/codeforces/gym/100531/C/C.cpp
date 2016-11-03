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

int solve (int u) {
    int res = 0;
    while (adj[u].size() != 0) {
        debug("[%d,%d]\n", lim[u][0], lim[u][1]);
        int ch = adj[u].front();
        res += solve(ch);
        adj[u].pop_front();
        while (!adj[ch].empty()) {
            int v = adj[ch].back();
            adj[ch].pop_back();
            adj[u].push_front(v);
        }

        char vv = str[lim[adj[u].front()][0]];
        debug("[%d,%d]: %c\n", lim[u][0], lim[u][1], vv);
        if (vv == 'B') {
            if (adj[u].size() >= 4) {
                adj[es].push_front(adj[u].back());
                adj[u].pop_back();

                adj[es].push_front(adj[u].back());
                adj[u].pop_back();

                es++;
                res++;
                adj[u].pop_front();
            }
        } else if (vv == 'C') {
            if (adj[u].size() >= 4) {
                int a = adj[u].back();
                adj[u].pop_back();
                int b = adj[u].back();
                adj[u].pop_back();
                adj[u].push_back(a);
                adj[u].push_back(b);

                res++;
                adj[u].pop_front();
            }
        } else if (vv == 'K') {
            if (adj[u].size() >= 3) {
                adj[u].pop_back();

                res++;
                adj[u].pop_front();
            }
        } else {
            if (adj[u].size() >= 2) {
                res++;
                adj[u].pop_front();
            }
        }
    }
    return res;
}

int main () {
    int i;
    scanf(" %s", str);
    n = strlen(str);

    st.push(n);
    lim[es][1] = n;
    es++;
    for (i = n-1; i >= 0; i--) {
        if (str[i] == ')') {
            lim[es][1] = i;
            st.push(es++);
        } else if (str[i] == '(') {
            int v = st.top();
            st.pop();
            lim[v][0] = i;

            int u = st.top();
            adj[u].push_back(v);
        } else {
            lim[es][0] = i;
            lim[es][1] = i;
            int u = st.top();
            adj[u].push_back(es);
            es++;           
        }
    }

    lim[0][0] = -1;

    printf("%d\n", solve(0));
}
