#include <bits/stdc++.h>

using namespace std;

#define N 5001

int multm[N], summ[N], multv[N], sumv[N];

int multc (int n) {
    int r;
    if (multm[n] != -1) return multv[n];
    
    multm[n] = multv[n] = n;

    for (int i = 2; i*i <= n; i++) {
        if (n%i) continue;

        r = multc(i)+multc(n/i)+2;
        if (r < multv[n]) {
            multv[n] = r;
            multm[n] = i;
        }
    }

    return multv[n];
}

int sumc (int n) {
    int r;
    if (summ[n] != -1) return sumv[n];
    
    sumv[n] = multc(n);
    summ[n] = 0;

    for (int i = 1; i <= n/2; i++) {
        r = sumc(i)+sumc(n-i)+2;
        if (r < sumv[n]) {
            sumv[n] = r;
            summ[n] = i;
        }
    }

    return sumv[n];
}

void multp (int n) {
    multc(n);
    
    if (multm[n] == n) {
        for (int i = 0; i < n; i++) printf("|");
    } else {
        multp(multm[n]);
        printf("x");
        multp(n/multm[n]);
    }
}

void sump (int n) {
    sumc(n);

    if (summ[n] == 0) multp(n);
    else {
        sump(summ[n]);
        printf("+");
        sump(n - summ[n]);
    }
}

int main () {
    int k;
    for (int i = 0; i <= N; i++)
        multm[i] = summ[i] = -1;

    while (scanf("%d", &k) != EOF) {
        printf("%d toothpicks: ", sumc(k));
        sump(k);
        printf("=%d\n", k);
    }
}
