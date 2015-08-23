#include <bits/stdc++.h>

#define N 100
#define X 50
#define V 100

bool memo[N][X+X+N*V+1];
int n, v[N], x, y, s;

bool tenta(int i, int f) {
    if (f == 0) return 1;
    if (f < 0 || i >= n || v[i] > f) {
 //       printf("(%d,%d) FI\n", i, f);
        return 0;
    }

    if (memo[i][f]) {
 //       printf("(%d,%d) FM %d\n", i, f, memo[i].count(f));
        return 0;
    }

    if (tenta(i+1, f-v[i])) {
 //       printf("(%d,%d) E1\n", i, f);
        return 1;
    }
    if (tenta(i+1, f)) {
 //       printf("(%d,%d) E2\n", i, f);
        return 1;
    }
    
 //   printf("(%d,%d) FF\n", i, f);
    memo[i][f] = 1;
    return 0;
}

inline int max (int a, int b) {
    if (a>b) return a;
    return b;
}

int main () {
    int t = 0, val;
    while (scanf("%d %d %d", &x, &y, &n) != EOF && x && y && n) {
        printf("Teste %d\n", ++t);
        s = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &v[i]);
            s += v[i];
        }

        if ((s+x+y)%2) printf("N\n");
        else {
            std::sort(v, v+n);
            
            val = (s+x+y)/2-max(x,y);

            for (int i = 0; i <= val; i++) {
                for (int j = 0; j < n; j++) {
                    memo[j][i] = 0;
                }
            }

            if (tenta(0, val)) printf("S\n");
            else printf("N\n");
        }

        printf("\n");
    }
}
