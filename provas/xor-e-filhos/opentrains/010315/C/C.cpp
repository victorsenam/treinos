#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 1007;

int n, k;
int a[2][N];
int p[N];
bool b;

int cmp_t (int i, int j) {
    if (a[!b][i] == a[!b][j])
        return i < j;
    return a[!b][i] < a[!b][j];
}

int main () {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        p[i] = i;
        a[0][i] = a[1][i] = -1;
    }

    int i;
    for (i = n-1; i+1; i--) {
        b = (i&1);
        sort(p+i+1, p+n, cmp_t);

        int m = k;
        int c = max((n-i+1)/2-1, 0);

        for (int j = 0; j < i; j++)
            a[b][j] = -1;

        for (int j = i+1; j < n; j++) {
            if (c > 0) {
                a[b][p[j]] = a[!b][p[j]] + 1;
                c--;
            } else {
                a[b][p[j]] = 0;
            }
            m -= a[b][p[j]];
        }
        a[b][i] = m;


        if (m < 0)
            for (int j = 0; j < n; j++)
                a[b][j] = a[!b][j];
    }
    for (int j = 0; j < n; j++)
        printf("%d ", a[0][j]);
    printf("\n");
}
