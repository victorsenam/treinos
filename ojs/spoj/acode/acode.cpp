#include <cstdio>
#include <cstring>

#define MAX 5002

long long int memo[MAX];
char s[MAX];
int n;

long long int pd (int i) {
    if (memo[i] != -1) return memo[i];
    
    memo[i] = 0;
    if (s[i-1] != '0') memo[i] += pd(i-1);
    if (i > 1) {
        if (s[i-2] > '2') return memo[i];
        if (s[i-2] == '0') return memo[i];
        if (s[i-2] == '2' && s[i-1] > '6') return memo[i];
        memo[i] += pd(i-2);
    }
    return memo[i];
}

int main () {
    while (scanf(" %s", s) != EOF) {
        n = strlen(s);
        if (n == 1 && s[0] == '0') break;
        
        for (int i = 1; i <= n; i++) memo[i] = -1;
        memo[0] = 1;
        
//        printf("%lld -> ", pd(n));
//        for (int i = 0; i <= n; i++) {
//            printf("%lld ", memo[i]);
//        }
//        printf("\n");
        printf("%lld\n", pd(n));
    }
}
