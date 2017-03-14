#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 1007;
const int K = 100007;
const num MOD = 1000000007ll;

int r;
int n, k;
char str[N], obj[N];

num mod (num a)
{ return a%MOD; }

void checkmatch () {
    for (int i = 0; i < n; i++) {
        int j = 0;
        for (j = 0; j < n; j++) {
            if (str[j] != obj[(i+j)%n])
                break;
        }
        if (j == n)
            return;
    }
    printf("0\n");
    exit(0);
}

int cntrep () {
    for (int i = 1; i < n; i++) {
        if (n%i)
            continue;
        int j = 0;
        for (j = 0; j < n-i; j++)
            if (str[j] != str[i+j])
                break;
        if (j == n-i)
            return n/i;
    }
    return 1;
}

num memo[K][2];
bool visi[K][2];

num dp (int k, bool pl) {
    if (k == 0)
        return pl;

    if (visi[k][pl])
        return memo[k][pl];
    visi[k][pl] = 1;

    memo[k][pl] = mod((r-pl)*dp(k-1, 1));
    memo[k][pl] = mod(memo[k][pl] + mod(n-r-!pl)*dp(k-1, 0));

    return memo[k][pl];
}

int main () {
    scanf(" %s", str); 
    scanf(" %s", obj);
    scanf("%d", &k);
    n = strlen(str);

    bool eq = 1;
    for (int i = 0; eq && i < n; i++)
        eq = (eq && (str[i] == obj[i]));

    if (!eq)
        checkmatch();
    
    r = cntrep();

    printf("%d\n", (int) dp(k, eq));
}

