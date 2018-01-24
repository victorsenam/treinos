#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

#define x first
#define y second
pii p[1123];

int main() {
	int i, j, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%lld %lld", &p[i].x, &p[i].y);
	if(n <= 3) {
		puts("0");
		return 0;
	}
	set<pii> s;
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++) {
			pii a(p[i].x + p[j].x, p[i].y + p[j].y);
			if(s.count(a)) {
				puts("1");
				return 0;
			}
			s.insert(a);
		}
	puts("2");
}
