#include <bits/stdc++.h>

using namespace std;

const int N = 12;

int t;
char mat[N][N];

const int mi[4] = {1, 1, -1, -1};
const int mj[4] = {1, -1, 1, -1};

inline bool isVal (int i, int j) {
    if (i < 0 || i >= 10)
        return 0;
    if (j < 0 || j >= 10)
        return 0;
    return 1;
}


int bt (int i, int j) {
    int res = 0;

    for (int k = 0; k < 4; k++) {
        int ai, aj;
        ai = i + mi[k];
        aj = j + mj[k];

        if (!isVal(ai, aj) || mat[ai][aj] != 'B')
            continue;

        ai += mi[k];
        aj += mj[k];
        if (!isVal(ai, aj) || mat[ai][aj] != '#' )
            continue;
        
        mat[ai-mi[k]][aj-mj[k]] = '#';
        res = max(res, bt(ai, aj)+1);
        mat[ai-mi[k]][aj-mj[k]] = 'B';
    }

    return res;
}

int main () {
    scanf("%d", &t);

    while (t--) {
        for (int i = 0; i < 10; i++)
            scanf(" %s", mat[i]);

        int res = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (mat[i][j] != 'W')
                    continue;
                mat[i][j] = '#';
                res = max(res, bt(i, j));
                mat[i][j] = 'W';
            }
        }
        printf("%d\n", res);
    }
    }
