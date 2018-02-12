#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int f[250 * 260];
int p[250 * 260];
int fim[250 * 260];

int main() {
	int n, m, x;
	int i, j, a, b, c;
	scanf("%d %d %d %d", &f[1], &a, &b, &c);
	p[1] = 1;
	for(i = 2; i <= 250 * 250; i++)
		f[i] = ((a * f[i - 1] + b) % c) + 1, p[i] = i;
	scanf("%d %d", &m, &n); n *= m;
	map<int, int> oc;
	for(i = 0; i < n; i++) {
		scanf("%d", &x);
		oc[x]++;
	}
	printf("%d\n", int(oc.size()));
	vector<int> all;
	for(pii e : oc)
		all.pb(e.first);
	sort(all.begin(), all.end(), [&oc](int x, int y) { return oc[x] < oc[y]; });
	sort(p + 1, p + all.size() + 1, [](int i, int j) { return f[i] < f[j]; });
	for(i = 0; i < all.size(); i++) {
		fim[p[i + 1] - 1] = all[i];
		//printf("fim[p[%d] - 1] = fim[%d] = all[%d] = %d\n", i + 1, p[i + 1] - 1, i, all[i]);
	}
	for(i = 0; i < all.size(); i++)
		printf("%d ", fim[i]);
	putchar('\n');
}
