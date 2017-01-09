#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;

const int N = 1e3+7;
const int mv[4][2] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0}
};

char mat[N][N];
int n, m;
int dist[5][N][N];

int bfs (int k) {
    deque<pii> qu;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mat[i][j] - '1' == k) {
                qu.push_back(pii(i,j));
                dist[k][i][j] = 0;
            } else {
                dist[k][i][j] = 1e7;
            }

    while (qu.size()) {
        pii att = qu.front();
        qu.pop_front();

        for (int d = 0; d < 4; d++) {
            pii nxt = att;
            nxt.first += mv[d][0];
            nxt.second += mv[d][1];

            if (nxt.first < 0 || nxt.first >= n ||
                nxt.second < 0 || nxt.second >= m ||
                dist[k][nxt.first][nxt.second] <= dist[k][att.first][att.second] + 1 ||
                mat[nxt.first][nxt.second] == '#')
                continue;

            dist[k][nxt.first][nxt.second] = dist[k][att.first][att.second] + (mat[nxt.first][nxt.second] == '.');
            if (mat[nxt.first][nxt.second] == '.')
                qu.push_back(nxt);
            else
                qu.push_front(nxt);
        }
    }
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
        scanf(" %s", mat[i]);

    for (int k = 0; k < 3; k++)
        bfs(k);

    int res = 1e7;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int loc = 0;
            for (int k = 0; k < 3; k++)
                loc += dist[k][i][j];

            if (mat[i][j] == '.')
                loc -= 2;

            res = min(res, loc);
        }
    }

    if (res == 1e7)
        res = -1;
    printf("%d\n", res);
}
