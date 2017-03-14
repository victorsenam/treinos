#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define V 100
#define E 200

using namespace std;

typedef int num;

vector<int> adj[2*V+2];
int org[2*V+2];
int turn[2*V+2];
num cap[2*V+2][2*V+2];
int v, e;
int a;
num obj, c, b;
queue<int> q;

int main () {
    scanf("%d %d", &v, &e);

    for (int i = 0; i < 2*v+2; i++)
        for (int j = 0; j < 2*v+2; j++)
            cap[i][j] = 0;

    b = 0;
    for (int i = 0; i < v; i++) {
        scanf("%d", &c);
        adj[i].push_back(2*v);
        adj[2*v].push_back(i);
        cap[2*v][i] = c;

        adj[i].push_back(v+i);
        adj[v+i].push_back(i);
        cap[i][v+i] = INT_MAX;
        b += c;

        turn[i] = 0;
    }

    obj = 0;
    for (int i = 0; i < v; i++) {
        scanf("%d", &c);
        adj[v+i].push_back(2*v+1);
        adj[2*v+1].push_back(v+i);
        cap[v+i][2*v+1] = c;
        obj += c;

        turn[v+i] = 0;
    }

    if (b != obj) {
        printf("NO\n");
        return 0;
    }

    for (int i = 0; i < e; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        adj[a].push_back(v+b);
        adj[v+a].push_back(b);
        cap[a][v+b] = INT_MAX;

        adj[b].push_back(v+a);
        adj[b+v].push_back(a);
        cap[b][v+a] = INT_MAX;
    }

    turn[2*v] = turn[2*v+1] = 0;

    while (42) {
        turn[2*v]++;
        q.push(2*v);

        while (!q.empty() && turn[2*v+1] != turn[2*v]) {
            a = q.front();
            q.pop();

            debug("%d", a);

            for (int i = 0; i < adj[a].size(); i++) {
                if (cap[a][adj[a][i]] == 0) continue;
                if (turn[adj[a][i]] == turn[a]) continue;

                turn[adj[a][i]] = turn[a];
                org[adj[a][i]] = a;

                q.push(adj[a][i]);
            }
        }
        while (!q.empty()) q.pop();

        debug("END BFS");

        if (turn[2*v+1] != turn[2*v]) break;

        debug("FOUND PATH");

        a = 2*v+1;
        c = INT_MAX;
        while (a != 2*v) {
            c = min(c, cap[org[a]][a]);
            a = org[a];
        }

        a = 2*v+1;
        while (a != 2*v) {
            cap[org[a]][a] -= c;
            cap[a][org[a]] += c;
            a = org[a];
        }
    }

    b = 0;
    for (int i = 0; i < v; i++)
        b += cap[2*v+1][v+i];

    if (b < obj)
        printf("NO\n");
    else {
        printf("YES\n");
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                printf("%d ", cap[v+j][i]);
            }
            printf("\n");
        }
    }
}
