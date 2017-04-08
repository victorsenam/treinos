
#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 3e2+7;

int mat[N][N], turn;
int t;
char str[N*N*N];
int x, y;

int dr[4][2] = {
    {0,1},
    {1,0},
    {0,-1},
    {-1,0}
};

void go (int c) {
    x += dr[c][0];
    y += dr[c][1];
}

int main () {
    scanf("%d", &t);
    printf("%d\n", t);

    while (t--) {
        turn++;


        scanf("%s", str);
        x = N/2; y = 0;
        mat[x][y] = turn;

        int mx[2][2] = {
            {x,x},
            {y,y}
        };
        int c = 0;
        for (int i = 0; str[i]; i++) {
            if (str[i] == 'R')
                c = (c+1)%4;
            else if (str[i] == 'L')
                c = (c+3)%4;
            else if (str[i] == 'B')
                c = (c+2)%4;
            
            go(c);
            mat[x][y] = turn;
            mx[0][0] = min(x, mx[0][0]);
            mx[0][1] = max(x, mx[0][1]);
            mx[1][0] = min(y, mx[1][0]);
            mx[1][1] = max(y, mx[1][1]);
        }

        int lm = 100;
        printf("%d %d\n", mx[0][1] - mx[0][0]+3, mx[1][1] - mx[1][0] + 2);
        for (int i = mx[0][0]-1; i <= mx[0][1] + 1; i++) {
            for (int j = mx[1][0]; j < mx[1][1] + 2; j++) {
                if (mat[i][j] == turn)
                    putchar('.');
                else
                    putchar('#');
            }
            putchar('\n');
        }
    }
}
