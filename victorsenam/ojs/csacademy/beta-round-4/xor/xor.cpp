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
const int M = N*40;

int v[N];
int s[4*N];

int n;

void join (int a, int b, int x) {
        
}

int unset (int x, int l, int r) {
    if (x < l || x >= r)
        return 0;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", s+i);
    }
}
