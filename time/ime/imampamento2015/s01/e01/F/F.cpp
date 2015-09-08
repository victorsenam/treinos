#include <bits/stdc++.h>

#define N 102

int n, k;
int ma[N][N], mb[N][N];
int t;
int diff, dd;
int invl, invc;

int main () {
    scanf("%d", &t);

    for (int c = 1; c <= t; c++) {
        scanf("%d %d", &n, &k);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &ma[i][j]);
        
        dd = 0;
        diff = 0;
        invl = invc = -1;
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++) {
                scanf("%d", &mb[i][j]);
                if (ma[i][j] != mb[i][j]) {
                    diff++;
                    if (i == j)
                        dd++;
                    else {
                        invl = i;
                        invc = j;
                    }
                }
            }

        printf("Case %d: ", c);
        if (diff == 0) {
            printf("0\n");
            continue;
        }

        bool eq = 1;
        for (int i = 0; i < n && eq; i++) 
            for (int j = 0; j < n && eq; j++)
                if (mb[i][j] != mb[j][i])
                    eq = 0;
        
        if (eq) {
            printf("-1\n");
            continue;
        }

        if (diff-dd != 2) {
            printf("%d\n", diff);
            continue;
        }

        ma[invl][invc] = mb[invl][invc];

        eq = 1;
        for (int i = 0; i < n && eq; i++) 
            for (int j = 0; j < n && eq; j++)
                if (ma[i][j] != ma[j][i])
                    eq = 0;
        
        if (!eq) {
            printf("%d\n", diff);
        } else {
            if (k > 2)
                printf("%d\n", diff+1);
            else if (n==2) 
                printf("-1\n");
            else 
                printf("%d\n", diff+2);
        }
    }
}
