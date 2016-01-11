#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 1000007;
const int M = 1003;
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

int uf[N], wf[N], vf[N];
char mat[M][M];
int n, m;

bool isval (int i, int j) {
    if (i < 0 || i >= n)
        return 0;
    if (j < 0 || j >= m)
        return 0;
    return (mat[i][j] == '.');
}

int find (int i) {
    if (i == uf[i])
        return i;
    return uf[i] = find(uf[i]);
}

void join (int i, int j) {
    i = find(i); j = find(j);
    if (i == j)
        return;
    if (wf[i] < wf[j])
        swap(i, j);
    wf[i] += wf[j];
    uf[j] = i;
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n*m; i++) {
        uf[i] = i;
        wf[i] = 1;
    }

    for (int i = 0; i < n; i++)
        scanf(" %s", &mat[i]);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] != '.')
                continue;
            for (int k = 0; k < 4; k++)
                if (isval(i+dx[k], j+dy[k]))
                    join(i*m+j, (i+dx[k])*m+j+dy[k]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == '.')
                continue;

            int turn = i*m + j + 1;
            int res = 1;
            for (int k = 0; k < 4; k++) {
                if (!isval(i+dx[k], j+dy[k]))
                    continue;
                int pos = find((i+dx[k])*m+j+dy[k]);
                if (vf[pos] == turn)
                    continue;
                vf[pos] = turn;
                res += wf[pos];
                res %= 10;
            }
            mat[i][j] = res + '0';
        }
    }
    for (int i = 0; i < n; i++)
        printf("%s\n", mat[i]);
}
