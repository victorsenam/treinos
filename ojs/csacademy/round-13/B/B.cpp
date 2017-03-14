#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e5+7;

int n[2];
int v[2][N];
multiset<int> s;
multiset<int>::iterator it;

void nope (){
    printf("-1\n");
    exit(0);
}

int main () {
    for (int k = 0; k < 2; k++)
        scanf("%d", &n[k]);

    for (int k = 0; k < 2; k++)
        for (int i = 0; i < n[k]; i++)
            scanf("%d", &v[k][i]);

    ll res = 0;
    for (int i = 0; i < n[0]; i++) {
        res += v[0][i];
        s.insert(v[0][i]);
    }

    for (int i = 0; i < n[1]; i++) {
        it = s.upper_bound(v[1][i]);
        if (it == s.end()) nope();
        res -= *it;
        s.erase(it);
    }

    printf("%lld\n", res);
}
