#include <bits/stdc++.h>

using namespace std;

#define N 30

char lf[N][N];
char rf[N][N];
int dl, dr;
char temp[2*N+2];
int wl, wr, t;
int ini, fim;

int getVal (char a) {
    int val = 0;
    a = a - 'A' + 65;
    while (a != 0) {
        val += a%2 + 1;
        a /= 2;
    }
    return val;
}

int main () {
    scanf("%d", &t);
    for (int c = 1; c <= t; c++) {
        printf("Case %d:\n", c);
        wl = wr = 0;
        for (int i = 0; i < 7; i++) {
            scanf(" %s", temp);
            for (int j = 0; j < 8; j++) {
                lf[i][j] = temp[j];
                rf[i][j] = temp[j+10];

                if (lf[i][j] == '_')
                    ini = i - 5;
                if (lf[i][j] >= 'A' && lf[i][j] <= 'Z')
                    wl += getVal(lf[i][j]);
                if (rf[i][j] >= 'A' && rf[i][j] <= 'Z')
                    wr += getVal(rf[i][j]);
            }
        }
        scanf(" %s", temp);

        if (wl > wr)
            fim = 1;
        else if (wl == wr)
            fim = 0;
        else
            fim = -1;
            
 //       printf("%d %d\n", ini, fim);

        if (ini == fim) {
            printf("The figure is correct.\n");
        } else {
            if (ini == -1) {
                if (fim == 0) {
                    dl = 1;
                    dr = 6;
                } else {
                    dl = 2;
                    dr = 5;
                }
            } else if (ini == 0) {
                if (fim == -1) {
                    dl = 6;
                    dr = 1;
                } else {
                    dl = 1;
                    dr = 6;
                }
            } else {
                if (fim == -1) {
                    dl = 5;
                    dr = 2;
                } else {
                    dl = 6;
                    dr = 1;
                }
            }
 //           printf("%d %d\n", dl, dr);

            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 8; j++)
                    printf("%c", lf[(i+7-dl)%7][j]);
                printf("||");
                for (int j = 0; j < 8; j++)
                    printf("%c", rf[(i+7-dr)%7][j]);
                printf("\n");
            }
        }
    }
}
