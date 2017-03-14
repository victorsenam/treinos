#include <bits/stdc++.h>

using namespace std;

const int N = 10000;
char str[N];
char aux[N];
int m;
int l, r, k;

void solve (int l, int r, int k) {
    for (int i = l; i < r; i++) 
        aux[l+((i-l+k)%(r-l))] = str[i];
    for (int i = l; i < r; i++)
        str[i] = aux[i];
}

int main () {
    scanf(" %s", str);

    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &l, &r, &k);
        l--;

        k %= (r-l);

        solve(l,r,k);
    }
    printf("%s\n", str);
}
