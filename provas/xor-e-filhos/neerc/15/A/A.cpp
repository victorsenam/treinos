#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 1000007;

num c[2], s[2], n;
int q;
char ty;
num x;
bool r[2][N];

int main () {
    freopen("adjustment.in", "r", stdin);
    freopen("adjustment.out", "w", stdout);

    scanf("%I64d %d", &n, &q);

    for (int i = 0; i < q; i++) {
        scanf(" %c %I64d", &ty, &x);

        ty = (ty == 'R');

        if (r[ty][x])
            printf("0\n");
        else {
            printf("%I64d\n", (n - c[!ty])*x - s[!ty] + n*(n+1)/2);
            c[ty]++;
            s[ty] += x;
        }
        
        r[ty][x] = 1;
    }
}
