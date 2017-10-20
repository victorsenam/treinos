#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e6+7;
const int K = 5;

int n;
ll a[N];
int nx[K];
int p[K];

ll mx[4*N];

int build (int u, int l, int r) {
	if (l == r)
		mx[u] = a[l];
	else {
		int md = (l+r)/2;
		build(2*u, l, md);
		build(2*u+1, md+1, r);
		mx[u] = max(mx[2*u], mx[2*u+1]);
	}
}

int find (int u, int l, int r, int ql, int qr, ll w) {
	if (r < ql || qr < l) return qr + 1;
	if (ql <= l && r <= qr && mx[u] <= w) return qr + 1;
	int md = (l+r)/2;
	int a = find(2*u+1, md+1, r, ql, qr, w);
	if (a != qr + 1) return a;
	return find(2*u, l, md, ql, qr, 2);
}

int main () {
	scanf("%d", &n);

	for (int j = 0; j < K; j++)
		p[j] = j;

	build(1, 1, n);

	int res = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);

		for (int j = 0; j < K; j++) {
			if (a[i]&(1<<j))
				nx[j] = i;
		}

		sort(p, p+K, [] (int i, int j) {
			return nx[i] < nx[j];
		});
		
		cout << "add " << a[i] << endl;
		int cur = 0;
		ll msk = (1ll<<K) - 1;
		for (int _j = 0; _j < K; _j++) {
			int j = p[_j];
			int a = find(1, 1, n, cur+1, nx[j], msk);
			cout << "busca " << msk << " entre " << cur + 1 << " e " << nx[j] << " : " << a<< endl;
			res += nx[j] + 1 - a; // primeiro lugar q aparece alguem maior
			cur = nx[j];
			msk -= (1 << j);
		}
	}

	printf("%d\n", res);
}
