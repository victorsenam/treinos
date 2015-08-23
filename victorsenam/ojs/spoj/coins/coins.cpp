#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

int n;
map<int, ll> mp;
map<int, ll>::iterator it;

ll pd (int n) {
    it = mp.find(n);
    if (it != mp.end()) return it->second;
    if (n == 0) return 0;
    
    it = mp.insert(make_pair(n, max((ll) n, pd(n/2)+pd(n/3)+pd(n/4)))).first;
    return it->second;
}

int main () {
    while (scanf("%d", &n) != EOF)
        printf("%lld\n", pd(n));
}
