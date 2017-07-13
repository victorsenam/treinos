#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define i first
#define j second

char g[1123][1123];
bool go() {
    int i, j, n, m, a, b; char c;
    scanf("%d %d %d %d", &n, &m, &a, &b);
    for(i = 0; i < n; i++)
        scanf("%s", g[i]);
    vector<pii> st;
    for(i = 0; i < a; i++)
        for(j = 0; j < b; j++) {
            scanf(" %c", &c);
            if(c != 'x') continue;
            st.push_back(pii(i, j));
        }
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++) {
            if(g[i][j] != 'x') continue;
            int di = i - st.front().i;
            int dj = j - st.front().j;
            for(pii p : st) {
                int pi = di + p.i;
                int pj = dj + p.j;
                if(pi < 0 || pi >= n || pj < 0 || pj >= m || g[pi][pj] != 'x') 
                    return false;
                g[pi][pj] = '.';
            }
        }
    return true;
}

int main () {
    int t;
    scanf("%d", &t);
    while(t--) {
        if(go()) puts("ANO");
        else puts("NIE");
    }
}
