#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e3+4;

int n;
char inp[N+3];
int val[N+3][N+3];
int sz[N+3];
int cnt[N+3][N+3][13];
int c[13];
int pri[N+3][N+3][13];
int inv[N+3][N+3];
int p[N+3][N+3];

ll memo[N+3][N+3];

void printa (int i, int k) {
    for (; k < N; k++)
        printf("%d", val[i][k]);
    printf(" ");
}

void conv (int k) {
    sz[k] = strlen(inp);
    for (int i = 0; i < N-sz[k]; i++)
        val[k][i] = 0;
    for (int i = 0; i < sz[k]; i++)
        val[k][i+N-sz[k]] = inp[i] - '0';
}

ll pd (int k, int cr) {
    if (k < 0) 
        return 0;

    ll & me = memo[k][cr];
    if (me != -1)
        return me;

    me = 0;

    int l = 0;
    int r = 9;
    if (k + sz[0] == N)
        l = 1;
    if (val[0][k] != '?' - '0')
        l = r = val[0][k];
    
    for (int d = l; d <= r; d++) {
        int ncr = cnt[k][n-cr][10-d] + (cnt[k][n][10-d-1] - cnt[k][n-cr][10-d-1]);
        
        ll loc = pd(k-1, ncr);
        loc += pri[k][n-cr][d] + (pri[k][n][(d+1)%10] - pri[k][n-cr][(d+1)%10]);
        if (sz[0] + k < N)
            loc -= inv[k][n-cr]*c[0];

        me = max(me, loc);
    }
    
    //printf("%d %d -> %lld\n", k, cr, me);
    return me;
}

int main () {
    memset(memo, -1, sizeof memo);
    scanf(" %s", inp);
    conv(0);

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf(" %s", inp);
        conv(i);
        //printa(i, 0);
        //printf("\n");
    }

    for (int i = 0; i < 10; i++)
        scanf("%d", &c[i]);

    for (int i = 0; i < n; i++)
        p[N][i] = i+1;

    for (int k = N-1; k >= 0; k--) {
        for (int i = 0; i < n; i++) {
            p[k][i] = p[k+1][i];
        }
        stable_sort(p[k], p[k]+n, [k] (int i, int j) {
            return val[i][k+1] < val[j][k+1];
        });

        for (int _i = 1; _i <= n; _i++) {
            int i = p[k][_i-1];
            
            inv[k][_i] = inv[k][_i-1] + (k + sz[i] < N);

            for (int d = 0; d < 10; d++) {
                cnt[k][_i][d] = cnt[k][_i-1][d];
                pri[k][_i][d] = pri[k][_i-1][d] + c[(val[i][k]+d)%10];
            }
            cnt[k][_i][val[i][k]]++;
        }

        for (int _i = 0; _i <= n; _i++) {
            //printa(p[k][_i], k);
            for (int d = 8; d >= 0; d--)
                cnt[k][_i][d] += cnt[k][_i][d+1];
        }
    }

    printf("%lld\n", pd(N-1, 0));
}
