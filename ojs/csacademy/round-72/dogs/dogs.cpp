#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;
int n, m;
ll t[N];
int p[N];
int cl[N], cr[N];
const int K = 20;
ll rmq[N][K];

ll get (int l, int r) {
	ll a = 0;
	cout << "[" << l << " " << r << "]" << endl;
	for (int k = K; k >= 0; k--) {
		if (l + (1<<k) <= r+1) {
			a = max(a, rmq[l][k]);
			l += (1<<k);
			cout << a << " -> " << l << endl;
		}
	}
	cout << a << endl;
	return a;
}

int comp (int i, int j) {
	if (cr[j] < cl[i] || cr[i] < cl[j]) return get(cl[i],cr[i]) < get(cl[j],cr[j]);
	if (cl[i] <= cl[j] && cr[j] <= cr[i]) return 0;
	if (cl[j] <= cl[i] && cr[i] <= cr[j]) return 1;
	if (cl[i] < cl[j]) return get(cl[i],cl[j]-1) < get(cr[i]+1,cr[j]);
	return get(cr[j]+1,cr[i]) < get(cl[j],cl[i]-1);
}

int main () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%lld", &t[i]);
	for (int i = n-1; i >= 0; i--) {
		rmq[i][0] = t[i];
		cout << i << ": ";
		for (int k = 1; k < K; k++) {
			if (i + (1<<(k-1)) > n) rmq[i][k] = rmq[i][k-1];
			else rmq[i][k] = max(rmq[i][k-1], rmq[i+(1<<(k-1))][k-1]);
			cout << rmq[i][k] << " ";
		}
		cout << endl;
	}

	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &cl[i], &cr[i]);
		cl[i]--; cr[i]--;
		p[i] = i;
	}

	sort(p, p+m, [] (int i, int j) { return comp(i,j); });

	for (int i = 0; i < m; i++) printf("%d ", p[i]+1);
	printf("\n");

}
