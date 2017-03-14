#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

int n;
int a, b;

map<int, ll> col;
map<int, ll> row;
map<pair<int, int>, ll> s;

pair<int, int> aux;

int main () {
    scanf("%d", &n);

    ll res = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &aux.first, &aux.second);

        res -= s[aux];
        s[aux]++;

        res += col[aux.first];
        res += row[aux.second];
        col[aux.first]++;
        row[aux.second]++;
    }
    printf("%I64d\n", res);
}
