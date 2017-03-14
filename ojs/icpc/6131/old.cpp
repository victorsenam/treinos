// INCOMPLETO - REFAZER TALVEZ

#include <bits/stdc++.h>

typedef long long int num;

const int N = 1003;

num dp[2][N];
int n, k;
num x[N], w[N];
num ini[N];
num acc[N];
double crs[N];
num a[N], b[N];
int qi, qf;

double clccrs(int i, int j) {
    return  double(b[j]-b[i])/double(a[j]-a[i]);
}

int main () {
    while (scanf("%d %d", &n, &k) != EOF) {
        for (int i = 0; i < n; i++)
            scanf("%lld %lld", x+i, w+i);


        dp[0][0] = 0;
        for (int i = 0; i < n; i++)
            acc[i] = dp[0][i] = dp[0][i - !!i] + x[i];

        for (int q = 2; q <= k; q++) {
            bool t = !(q&1);
                
            qi = qf = 0;

            for (int i = q-1; i < n; i++) { 
                a[qf] = -i;
                b[qf] = dp[!t][i-1] + acc[i-1];
                crs[qf] = 0;
                
                // Colocar a nova reta na posição certa
                while (qi < qf) {
                    crs[qf] = clccrs(qf, qf-1);
                    if (crs[qf] <= crs[qf-1]) {
                        a[qf-1] = a[qf];
                        b[qf-1] = b[qf];
                        crs[qf-1] = crs[qf];
                        qf--;
                    } else
                        break;
                }
                qf++;

                // Ignorar as retas que terminam antes de x[i]
                while (++qi < qf && crs[qi] <= x[i]);
                qi--;

                dp[t][i] = a[qi]*x[i] + b[qi] + (i+1)*x[i] - acc[i-1];
            }
        }

        printf("%lld\n", dp[!(k&1)][n-1]);
    }
}
