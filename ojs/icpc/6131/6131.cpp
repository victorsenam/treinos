#include <bits/stdc++.h>

using namespace std;

const int N = 1007;

typedef long long int num;

struct crs {
    double s;
    num a, b;

    num calc (num x)
    { return a*x + b; }

    double cross (crs & other)
    { return double(other.b-b)/double(a-other.a); }
};

int n, k;
num x[N], w[N];
num dp[2][N], acc[N], sum[N];
crs qu[N];
int qi, qf;

int main () {
    while (scanf("%d %d", &n, &k) != EOF && n && k) {
        for (int i = 0; i < n; i++)
            scanf("%lld %lld", x+i, w+i);

        sum[0] = 0;
        for (int i = 0; i < n; i++)
            sum[i] = sum[i-!!i] + w[i];

        acc[0] = 0;
        for (int i = 0; i < n; i++)
            acc[i] = dp[1][i] = acc[i-!!i] + sum[i-!!i]*(x[i]-x[i-!!i]);

        for (int q = 2; q <= k; q++) {
            bool t = q&1;
            qi = qf = 0;

            dp[t][q-1] = dp[!t][q-2];

            for (int i = q-1; i < n; i++) {
                int j = i-1;
                crs aux;
                aux.a = -sum[j];
                aux.b = dp[!t][j]-acc[j]+sum[j]*x[j];
                aux.s = -1000.0;

                while (qi < qf) {
                    qf--;
                    aux.s = aux.cross(qu[qf]);
                    if (aux.s > qu[qf].s) {
                        qf++;
                        break;
                    }
                }
                qu[qf++] = aux;

                dp[t][i] = qu[qi].calc(x[i]) + acc[i];               
                
                while (qi+1 < qf) {
                    num val = qu[qi+1].calc(x[i]) + acc[i];
                    if (val <= dp[t][i]) {
                        dp[t][i] = val;
                        qi++;
                    } else {
                        break;
                    }
                }
            }
        }

        printf("%lld\n", dp[k&1][n-1]);
    }
}
