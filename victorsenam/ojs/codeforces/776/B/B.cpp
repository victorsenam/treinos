#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;

int n;
int sieve[N];

int main () {
    scanf("%d", &n);

    if (n+1 <= 3) {
        printf("1\n");
        for (int i = 2; i <= n+1; i++)
            printf("1 ");
        printf("\n");
        return 0;
    }

    for (ll i = 2; i <= n+1; i++) {
        if (sieve[i]) continue;
        for (ll j = i*i; j <= n+1; j += i)
            sieve[j] = 1;
    }

    printf("%d\n", 2);
    for (int i = 2; i <= n+1; i++)
        printf("%d ", sieve[i] + 1);
    printf("\n");
}
