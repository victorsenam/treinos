#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e3+7;
const ll MOD = 1e9+7;

int n;
ll a[3][N][N];
ll v[3][N];

inline ll mod (ll x) {
    return x%MOD;
}

int main () {
    scanf("%d", &n);

    for (int k = 0; k < 3; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%lld", &a[k][i][j]);

    srand(time(NULL)); rand(); rand();
    for (int i = 0; i < n; i++)
        v[0][i] = mod(rand());

    for (int i = 0; i < n; i++) {
        v[1][i] = 0;
        for (int j = 0; j < n; j++)
            v[1][i] = mod(v[1][i] + mod(v[0][j]*a[1][i][j]));
    }

    for (int i = 0; i < n; i++) {
        v[2][i] = 0;
        for (int j = 0; j < n; j++)
            v[2][i] = mod(v[2][i] + mod(v[1][j]*a[0][i][j]));
    }

    for (int i = 0; i < n; i++) {
        v[1][i] = 0;
        for (int j = 0; j < n; j++)
            v[1][i] = mod(v[1][i] + mod(v[0][j]*a[2][i][j]));
    }
    
    for (int i = 0; i < n; i++) {
        if (v[1][i] != v[2][i]) {
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    return 0;
}
