#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 200007;

map<int, int> mp;
int n, m;
int a;
int b[N], c[N];

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        mp[a]++;
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
        scanf("%d", b+i);

    for (int i = 0; i < m; i++)
        scanf("%d", c+i);

    int maxi = 0;
    for (int i = 1; i < m; i++)
        if (mp[b[i]] > mp[b[maxi]] || (mp[b[i]] == mp[b[maxi]] && mp[c[i]] > mp[c[maxi]]))
            maxi = i;
    printf("%d\n", maxi+1);
}
