#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 4007;
const num MOD = 1000000007ll;
const num B = 263;

num pot[N];
char str[N];
int memo[N];
int res[N];

inline num mod (num a) {
    return (a+MOD)%MOD;
}

int pd(int i) {
    if (str[i] == '\0')
        return 0;

    if (memo[i] != -1)
        return memo[i];

    memo[i] = INT_MAX;

    num rolp, rols;
    rolp = rols = 0ll;
    for (int j = 0; str[i+j] != '\0'; j++) {
        rolp = (rolp + (pot[j]*str[i+j])%MOD)%MOD;
        rols = ((rols*B)%MOD + str[i+j])%MOD;
        if (rolp == rols) {
            if (memo[i] > pd(i+j+1) + 1) {
                memo[i] = pd(i+j+1)+1;
                res[i] = i+j+1;
            }
        }
    }

    return memo[i];
}

int main () {
    scanf(" %s", str);
    memset(memo, -1, sizeof memo);

    pot[0] = 1ll;
    for (int i = 0; str[i] != '\0'; i++) 
        pot[i+1] = (pot[i]*B)%MOD;

    printf("%d\n", pd(0));
    int att = 0;
    while (str[att]) {
        if (att) printf(" ");
        for (int i = att; i < res[att]; i++)
            printf("%c", str[i]);
        att = res[att];
    }
}
