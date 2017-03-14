#include <bits/stdc++.h>

using namespace std;

const int N = 1007;

int lin[N];
int col[N];
int cm, lm;
int n, m, t, a;

int tryFor (int * v, int n) {
    int sum = 0;
    int mini = INT_MAX;
    int res = 0;
    int carry = 0;
    for (int i = 0; i < n; i++) {
        //printf("%d ", v[i]);
        sum += v[i];
    }
    //printf("\n");

    //printf("==%d/%d\n", sum, n);
    if (sum%n)
        return -1;


    for (int k = 0; k < n; k++) {
        carry = 0;
        res = 0;
        for (int i = 0; i < n; i++) {
            carry += v[(i+k)%n]-(sum/n);
            res += max(carry, -carry);
        }
        mini = min(mini, res);
    }

    return mini;
}

int main () {
    scanf("%d", &t);
    for (int c = 1; c <= t; c++) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++)
            lin[i] = 0;
        for (int i = 0; i < m; i++)
            col[i] = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf(" %c", &a);
                a -= '0';
                lin[i] += a;
                col[j] += a;
            }
        }

        lm = tryFor(lin, n);
        cm = tryFor(col, m);

        printf("Case %d: ", c);
        if (cm > -1 && lm > -1)
            printf("both %d\n", cm+lm);
        else if (cm > -1)
            printf("column %d\n", cm);
        else if (lm > -1)
            printf("row %d\n", lm);
        else
            printf("none\n");
    }
}
