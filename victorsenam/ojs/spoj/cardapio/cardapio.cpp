#include <bits/stdc++.h>

using namespace std;

#define N 4002

typedef int num;

map<string, int> mp;
stack<int> st;
vector<int> adj[N];
set<int> seen;
int a, b, t, n;
char temp[22];
bool val;
int ord[N], ret[N];
int cnt;

bool checkStrong(int v)
{
    int u;
    seen.clear();

    while (!st.empty()) 
    {
        u = st.top();
        st.pop();
        //if (u%2) printf("!");
        //printf("%d ", u/2);
        seen.insert(u);
        ord[u] = INT_MAX;
        if (seen.find(u^1) != seen.end()) return 0;
        if (u==v) break;
    }
    //printf("\n");

    return 1;
}

bool dfs(int v) 
{
    if (ord[v] != -1) return 1;
 //       printf("==");
 //       if (v%2) printf("!");
 //       printf("%d\n", v/2);
    ord[v] = ret[v] = cnt++;

    st.push(v);

    for (int i = 0; i < adj[v].size(); i++) 
    {
        if (ord[adj[v][i]] != -1)
        {
            ret[v] = min(ret[v], ord[adj[v][i]]);
        }
        else 
        {
            if(!dfs(adj[v][i])) return 0;
            ret[v] = min(ret[v], ret[adj[v][i]]);
        }
    }

    if (ret[v] < ord[v]) return 1;
    return checkStrong(v);
}

int main () 
{
    t = 0;
    while (scanf("%d", &n) != EOF) 
    {
        t++;
        mp.clear();
        while (!st.empty()) st.pop();
        cnt = 0;
        
        for (int i = 0; i < n; i++) 
        {
            adj[4*i].clear();
            adj[4*i+1].clear();
            adj[4*i+2].clear();
            adj[4*i+3].clear();
            ord[4*i] = ord[4*i+1] = ord[4*i+2] = ord[4*i+3] = -1;

            scanf(" %s", temp);
            val = (temp[0] != '!');
            a = mp.insert(make_pair(temp+!val, mp.size())).first->second;
            a = 2*a + !val;

            scanf(" %s", temp);
            val = (temp[0] != '!');
            b = mp.insert(make_pair(temp+!val, mp.size())).first->second;
            b = 2*b + !val;

            adj[a^1].push_back(b);
            adj[b^1].push_back(a);
        }
        adj[2*mp.size()].clear();
        for (int i = 0; i < mp.size(); i++) adj[2*mp.size()].push_back(i);

        printf("Instancia %d\n", t);

        if (dfs(2*mp.size())) printf("sim\n");
        else printf("nao\n");
        printf("\n");

/*
        for (map<string, int>::iterator it = mp.begin(); it != mp.end(); it++) {
            printf("%d -> ", it->second);
            int i = it->second;
            for (int j = 0; j < adj[2*i].size(); j++) {
                if (adj[2*i][j]%2) printf("!");
                printf("%d ", adj[2*i][j]/2);
            }
            printf("\n");
            printf("!%d -> ", it->second);
            for (int j = 0; j < adj[2*i+1].size(); j++) {
                if (adj[2*i+1][j]%2) printf("!");
                printf("%d ", adj[2*i+1][j]/2);
            }
            printf("\n");
        }
*/
    }
}
