#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef double db;

const int N = 5e4+7;
const int M = 57;

char str[N][M];
int p[N];
int n;
char aux[2*M];

bool cmp_t (int i, int j) {
    int k, n, c;
    for (k = 0; str[i][k]; k++)
        aux[k] = str[i][k];
    for (n = k; str[j][n-k]; n++)
        aux[n] = str[j][n-k];

    for (c = 0; c < n && aux[c] == aux[(c+k)%n]; c++);
    if (c == n) return 0;
    return aux[c] < aux[(c+k)%n];
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf(" %s", str[i]);
        p[i] = i;
    }

    sort(p, p+n, cmp_t);

    for (int i = 0; i < n; i++)
        printf("%s", str[p[i]]);
    printf("\n");
}
