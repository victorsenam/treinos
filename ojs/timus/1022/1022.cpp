#include <bits/stdc++.h>

using namespace std;

const int N = 102;

int n, m;
vector<int> adj[N];
int in[N];
int a;
int sol[N];
queue<int> q;
int ss;

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        while (scanf("%d", &a) != EOF && a) {
            a--;

            adj[i].push_back(a);
            in[a]++;
        }
    }

    for (int i = 0; i < n; i++)
        if (in[i] == 0)
            q.push(i);

    ss =0 ;
    while (!q.empty()) {
        a = q.front();
        q.pop();

        sol[ss++] = a;

        for (int i = 0; i < adj[a].size(); i++) {
            in[adj[a][i]]--;
            if (in[adj[a][i]] == 0)
                q.push(adj[a][i]);
        }
    }

    for (int i = 0; i < ss; i++) {
        if (i)
            printf(" ");
        printf("%d", sol[i]+1);
    }
    printf("\n");
}
