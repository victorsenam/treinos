#include <bits/stdc++.h>

using namespace std;

const int N = 20007;

vector<int> adji[N], adjo[N];
vector<int> cmp[N];
int isFrom[N];
int ret[N], ord[N];
int degi, dego, si, so;
int comps, cnt, n, m, a, b;
int seen[N];
int t;
stack<int> st;

void createComp(int v) {
    cmp[comps].clear();
 //   printf("comp %d has %d ", comps, v);
    while (st.top() != v) {
        cmp[comps].push_back(st.top());
        isFrom[st.top()] = comps;
 //       printf("%d ", st.top());
        st.pop();
    }
 //   printf("\n");

    cmp[comps].push_back(v);
    isFrom[v] = comps;
    st.pop();
    comps++;
}

int dfs(int v) {
    if (seen[v] == 2)
        return INT_MAX;
    if (seen[v] == 1)
        return ord[v];
    ret[v] = ord[v] = cnt++;

    seen[v] = 1;
//    printf("abre %d\n", v);

    st.push(v);

    for (int i = 0; i < adjo[v].size(); i++) {
        int res = dfs(adjo[v][i]);
 //       printf("from %d to %d -> min(%d,%d)\n", v, adjo[v][i], ret[v], res);
        ret[v] = min(ret[v], res);
    }
    
    seen[v] = 2;
//    printf("fecha %d\n", v);

    if (ret[v] == ord[v])
        createComp(v);
    return ret[v];
}

int main ( ) {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++) {
            seen[i] = 0;
            adji[i].clear();
            adjo[i].clear();
        }

        for (int i = 0; i < m; i++) {
            scanf("%d %d", &a, &b);
            a--;
            b--;
            adjo[a].push_back(b);
            adji[b].push_back(a);
        }

        cnt = 0;
        comps = 0;
        while (!st.empty()) st.pop();
        for (int i = 0; i < n; i++)
            dfs(i);

        si = so = 0;
        for (int i = 0; i < comps; i++) {
            degi = dego = 0;
            for (int j = 0; (!degi || !dego) && j < cmp[i].size(); j++) {
                for (int k = 0; !degi && k < adji[cmp[i][j]].size(); k++) {
  //                   printf("comp %d el %d entra de %d => ", i, cmp[i][j], adji[cmp[i][j]][k]);
                    if (isFrom[adji[cmp[i][j]][k]] != i)
                        degi++;
 //                   printf("%d\n", degi);
                }
                for (int k = 0; !dego && k < adjo[cmp[i][j]].size(); k++) {
 //                   printf("comp %d el %d sai para %d => ", i, cmp[i][j], adjo[cmp[i][j]][k]);
                    if (isFrom[adjo[cmp[i][j]][k]] != i)
                        dego++;
  //                  printf("%d\n", dego);
                }
            }
  //          printf("%d -> %d %d\n", i, degi, dego);
            if (degi == 0) si++;
            if (dego == 0) so++;
        }

        if (comps == 1)
            printf("0\n");
        else 
            printf("%d\n", max(si, so));
    }
}
