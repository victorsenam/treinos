#include <bits/stdc++.h>

using namespace std;

const int N = 3007;
const int S = 27;

int n, m;
int dist[N];
vector<int> adj[N];
map<string, int> mp;
map<string, int>::iterator it;
char str[3][S];
int id[3];
queue<int> q;

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) { 
        scanf(" %s %s %s", str[0], str[1], str[2]);

        for (int j = 0; j < 3; j++) {
            if (mp.find(str[j]) == mp.end()) {
                id[j] = mp.size();
                mp[str[j]] = id[j];
            }
            id[j] = mp[str[j]];
        }

        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                adj[id[j]].push_back(id[k]);
            }
        }
    }
    
    for (int i = 0; i < mp.size(); i++)
        dist[i] = -1;

    if(mp.find("Isenbaev") != mp.end()) {
        dist[mp["Isenbaev"]] = 0;
        q.push(mp["Isenbaev"]);
    }
    
    while (!q.empty()) {
        int aux = q.front();
        q.pop();

        if (dist[aux] == -1)
            continue;

        for (int i = 0; i < adj[aux].size(); i++) {
            if (dist[adj[aux][i]] != -1 && dist[adj[aux][i]] <= dist[aux])
                continue;
            dist[adj[aux][i]] = dist[aux] + 1;
            q.push(adj[aux][i]);
        }
    }

    for (it = mp.begin(); it != mp.end(); ++it) {
        printf("%s ", it->first.c_str());
        if (dist[it->second] == -1)
            printf("undefined\n");
        else
            printf("%d\n", (int) dist[it->second]);
    }
}
