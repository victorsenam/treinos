#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef ull num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif


num w;
int a, b;
num n;
num modu;

bool solve (num n, num pot) {
    if (n == 0)
        return 1;

    if (n%(pot*w) == 0)
        return solve(n, pot*w);

    if (n%(pot*w) == pot && n%(pot*w) == pot*w - pot) {
        if (solve(n-pot, pot*w)) return 1;
        if (solve(n+pot, pot*w)) return 1;
        return 0;
    }
    
    if (n%(pot*w) == pot)
        return solve(n-pot, pot*w);

    if (n%(pot*w) == pot*w - pot)
        return solve(n+pot, pot*w);

    return 0;
}

int main () {
    scanf("%d %d", &a, &b);
    w = a;
    n = b;
    if (solve(n, 1)) printf("YES\n");
    else printf("NO\n");
}
