#include <bits/stdc++.h>

using namespace std;

const int N = 53;

int n;
int sum[2][N];
int a[2][N];
int b[N];
int mini, res;

int main () {
    scanf("%d", &n);

    for (int k = 0; k < 2; k++) {   
        for (int i = 1; i < n; i++) { 
            scanf("%d", &a[k][i]);
            sum[k][i] = sum[k][i-1] + a[k][i];
        }
    }

    mini = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", b+i);
        b[i] += sum[0][i] + sum[1][n-1] - sum[1][i];
        if (b[i] < b[mini]) {
            mini = i;
        }
    }

    res = b[mini];
    b[mini] = INT_MAX;

    mini = 0;
    for (int i = 0; i < n; i++) {
        if (b[i] < b[mini])
            mini = i;
    }

    res += b[mini];
    printf("%d\n", res);
}
