#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

struct seg {
	int a, b, i;

	bool operator < (const seg & o) const {
		return b > o.b;
	}
};

int n, k;
vector<seg> v;
priority_queue<seg> pq;

int main () {
	scanf("%d %d", &n, &k);
	v.resize(n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &v[i].a, &v[i].b);
		v[i].i = i;
	}
	sort(v.begin(), v.end(), [] (seg a, seg b) { return a.a < b.a; });

	seg ans;
	ans.a = ans.b = 0;
	for (int i = 0; i < n; i++) {
		pq.push(v[i]);
		while (pq.top().b <= v[i].a) pq.pop();
		while (pq.size() > k) pq.pop();
		if (pq.size() == k) {
			seg loc;
			loc.b = pq.top().b;
			loc.a = v[i].a;
			if (loc.b - loc.a > ans.b - ans.a) {
				ans = loc;
			}
		}
	}

	printf("%d\n", ans.b - ans.a);
	for (int i = 0; i < n; i++) {
		if (k && v[i].a <= ans.a && ans.b <= v[i].b) {
			printf("%d ", v[i].i+1);
			k--;
		}
	}
	printf("\n");
}
