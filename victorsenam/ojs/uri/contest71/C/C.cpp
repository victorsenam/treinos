#include <bits/stdc++.h>

using namespace std;

const int N = 2007;
const int S = 27;

vector<int> adj[N];
int dist[N];
map<string, int> mp;
int n, g;
char stra[S], strb[S];
int a, b;
string nm[N];
queue<int> q;
set<string> s;
set<string>::iterator it;

int main () {
    scanf("%d %d", &n, &g);

    for (int i = 0; i < n; i++) {
        scanf(" %s %s", stra, strb);

        if (mp.find(stra) == mp.end()) {
            mp[stra] = mp.size()-1;
            nm[mp.size()-1] = stra;
        }
        a = mp[stra];

        if (mp.find(strb) == mp.end()) {
            mp[strb] = mp.size()-1;
            nm[mp.size()-1] = strb;
        }
        b = mp[strb];

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    a = mp["Rerisson"];
    q.push(a);

    for (int i = 0; i < mp.size(); i++)
        dist[i] = INT_MAX;

    dist[a] = 0;

    while (!q.empty()) {
        a = q.front();
        q.pop();
        for (int i = 0; i < adj[a].size(); i++) {
            if (dist[adj[a][i]] == INT_MAX) {
                dist[adj[a][i]] = dist[a] + 1;
                q.push(adj[a][i]);
            }
        }
    }

    for (int i = 0; i < mp.size(); i++) {
        if (dist[i] <= g && dist[i] > 0)
            s.insert(nm[i]);
    }

    printf("%d\n", s.size());
    for (it = s.begin(); it != s.end(); it++)
        printf("%s\n", (*it).c_str());
}
