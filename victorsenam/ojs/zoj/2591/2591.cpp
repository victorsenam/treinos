#include <bits/stdc++.h>

using namespace std;

const int N = 2000;
const int Y = 2004-1870;
const int MY = 1870;
const int S = 100;
const int T = 5;
const int M = (2<<T);

struct state {
    int y, r, t, m;
};

char name[N+7][S+7];
int ts, n, a, b;
vector<int> movies[Y+7][T+2];
int memo[Y+7][T+2][T+2][M+7];
state remo[Y+7][T+2][T+2][M+7];

int pd (int y, int r, int t, int m) {
    if (y > Y) 
        return 0;

    int & me = memo[y][r][t][m];
    state & re = remo[y][r][t][m];

    if (me != -1)
        return me;

    me = pd(y+1, r, t, 1<<r);
    re.y = y+1;
    re.r = r;
    re.t = t;
    re.m = (1<<r);

    for (int i = 0; i < 5 && t > 0; i++) {
        if (i == r)
            continue;
        if ((m&(1<<i)))
            continue;
        int loc = pd(y, i, t-1, (m|(1<<i)));
        if (loc > me) {
            me = loc;
            re.y = y;
            re.r = i;
            re.t = t-1;
            re.m = (m|(1<<i));
        }
    }

    me += movies[y][r].size();
    
    return me;
}

int main () {
    scanf("%d", &ts);
    while (ts--) {
        scanf("%d", &n);
        for (int i = 0; i <= Y; i++) {
            for (int j = 0; j <= T; j++) {
                for (int k = 0; k <= T; k++) {
                    for (int l = 0; l < (1<<T); l++) {
                        memo[i][j][k][l] = -1;
                        movies[i][j].clear();
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            scanf(" \"%[a-zA-Z ]\" %d %d", name+i, &a, &b);
            movies[a-MY][b-1].push_back(i);
        }

/*
        for (int i = 0; i <= Y; i++) {
            for (int j = 0; j < T; j++) {
                if (movies[i][j].size()) {
                    printf("%d %d -> ", i+MY, j+1);
                    for (int k = 0; k < movies[i][j].size(); k++)
                        printf("%s ", name[movies[i][j][k]]);
                    printf("\n");
                }
            }
        }
*/

        int maxi = -1;
        int mres = 0;
        for (int i = 0; i < T; i++) {
            int loc = pd(0, i, T, (1<<i));
            if (loc > mres) {
                mres = loc;
                maxi = i;
            }
        }

        printf("%d\n", mres);

        state aux;
        aux.y = 0;
        aux.r = maxi;
        aux.t = T;
        aux.m = (1<<maxi);
        while (aux.y <= Y) {
            for (int i = 0; i < movies[aux.y][aux.r].size(); i++)
                printf("\"%s\"\n", name[movies[aux.y][aux.r][i]]);
            aux = remo[aux.y][aux.r][aux.t][aux.m];       
        }
        if (ts) printf("\n");
    }
}
