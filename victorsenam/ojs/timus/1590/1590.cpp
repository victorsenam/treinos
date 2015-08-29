// WA :(

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const num MOD = 1000000007llu;
const num B = 263llu;
const int N = 5007;

int s[N];

num rol;
int res;
num pot;
char str[N];
int n;
int qtd;

int main () {
    scanf(" %s", str);

    rol = 0;
    res = 0;
    n = strlen(str);
    pot = 1llu;

    for (int k = 1; k <= n; k++) {
        rol = 0;
        pot = (pot*B)%MOD;
        qtd = 0;
        
        for (int i = 0; i < k; i++)
            rol = ((rol*B)%MOD + (str[i]))%MOD;
        s[qtd++] = rol;
        
        for (int i = k; i < n; i++) {
            rol = (rol*B + ((num)str[i]))%MOD;
            rol = ((rol - (pot*str[i-k])%MOD) + MOD)%MOD;
            s[qtd++] = rol;
        }

        sort(s, s+qtd);
        res += unique(s, s+qtd) - s;
    }

    printf("%llu\n", res);
}
