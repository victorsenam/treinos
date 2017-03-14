#include <bits/stdc++.h>

using namespace std;

typedef long long int num;
const int N = 2003;

double memo[N][N][2][2];
bool visi[N][N][2][2];
double p;
int lf[N], rf[N];
num x[N];
int n;
num h;

num calc(int i, bool side, bool occ) {
    if (side == 1) {
        if (i == n-1)
            return h;
        else 
            return min(h, max(0ll, x[i+1]-x[i]-(occ?h:0)));
    } else {
        if (i == 0)
            return h;
        else 
            return min(h, max(0ll, x[i]-x[i-1]-(occ?h:0)));
    }
}

double dp (int i, int j, bool l, bool r) {
    if (i > j)
        return 0.0;

    double & me = memo[i][j][l][r];
    if (visi[i][j][l][r])
        return me;
    visi[i][j][l][r] = 1;

    me = 0.0;
        
    if (i == j) {
        me += p*calc(i, 0, l);
        me += (1.0-p)*calc(i, 1, r);
    } else {
        int aux;
        // direita pra direita
        me += 0.5*(1.0-p)*(dp(i, j-1, l, 0) + calc(j, 1, r));
        // esquerda pra esquerda
        me += 0.5*p*(dp(i+1, j, 0, r) + calc(i, 0, l));

        // direita pra esquerda
        aux = lf[j];
        
        double loc = 0;
        if (aux < i) {
            loc = 0.5*p*(x[j] - x[i] + calc(i, 0, l));
        } else {
            loc = 0.5*p*(x[j] - x[aux+1] + h + dp(i, aux, l, 1));
        }
        me += loc;
        
        // esquerda pra direita
        aux = rf[i];
        if (aux > j) {
            me += 0.5*(1.0-p)*(x[j]-x[i] + calc(j, 1, r));
        } else {
            me += 0.5*(1.0-p)*(x[aux-1] - x[i] + h + dp(aux, j, 1, r));
        }
    }

    return me;
}

int main () {
    scanf("%d %I64d %lf", &n, &h, &p);

    for (int i = 0; i < n; i++)
        scanf("%I64d", x+i);

    sort(x, x+n);

    int ls = 0;
    for (int i = 0; i < n; i++) {
        if (ls > i)
            rf[i] = ls;
        else {
            do {
                ls++;
            } while (ls < n && x[ls] - x[ls-1] < h);
            rf[i] = ls;
        }
    }

    ls = n-1;
    for (int i = n-1; i >= 0; i--) {
        if (ls < i)
            lf[i] = ls;
        else {
            do {
                ls--;
            } while (ls >= 0 && x[ls+1] - x[ls] < h);
            lf[i] = ls;
        }
    }

    printf("%.20f\n", dp(0, n-1, 0, 0));
}
