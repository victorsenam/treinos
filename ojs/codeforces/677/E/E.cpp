#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 1003;
const int K = 8;
const ll MOD = 1000000007;

const int mv[8][2] = {
    {-1, 0},
    {-1, -1},
    {0, -1},
    {1, -1},
    {1, 0},
    {1, 1},
    {0, 1},
    {-1, 1}
};

int acc[N][N][8][2];
int ls[N][N][8];
int n;
char mat[N][N];
int att[2];
int res[2];

bool isVal (int i, int j) {
    return !(i < 0 || j < 0 || i >= n || j >= n);
}

int pd_ls (int i, int j, int k) {
    if (!isVal(i, j)) return 0;
    if (mat[i][j] == '0') return 0;
    if (ls[i][j][k] != -1) return ls[i][j][k];
    return ls[i][j][k] = pd_ls(i+mv[k][0], j+mv[k][1], k) + 1;
}

int pd_acc (int i, int j, int k, int v) {
    if (!isVal(i, j)) return 0;
    if (acc[i][j][k][v] != -1) return acc[i][j][k][v];
    acc[i][j][k][v] = pd_acc(i+mv[k][0], j+mv[k][1], k, v);
    if (mat[i][j] == '2'+v) acc[i][j][k][v]++;
    return acc[i][j][k][v];
}

void swapans () {
    swap(att[0], res[0]);
    swap(res[1], att[1]);
}

void upd () {
    DEBUG("2^%d 3^%d ou 2^%d 3^%d\n", att[0], att[1], res[0], res[1]);
    if (att[0] > res[0]) swapans();

    if (res[1] >= att[1]) return;

    ll n = att[1] - res[1];
    ll m = res[0] - att[0];

    double prop = m;
    prop /= double(n);
    if (prop <= 1.584962500721156181453738943947816508759814407692481060455)
        swapans();
}

int main () {
    memset(acc, -1, sizeof acc);
    memset(ls, -1, sizeof ls);
    scanf("%d", &n);
    bool ok = 0;
    for (int i = 0 ;i < n; i++) {
        scanf(" %s", mat[i]);
        for (int j = 0; !ok && j < n; j++)
            ok = (mat[i][j] != '0');
    }

    if (!ok) {
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < 2; i++)
        res[i] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int d = 0; d < 2; d++) {
                int mini = n;
                for (int k = d; k < 8; k+=2)
                    mini = min(mini, pd_ls(i, j, k));

                if (mini == 0) continue;

                for (int r = 0; r < 2; r++) {
                    att[r] = 0;
                    for (int k = d; k < 8; k+=2)
                        att[r] += pd_acc(i, j, k, r) - pd_acc(i+mv[k][0]*mini, j+mv[k][1]*mini, k, r);
                }
                if (mat[i][j] == '2') att[0] -= 3;
                if (mat[i][j] == '3') att[1] -= 3;

                upd();
                DEBUG("2^%d 3^%d\n", res[0], res[1]);
            }
        }
    }

    ll ans = 1;
    for (int i = 0; i < res[0]; i++)
        ans = (ans*2ll)%MOD;
    for (int i = 0; i < res[1]; i++)
        ans = (ans*3ll)%MOD;
    printf("%lld\n", ans);
}
