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

const int N = 1e5+7;

ll v[N];
ll a[N];
int n;

int main () {
    scanf("%d", &n);

    ll res = 0;
    for (int i = 0; i <n ; i++) {
        scanf("%lld", &v[i]);
        a[i+1] = a[i] + v[i];
        res += v[i] * a[i];
    }

    printf("%lld\n", res);
}
