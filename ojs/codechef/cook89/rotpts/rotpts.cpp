#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back
const ll MOD = 1e9+7;

inline ll mod (ll x) {
	return ((x%MOD) + MOD)%MOD;
}

struct mat {
	ll a[3][3];
	mat (int _a, int b, int c, int d, int e, int f, int g, int h, int i) {
		a[0][0] = _a;
		a[0][1] = b;
		a[0][2] = c;
		a[1][0] = d;
		a[1][1] = e;
		a[1][2] = f;
		a[2][0] = g;
		a[2][1] = h;
		a[2][2] = i;
	}
	mat () {}

	mat operator * (mat o) {
		mat r(0,0,0,0,0,0,0,0,0);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				r.a[i][j] = 0;
				for (int k = 0; k < 3; k++) 
					r.a[i][j] = mod(r.a[i][j] + mod(a[i][k]*o.a[k][j]));
			}
		}
		return r;
	}

	void printa () {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++)
				cout << a[i][j] << " ";
			cout << endl;
		}
		cout << endl;
	}
};

mat rot(0,1,0,-1,0,0,0,0,1);
mat nwmat (ll x, ll y, ll a) {
	a /= 90;
	mat res(1,0,0,0,1,0,-x,-y,1);
	for (int k = 0; k < a; k++)
		res = res*rot;
	res = res*mat(1,0,0,0,1,0,x,y,1);
	return res;
}

const int N = 4e5+7;

mat seg[N];
int n;
int q;

mat upd (int u, int l, int r, int i, mat & mt) {
	if (r < i || l > i) return seg[u];
	if (l == r) return seg[u] = mt;
	int md = (l+r)/2;
	return seg[u] = upd(2*u, l, md, i, mt) * upd(2*u+1, md+1, r, i, mt);
}

mat get (int u, int l, int r, int ql, int qr) {
	if (qr < l || r < ql) return mat(1,0,0,0,1,0,0,0,1);
	if (ql <= l && r <= qr) return seg[u];
	int md = (l+r)/2;
	return get(2*u, l, md, ql, qr) * get(2*u+1, md+1, r, ql, qr);
}

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		ll x, y, a;
		scanf("%lld %lld %lld", &x, &y, &a);
		mat mt = nwmat(x,y,a);
		//mt.printa();
		upd(1, 0, n-1, i, mt);
	}

	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		int t;
		scanf("%d", &t);
		if (t == 1) {
			ll x, y, l, r;
			scanf("%lld %lld %lld %lld", &x, &y, &l, &r);
			l--; r--;
			mat rs = get(1, 0, n-1, l, r);
			printf("%lld ", mod(mod(mod(x*rs.a[0][0]) + mod(y*rs.a[1][0])) + rs.a[2][0]));
			printf("%lld\n", mod(mod(mod(x*rs.a[0][1]) + mod(y*rs.a[1][1])) + rs.a[2][1]));
		} else {
			ll i, x, y, b;
			scanf("%lld %lld %lld %lld", &i, &x, &y, &b);
			i--;
			mat mt = nwmat(x,y,b);
			upd(1, 0, n-1, i, mt);
		}
	}
}
