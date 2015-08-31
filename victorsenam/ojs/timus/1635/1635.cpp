#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 4007;
const num MOD = 1000000007ll;
const num B = 263;

num lhash[N];
num rhash[N];
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

    for (int j = 0; str[j+i] != '\0'; j++) {
        if (mod(lhash[i+j+2]-lhash[i]) == mod(rhash[i+j+2] - (rhash[i]*pot[j+1])%MOD)) {
            if (pd(i+j+1) + 1 < memo[i]) { 
                memo[i] = pd(i+j+1) + 1;
                res[i] = i+j+1;
            }
        }
    }
    return memo[i];
}

int main () {
    scanf(" %s", str);

    lhash[0] = rhash[0] = 0;
    pot[0] = 1llu;
    for (int i = 0; str[i] != '\0'; i++) {
        pot[i+1] = (pot[i]*B)%MOD;
        lhash[i+1] = (lhash[i] + (pot[i]*(num)str[i])%MOD)%MOD;
        rhash[i+1] = ((rhash[i]*B)%MOD + (num)str[i])%MOD;
    }

    memset(memo, -1, sizeof memo);
    printf("%d\n", pd(0));
}
