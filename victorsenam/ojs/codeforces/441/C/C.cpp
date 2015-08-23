#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

int n, m, k;
int lin, col;

int main () {
    scanf("%d %d %d", &n, &m, &k);

    lin = col = 0;
    for (int i = 0; i < k-1; i++) {
        printf("2 %d %d", lin+1, (col+1) + (lin%2)*(m - 2*col - 1));
        col++;
        if (col >= m) {
            lin++;
            col = 0;
        }
        printf(" %d %d\n", lin+1, (col+1) + (lin%2)*(m - 2*col - 1));
        col++;
        if (col >= m) {
            lin++;
            col = 0;
        }
    }

    printf("%d", n*m - lin*m - col);
    while (lin < n) {
        printf(" %d %d", lin+1, (col+1) + (lin%2)*(m - 2*col - 1));
        col++;
        if (col >= m) {
            lin++;
            col = 0;
        }
    }
    printf("\n");
}
