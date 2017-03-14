#line 2 "MovingCandies.cpp"
#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int N = 21;
const int mv[4][2] = {
    {0,1},
    {0,-1},
    {1,0},
    {-1,0}
};

vector<string> t;
int n, m;

int memo[N][N][N*N];

int pd (int i, int j, int x) {
    if (x <= 0) return N*N;
    if (i >= n || i < 0 || j >= m || j < 0) return N*N;
    if (i == n-1 && j == m-1)
        return (t[i][j] == '.');
    
    int & me = memo[i][j][x];
    if (me != -1) return me;
    me = N*N;

    for (int k = 0; k < 4; k++)
        me = min(me, pd(i+mv[k][0], j+mv[k][1], x-1));
    me += (t[i][j] == '.');

    return me;
}

class MovingCandies {
    public:
    int minMoved(vector <string> inp) {
        memset(memo, -1, sizeof memo);
        t = inp;
        n = inp.size();
        m = inp[0].size();

        int r = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (t[i][j] == '#')
                    r++;

        r = pd(0,0,r);
        if (r >= N*N)
            r = -1;
        return r;
    }
};
