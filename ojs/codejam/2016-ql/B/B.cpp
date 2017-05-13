#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 1007;

struct node {
    int i;
    bool t;
};

int visi[N][2];
int dist[N][2];
int memo[N][2];
int turn;
int n, t;
char str[N];
int qi, qf;
node qu[N];

int main () {
    scanf("%d", &t);

    for (turn = 1; turn <= t; turn++) {
        scanf(" %s", str);
        int n = strlen(str);

        qi = qf = 0;
        qu[0].i = 1;
        qu[0].t = (str[0] == '+');
        dist[qu[0].i][qu[0].t] = 0;
        visi[qu[0].i][qu[0].t] = turn;
        qf++;

        while (qi < qf && visi[n][1] != turn) {
            node u = qu[qi++];
            
            node nx = u;
            nx.t = !nx.t;

            if (visi[nx.i][nx.t] != turn) {
                dist[nx.i][nx.t] = dist[u.i][u.t] + 1;
                visi[nx.i][nx.t] = turn;
                qu[qf++] = nx;
            }

            nx = u;
            if (nx.i >= n || ((str[nx.i] == '+') != (u.t)))
                continue;
            nx.i++;

            if (visi[nx.i][nx.t] != turn) {
                dist[nx.i][nx.t] = dist[u.i][u.t];
                visi[nx.i][nx.t] = turn;
                qu[qf++] = nx;
            }
        }
        assert(visi[n][1] == turn);

        printf("Case #%d: %d\n", turn, dist[n][1]);
    }
}
