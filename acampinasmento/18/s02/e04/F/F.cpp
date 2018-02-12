#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

inline ll rnd() { return (ll(rand()) << 32) ^ ll(rand()); }

const int N = 1123456;
ll a[N], ans[N];
int s[N];

int main() {
	srand(time(NULL));
	int i, n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	for(i = 0; i < n; i++) a[i] = rnd();
	for(i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b); a--; b--;
		ans[a] ^= ::a[b];
		ans[b] ^= ::a[a];
	}
	//for(i = 0; i < n; i++) printf("[%d] %lld\n", i, ans[i]);
	while(k--) {
		int x;
		scanf("%d", &x);
		ll xo = 0;
		for(i = 0; i < x; i++) { scanf("%d", &s[i]); s[i]--; xo ^= a[s[i]]; }
		//puts("----");
		for(i = 0; i < x; i++) {
			ans[s[i]] ^= (xo ^ a[s[i]]);
			//printf("[%d] %lld\n", s[i], ans[s[i]]);
		}
	}
	for(i = 0; i < n; i++)
		if(ans[i])
			puts("NIE");
		else
			puts("TAK");
}
