#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

set<ll> s;
ll n;
int m;
ll b[12];

int main () {
	scanf("%lld %d", &n, &m);

	for (int i = 0; i < m; i++) scanf("%lld", &b[i]);
	queue<ll> qu;
	qu.push(n);
	s.insert(n);

	while (!qu.empty()) {
		ll a = qu.front(); qu.pop();
		for (int i = 0; i < m; i++) {
			if (s.find(a/b[i]) == s.end()) {
				s.insert(a/b[i]);
				qu.push(a/b[i]);
			}
		}
	}
	
	printf("%d\n", (int) s.size());
}
