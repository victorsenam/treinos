#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int K = 103;
const int N = 7;
const int M = 21;
const int H = 60*24;

char curr[N][M];
char inp[K][N][M];

const bool let[10][7] = {
    {1, 1, 1, 0, 1, 1, 1},
    {0, 0, 1, 0, 0, 1, 0},
    {1, 0, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 0, 1, 1},
    {0, 1, 1, 1, 0, 1, 0},
    {1, 1, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1}
};

const int ps[7][2][2] = {
    {{0, 1}, {0, 2}},
    {{1, 0}, {2, 0}},
    {{1, 3}, {2, 3}},
    {{3, 1}, {3, 2}},
    {{4, 0}, {5, 0}},
    {{4, 3}, {5, 3}},
    {{6, 1}, {6, 2}}
};

int n;
bitset<N*M> vis[2], res[2];
bool ss[N][M];

void reset () {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            curr[i][j] = '.';
    curr[2][10] = curr[4][10] = 'X';
    ss[2][10] = ss[4][10] = 1;
}

void printa () {
    return;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            printf("%c", curr[i][j]);
        printf("\n");
    }
    printf("\n");
}

void put (int p, int x) {
    if (p == 0 && x == 0)
        return;

    p = 5*p + 2*(p/2);

    for (int k = 0; k < 7; k++)
        if (let[x][k])
            for (int z = 0; z < 2; z++) {
                curr[ps[k][z][0]][ps[k][z][1]+p] = 'X';
                ss[ps[k][z][0]][ps[k][z][1]+p] = 1;
            }
}

void put (int m) {
    reset();
    put(3, m%10);
    m /= 10;
    put(2, m%6);
    m /= 6;
    put(1, m%10);
    m /= 10;
    put(0, m);
}

void imp (bitset<N*M> v, string s) {
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < M; j++) {
            if (v.test(i*M + j))
                putchar('X');
            else
                putchar('.');
        }
        printf(" || %s\n", s.c_str());
    }
    putchar('\n');
}

bool find (int h) {
    vis[0] = vis[1] = 0;
    res[0] = res[1] = 0;
    for (int k = 0; k < n; k++) {
        put((h+k)%H);
        printa();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                vis[inp[k][i][j] == 'X'][i*M+j] = 1;
                if (curr[i][j] == '.' && inp[k][i][j] == 'X')
                    res[1][i*M+j] = 1;                    
                if (curr[i][j] == 'X' && inp[k][i][j] == '.')
                    res[0][i*M+j] = 1;
            }
        }
    }
/*
    imp(vis[0], "off");
    imp(vis[1], "on");
    imp(res[0], "broke off");
    imp(res[1], "broke on");

    imp(vis[1]&res[0], "broke off shows on");
    imp(vis[0]&res[1], "broke on shows off");
    */

    if ((vis[0] & res[1]).any()) return 0;
    if ((vis[1] & res[0]).any()) return 0;

    return 1;
}

int main () {
    for (int p = 0; p < 4; p++)
        for (int x = 0; x < 9; x++)
            put(p, x);
    scanf("%d", &n);


    for (int i = 0; i < n; i++)
        for (int j = 0; j < N; j++)
            scanf(" %s", inp[i][j]);

    int cnt = 0;
    char ans[N][M];

    for (int m = 0; m < H; m++) {
        if (find(m)) {
            for (int i = 0; i < N*M; i++) {
                char c;
                if (vis[0][i] && vis[1][i])
                    c = 'W';
                else if (res[0][i])
                    c = '0';
                else if (res[1][i])
                    c = '1';
                else
                    c = '?';

                if (cnt == 0) {
                    ans[i/M][i%M] = c;
                } else {
                    if (ans[i/M][i%M] != c)
                        ans[i/M][i%M] = '?';
                }
            }

            cnt++;
        }
    }
    if (cnt == 0)
        printf("impossible\n");
    else {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++)
                if (ss[i][j])
                    printf("%c", ans[i][j]);
                else
                    printf(".");
            printf("\n");
        }
    }
}
