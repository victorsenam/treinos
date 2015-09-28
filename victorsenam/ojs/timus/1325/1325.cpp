// TLE
#include <bits/stdc++.h>

using namespace std;

const int N = 500;
const int mi[8] = {0, 0, 1, -1, -1, -1, 1, 1};
const int mj[8] = {1, -1, 0, 0, -1, 1, -1, 1};

int n, m;
int bts[N*N];
int dis[N*N];
int ini, obj;
int a, b;
char mat[N*N];
queue<int> q;

inline bool isVal(int i, int j)
{ return (i >= 0 && i < n && j >= 0 && j < m); }

int main () {
    scanf("%d %d", &n, &m);

    scanf("%d %d", &a, &b);
    a--; b--;
    ini = a*m+b;
    scanf("%d %d", &a, &b);
    a--; b--;
    obj = a*m+b;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf(" %c", &mat[i*m+j]);
    
    for (int i = 0; i < n*m; i++)
        bts[i] = dis[i] = INT_MAX;
    bts[obj] = 0;
    dis[ini] = 1;

    q.push(obj);
    while (!q.empty()) {
        int att = q.front();
        q.pop();

        for (int k = 0; k < 8; k++) {
            int ni = att/m + mi[k];
            int nj = att%m + mj[k];
            int nx = ni*m+nj;

            if (!isVal(ni, nj) || mat[nx] == '0')
                continue;
            int aux = bts[att];
            
            if (mat[nx] != mat[att])
                aux++;
            
            if (bts[nx] > aux) {
                bts[nx] = aux;
                q.push(nx);
            }
        }
    }

    q.push(ini);
    while (!q.empty()) {
        int att = q.front();
        q.pop();

        if (att == obj)
            break;

        for (int k = 0; k < 8; k++) {
            int ni = att/m + mi[k];
            int nj = att%m + mj[k];
            int nx = ni*m+nj;

            if (!isVal(ni, nj) && mat[nx] != '0')
                continue;
            int aux = dis[att] + 1;
            if (mat[att] != mat[nx] && bts[att] <= bts[nx])
                continue;
            
            if (dis[nx] > aux) {
                dis[nx] = aux;
                q.push(nx);
            }
        }
    }
    
    if (max(dis[obj], bts[ini]) == INT_MAX)
        printf("0 0\n");
    else
        printf("%d %d\n", dis[obj], bts[ini]);
}
