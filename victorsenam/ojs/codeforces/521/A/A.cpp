#include <bits/stdc++.h>

typedef long long int num;

const num MOD = 1000000007;

using namespace std;

int freq[4], n, eq;
num qtd, maxi;
char c;

num fexp (int eq, int n) {
    if (n == 0) 
        return 1llu;
    if (n%2)
        return (fexp(eq, n-1)*eq)%MOD;

    num res = fexp(eq, n/2);
    return (res*res)%MOD;
}

int main () {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf(" %c", &c);

        if (c == 'A')
            freq[0]++;
        else if (c == 'C')
            freq[1]++;
        else if (c == 'G')
            freq[2]++;
        else
            freq[3]++;
    }

    maxi = eq = -1;
    for (int i = 0; i < 4; i++) {
        if (freq[i] == maxi)
            eq++;
        else if (freq[i] > maxi) {
            maxi = freq[i];
            eq = 1;
        }
    }

    printf("%d\n", (int)fexp(eq, n));
}
