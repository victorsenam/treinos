#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll n, m, a;

int main () {
	scanf("%lld %lld %lld", &n, &m, &a);
	printf("%lld\n", ((n+a-1)/a)*((m+a-1)/a));
}
