#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;
int n;
int ts;

int to[N];
int v[N];
int s[N];

int main () {
	scanf("%d", &ts);

	while (ts--) {
		scanf("%d", &n);

		int res = 0;
		
		for (int i = 0; i < n; i++) {
			scanf("%d", &s[i]);
			s[i]--;
		}
	

		int cur = 0;
		for (int i = 0; i < n; i++)
			v[i] = s[i];
		for (int i = 1; i < n; i++)
			if (v[i] == n/2 - 1) {
				swap(v[i], v[0]);
				cur++;
			}
		for (int i = 0; i < n-1; i++)
			if (v[i] == n/2) {
				swap(v[i], v[n-1]);
				cur++;
			}
		for (int i = 1; i < n - 1; i += 2)
			if (v[i] < n/2)
				cur++;
		res = cur;

		cur = 0;
		for (int i = 0; i < n; i++)
			v[i] = s[i];
		for (int i = 1; i < n; i++)
			if (v[i] == n/2) {
				swap(v[i], v[0]);
				cur++;
			}
		for (int i = 0; i < n-1; i++)
			if (v[i] == n/2 - 1) {
				swap(v[i], v[n-1]);
				cur++;
			}
		for (int i = 1; i < n - 1; i += 2)
			if (v[i] >= n/2)
				cur++;
		res = min(res, cur);

		printf("%d\n", res);
	}
}
