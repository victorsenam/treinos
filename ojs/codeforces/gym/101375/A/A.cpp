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

ll n;

int main () {
    scanf("%lld", &n);
    printf("%lld\n", n*(n+1)/2 - n + 1);
}
