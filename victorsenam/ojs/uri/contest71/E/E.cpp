#include <bits/stdc++.h>

using namespace std;

const int N = 1007;
const int mi[4] = {0, 0, 1, -1};
const int mj[4] = {1, -1, 0, 0};

int uf[N*N];
int wf[N*N];
int n, m;
char mat[N][N];
int cnt[N*N];

int find (int a) {
    if (uf[a] == a)
        return a;
    uf[a] = find(uf[a]);
    return uf[a];
}
void join (int a, int b) {
    a = find(a);
    b = find(b);
    if (wf[a] > wf[b])
        swap(a,b);
    uf[b] = a;
    wf[b] += wf[a];
}


bool isVal (int i, int j) {
    if (i >= n || i < 0)
        return 0;
    if (j >= m || j < 0)
        return 0;
    return (mat[i][j] == 'n');
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
        scanf("%s", mat[i]);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            wf[i*m+j] = 1;
            uf[i*m+j] = i*m + j;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] != 'n')
                continue;

            for (int k = 0; k < 4; k++) {
                if (isVal(i+mi[k], j+mj[k]))
                    join(i*m+j, (i+mi[k])*m+j+mj[k]);
            }
        }
    }


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] != 'n')
                continue;

            cnt[find(i*m+j)]++;
        }
    }

    int maxi, maxj, maxv = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] != '*')
                continue;

            set<int> s;
            for (int k = 0; k < 4; k++) {
                if (isVal(i+mi[k], j+mj[k]))
                    s.insert(find((i+mi[k])*m+j+mj[k]));
            }

            set<int>::iterator it;
            int att = 0;
            for (it = s.begin(); it != s.end(); it++)
                att += cnt[*it];

            if (att > maxv) {
                maxv = att;
                maxi = i;
                maxj = j;
            }
        }
    }

    printf("%d,%d\n", maxi+1, maxj+1);
}
