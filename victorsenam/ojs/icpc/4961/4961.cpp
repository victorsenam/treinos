#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

#define N 201
#define K 26

num memo[N+1][N+1][K];
int k, t, n;
char st[K];
char s[N];
num tass[K+1][K+1];
char mass[K+1][K+1];

int main () {
    n = 0;
    while (scanf("%d", &k) != EOF && k) {
        if (n) printf("\n");
        for (int i = 0; i < k; i++) scanf(" %c", &st[i]);
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                scanf("%lld-%c", &tass[st[i]-'a'][st[j]-'a'], &mass[st[i]-'a'][st[j]-'a']);
            }
        }

        scanf("%d", &t);
        while (t--) {
            scanf(" %s", s);

            n = 0;
            for (n = 0; !n || s[n-1] != '\0'; n++) {
                for (int i = 0; i < n; i++) {
                    for (char a = 0; a <= 'z'-'a'; a++) {
                        memo[i][n][a] = LLONG_MAX;
                    }
                }
            }
            n--;
            for (int i = 0; i < n; i++) memo[i][i+1][s[i]-'a'] = 0;

            for (int i = n-1; i >= 0; i--) {
                for (int j = i+2; j <= n; j++) {
                    for (int l = i+1; l < j; l++) {
 //                       printf("%d | %d | %d\n", i, l, j);
                        for (char a = 0; a <= 'z'-'a'; a++) {
                            if (memo[i][l][a] == LLONG_MAX) continue;
   //                         printf("%c (%d)\n", a+'a', memo[i][l][a]);
                            for (char b = 0; b <= 'z'-'a'; b++) {
                                if (memo[l][j][b] == LLONG_MAX) continue;
                                memo[i][j][mass[a][b]-'a'] = min(memo[i][j][mass[a][b]-'a'], memo[i][l][a] + memo[l][j][b] + tass[a][b]);
     //                           printf("   %c (%d) -> %d\n", b+'a', memo[l][k][b], memo[i][j][mass[a][b]-'a']);
                            }
                        }
                    }
                }
            }

            int mini = 0;
            for (int i = 0; i < k; i++)
                if (memo[0][n][st[i]-'a'] < memo[0][n][st[mini]-'a']) mini = i;

            printf("%lld-%c\n", memo[0][n][st[mini]-'a'], st[mini]);
        }
    }
}
