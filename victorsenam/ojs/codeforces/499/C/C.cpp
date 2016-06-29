#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define lld I64d
#define DEBUG(...) {}
#endif

const int N = 307;

ll me[2], ob[2];
ll rt[N][3];
int n;

bool getside(ll x, ll y, int i) {
    return (rt[i][0]*x + rt[i][1]*y + rt[i][2] > 0);
}

int main () {
    scanf("%lld %lld", &me[0], &me[1]);
    scanf("%lld %lld", &ob[0], &ob[1]);

    scanf("%d", &n);

    int cnt = 0;

    for (int i = 0 ; i< n; i++) {
        scanf("%lld %lld %lld", &rt[i][0], &rt[i][1], &rt[i][2]);
        cnt += (getside(me[0], me[1], i) != getside(ob[0], ob[1], i));
    }

    printf("%d\n", cnt);
}

