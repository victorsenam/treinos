#include <bits/stdc++.h>

using namespace std;

typedef unsigned int num;

bool state[4][4];
bool change[9];
char c;

const int mi[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
const int mj[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

inline bool isVal(int i, int j) {
    if (i < 0 || i >= 4)
        return 0;
    if (j < 0 || j >= 4)
        return 0;
    return 1;
}

bool teste (num mask) {
    bool att[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            att[i][j] = state[i][j];

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (mask&(1u<<(i*4+j)))
                for (int k = 0; k < 9; k++)
                    if (change[k] && isVal(i+mi[k], j+mj[k]))
                        att[i+mi[k]][j+mj[k]] = !att[i+mi[k]][j+mj[k]];

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (att[i][j] != att[0][0])
                return 0;


    return 1;
}

int main () {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            scanf(" %c", &c);
            state[i][j] = (c=='W');
        }
    }

    for (int i = 0; i < 9; i++) {
        scanf(" %c", &c);
        change[i] = (c=='1');
    }

    int res = INT_MAX;
    for (num mask = 0u; mask < (1u<<16); mask++) {
        if (teste(mask))
            res = min(res, __builtin_popcount(mask));
    }

    if (res == INT_MAX)
        printf("Impossible\n");
    else
        printf("%d\n", res);
}
