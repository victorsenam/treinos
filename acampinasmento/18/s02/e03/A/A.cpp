#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

int m, n;
int v[N];

int main () {
	scanf("%d %d", &m, &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &v[i]);

	int r = 0;
	while (n && v[n-1] == m-1) {
		n--; m--; r++;
	}
	if (r) {
		printf("%d\n", r);
		return 0;
	}

	int ls = m;
	vector<int> p;
	for (int i = n-1; i >= 0; i--) {
		if (v[i] + 1 == ls) p.back()++;
		else {
			if ((ls - v[i])%2) p.pb(0);
			else if(v[i] < ls - 2) p.pb(0), p.pb(0);
			p.pb(1);
		}
		ls = v[i];
	}

	int x = 0;
	for (int i = 0; i < p.size(); i++) if (i&1) x^=p[i];
	for (int i = 0; i < p.size(); i++) {
		if (i&1) {
			r += ((x^p[i]) < p[i]);
		} else if (i > 0) {
			int xx = (x^p[i-1]);
			if(xx > p[i - 1] && xx <= p[i - 1] + p[i])
				r++;
		}
	}

	if (x) printf("%d\n", r);
	else printf("0\n");
}
