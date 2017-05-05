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

ll a[2][2];
ll d[2];

int main () {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%lld", &a[i][j]);
            d[i] += a[i][j] * a[i][j];
        }
    }

    if (d[0] < d[1])
        printf("Russo\n");
    else if (d[0] == d[1])
        printf("Empate\n");
    else
        printf("Wil\n");

}
