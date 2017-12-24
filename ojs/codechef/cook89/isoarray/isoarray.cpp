#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 75000;
const int R = 275;

int fq[N];
int a[N];
int last;
vector<int> occ[N];

int main () {
	int t;
	int n, q;

	scanf("%d", &t);
	while (t--) {
		last = 0;
		scanf("%d", &n);
		vector<int> big;

		for (int i = 0; i < n; i++) 
			fq[i] = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			occ[a[i]].pb(i+1);
			a[i]--;
			fq[a[i]]++;
		}

		for (int i = 0; i < n; i++)
			if (fq[i] >= R)
				big.pb(i);
		
		scanf("%d", &q);
		for (int qq = 1; qq <= q; qq++) {
			multiset<int> fa, fb;
			int x, y, z, t, c, d, k;
			scanf("%d %d %d %d", &x, &y, &c, &d);
			k = min(n-x, n-z) + 1;
			y = x + (c + d*last)%k;
			t = z + (c + d*last)%k;

			for (int v : big) {
				fa.insert(occ[v].upper_bound(y) - occ[v].lower_bound(x));
				fb.insert(occ[v].upper_bound(t) - occ[v].lower_bound(z));
			}

			bool ok = (fa == fb);
			for (int k = R-1; ok && k >= 1; k--) {
				ok = (get(hd[x], x, y) == get(hd[z], z, y));
			}
			
			if (ok) { printf("YES\n"); last = qq; }
			else printf("NO\n");
		}
	}
}
