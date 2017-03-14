#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#define double long double

using namespace std;
typedef long long int ll;

const int N = 23;
const int H = 2e4+7;

int visi[N][N][H];
double memo[N][N][H];

double pd (int d, int y, int h) {
    if (h < 0) h = 0;
    if (d == 0) return (h == 0);

    double & me = memo[d][y][h];
    
    if (visi[d][y][h])
        return me;
    visi[d][y][h] = 1;

    me = 0;
    for (int i = 1; i <= y; i++)
        me += pd(d-1, y, h-i);
    return me;
}

int ts;
int h, n;

double ele (double a, ll e) {
    double r = 1;
    while (e) {
        if (e & 1) r *= a;
        a *= a;
        e >>= 1;
    }
    return r;
}

int main () {
    scanf("%d", &ts);

    for (int t = 1; t <= ts; t++) {
        scanf("%d %d", &h, &n);

        double r = 0.;
        
        for (int i = 0; i < n; i++) {
            int x, y, z;
            char c;
            scanf("%dd%d", &x, &y, &z);
            scanf("%c", &c);

            if (c != '+' && c != '-')
                z = 0;
            else
                scanf("%d", &z);
            
            if (c == '-')
                z = -z;

            double loc = pd(x, y, h-z);
            for (int j = 0; j < x; j++)
                loc /= (double)(y);
            r = max(r, loc);
        }

        printf("Case #%d: %.20Lf\n", t, r);
    }
}
