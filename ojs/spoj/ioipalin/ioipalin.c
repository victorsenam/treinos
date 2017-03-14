#include <stdio.h>

#define MAX 5001

inline int max (int a, int b) {
    if (a>=b) return a;
    return b;
}

int n, i, j;
char s[MAX];
int memo[2][MAX];

int main () {
    scanf("%d %s", &n, s);

    for (i = 0; i <= n; i++) memo[0][i] = 0;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (s[i-1] == s[n-j]) memo[i%2][j] = memo[(i+1)%2][j-1] + 1;
            else memo[i%2][j] = max(memo[(i+1)%2][j], memo[i%2][j-1]);
        }
    }

    printf("%d\n", n-memo[n%2][n]);
}
