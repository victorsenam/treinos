#include <bits/stdc++.h>

using namespace std;

int oi, oj, mx[4] = {1, -1, -1, 1}, my[4] = {-1, 1, -1, 1};
char mat[10][10];
queue<pair<int,int> > q;

bool checkpos (int i, int j) {
    if (i >= 10 || i < 0)
        return 0;
    if (j >= 10 || j < 0)
        return 0;
    return 1;
}

int bt(int i, int j) {
    int res = 0;
    for (int k = 0; k < 4; k++) {
        if (!checkpos(i+mx[k], j+my[k]))
            continue;
        if (!checkpos(i+2*mx[k], j+2*my[k]))
            continue;
        if (mat[i+mx[k]][j+my[k]] != 'B')
            continue;
        if (mat[i+2*mx[k]][j+2*my[k]] != '#')
            continue;
        mat[i+mx[k]][j+my[k]] = '#';
        //printf("try %d %d\n", i+2*mx[k], j+2*my[k]);
        res = max(res, 1+bt(i+2*mx[k], j+2*my[k]));
        //printf("leave %d %d\n", i+2*mx[k], j+2*my[k]);
        mat[i+mx[k]][j+my[k]] = 'B';
    }
    return res;
}

int main () {
    int t;
    scanf("%d", &t);
    while (t--) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                scanf(" %c", &mat[i][j]);
                if (mat[i][j] == 'W')
                    q.push(make_pair(i, j));
            }
        }
        int res = 0;
        while (!q.empty()) {
            oi = q.front().first;
            oj = q.front().second;
            q.pop();
            mat[oi][oj] = '#';
            res = max(res, bt(oi, oj));
            mat[oi][oj] = 'W';
        }
        printf("%d\n", res);
    }
}
