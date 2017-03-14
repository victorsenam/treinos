#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

int n, m;

int main () {
    scanf("%d %d", &n, &m);

    int att = 0;
    for (int i = 0; i < n; i++) {
        att += 2;
        while (att%3 == 0 && att/3 <= m)
            att += 2;
    }
    int res = max(3*m, att);
    printf("%d %d\n", att, 3*m);

    att = 0;
    for (int i = 0; i < m; i++) {
        att += 3;
        while (att%2 == 0 && att/2 <= n)
            att += 3;
    }

    res = min(res, max(2*n, att));
    printf("%d %d\n", 2*n, att);

    printf("%d\n", res);
}
