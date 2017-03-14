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

ll n;

int main () {
    cin >> n;
    ll ans = 0;
    ll i;
    for(i = 1; i * i < n; i++)
        if(n%i == 0) ans += 2;
    if (n%i == 0) ans++;
    cout << ans << endl;
}

