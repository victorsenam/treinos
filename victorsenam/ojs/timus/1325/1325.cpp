// TLE
#include <bits/stdc++.h>

using namespace std;

const int N = 500;
const int mi[8] = {0, 0, 1, -1, -1, -1, 1, 1};
const int mj[8] = {1, -1, 0, 0, -1, 1, -1, 1};

struct vert
{
    int st, bt;
    int i, j;
    bool operator < (const vert & a) const {
        if (bt != a.bt)
            return bt < a.bt;
        if (st != a.st)
            return st < a.st;
        if (i != a.i)
            return i < a.i;
        return j < a.j;
    }
};

int n, m;
vert ini;
int oi, oj;
char mat[N][N];
vert dist[N][N];
set<vert> pq;

inline bool isVal (int i, int j)
{ return (i >= 0 && i < n && j >= 0 && j < m); }

int main () 
{
    scanf("%d %d", &n, &m);
    scanf("%d %d", &ini.i, &ini.j);
    scanf("%d %d", &oi, &oj);
    ini.i--;
    ini.j--;
    oi--;
    oj--;

    for (int i = 0; i < n; i++) {
        scanf("%s", mat[i]);
        for (int j = 0; j < m; j++)
            dist[i][j].st = dist[i][j].bt = INT_MAX;
    }

    ini.bt = 0;
    ini.st = 1;
    dist[ini.i][ini.j] = ini;
    pq.clear();
    pq.insert(ini);

    while (!pq.empty()) {
        vert att = *(pq.begin());
        pq.erase(pq.begin());

        if (att.i == oi && att.j == oj)
            break;
        if (dist[att.i][att.j] < att)
            continue;
    
        for (int k = 0; k < 8; k++) {
            vert nx = att;
            nx.i += mi[k]; nx.j += mj[k];
            if (!isVal(nx.i, nx.j) || mat[nx.i][nx.j] == '0')
                continue;
            
            nx.st++;
            nx.bt += (mat[nx.i][nx.j] != mat[att.i][att.j]);

            if (dist[nx.i][nx.j] < nx)
                continue;

            pq.erase(dist[nx.i][nx.j]);
            pq.insert(nx);

            dist[nx.i][nx.j] = nx;
            pq.insert(nx);
        }
    }

    if (dist[oi][oj].st == INT_MAX)
        printf("0 0\n");
    else 
        printf("%d %d\n", dist[oi][oj].st, dist[oi][oj].bt);
}
