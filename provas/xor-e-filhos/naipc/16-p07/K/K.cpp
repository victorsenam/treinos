#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;

int n[2];
ll a[2][N];

int main () {
    int turn = 0;
    while (scanf("%d %d", n, n+1) != EOF) {

        a[0][0] = a[1][0] = 0;
        for (int i = 1; i <= n[0]; i++)
            scanf("%lld", a[0]+i);
        for (int i = 1; i <= n[1]; i++)
            scanf("%lld", a[1]+i);

        sort(a[0], a[0]+n[0]+1);
        sort(a[1], a[1]+n[1]+1);
        
        bool t = 0;
        while (n[0] && n[1]) {
            if (a[t][n[t]] + a[t][n[t]-1] > a[!t][n[!t]] + a[!t][n[!t]-1]) {
                n[!t] = 0;
            } else if (a[t][n[t]] > a[!t][n[!t]]) {
                n[!t]--;
            } else {
                a[t][n[t]-1] += a[t][n[t]];
                n[t]--;
            }
            t = !t;
        }

        if (n[0])
            printf("Case %d: Takeover Incorporated\n", ++turn);
        else
            printf("Case %d: Buyout Limited\n", ++turn);

    }
}
