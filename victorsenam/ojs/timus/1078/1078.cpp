#include <bits/stdc++.h>

using namespace std;

const int N = 507;

vector<int> adj[N];
stack<int> st;
int lf[N], rg[N];
int a, b, n;
int hei[N];

int dfs (int v) {
    if (hei[v] != -1)
        return hei[v];

    hei[v] = 1;
    for (int i = 0; i < adj[v].size(); i++)
        hei[v] = max(hei[v], dfs(adj[v][i])+1);
    
    return hei[v];
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d %d", lf+i, rg+i);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (lf[i] > lf[j] && rg[i] < rg[j])
                adj[j].push_back(i);
        }
    }

    int maxi = 0;
    for (int i = 0; i < n; i++)
        hei[i] = -1;

    for (int i = 0; i < n; i++) {
        dfs(i);
        if (hei[maxi] < hei[i])
            maxi = i;
    }
    
    printf("%d\n", hei[maxi]);

    while (hei[maxi] != 1) {
        st.push(maxi+1);
        for (int i = 0; i < adj[maxi].size(); i++) {
            if (hei[adj[maxi][i]] == hei[maxi] - 1) {
                maxi = adj[maxi][i];
                break;
            }
        }
    }
    st.push(maxi+1);

    while (st.size() > 1) {
        printf("%d ", st.top());
        st.pop();
    }

    printf("%d\n", st.top());
}
