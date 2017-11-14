#include <bits/stdc++.h>
//#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef long long num;
int pr[N];
num w[N];
ll good_i;
//const int N = (1<<17)+7;
const int N = 300007;

inline num s_mod (ll x, ll p) {
	if (x >= p) return x-p;
	else if (x < 0) return x += p;
	return x;
}

num fexp (ll x, int e, num p) {
	ll r = 1;
	while (e) {
		if (e&1) r = (r*x)%p;
		x = (x*x)%p;
		e >>= 1;
	}
	return r;
}

void rou (int p) {
	w[0] = 1;
	bool ok = 0;
	for (num i = 2; !ok && i < p; i++) {
		ok = 1;
		for (ll j = 2; ok && j*j <= p-1; j++)
			if ((p-1)%j == 0)
				ok = !(fexp(i,j,p) == 1 || fexp(i,(p-1)/j,p) == 1);
		if (ok) {
			good_i = i;
			return;
		}
	}
}

void get_rou (int n, int p) {
	w[0] = 1;
	w[1] = fexp(good_i,(p-1)/n,p);
	for (int i = 2; i <= n; i++)
		w[i] = (ll(w[i-1])*w[1])%p;
}

void fft_finite (vector<num> & v, vector<num> & ans, int n, int type, num p) {
	assert(!(n & (n-1)));
	ll invn = fexp(n,p-2,p); // pode ser aproveitado de chamadas diferentes
	if (type == -1) reverse(w, w+n+1);

	pr[0] = 0;
	for (int i = 1; i < n; i++) pr[i] = ((pr[i>>1] >> 1) | ((i&1)?(n>>1):0));
	for (int i = 0; i < n; i++) ans[i] = v[pr[i]];
	for (int sz = 1; sz < n; sz <<= 1) {
		for (int o = 0; o < n; o += (sz<<1)) {
			for (int i = 0; i < sz; i++) {
				const num u = ans[o+i], t = (w[(n/sz/2)*i]*ans[o+sz+i])%p;
				ans[o+i] = s_mod(u+t,p);
				ans[o+i+sz] = s_mod(u-t,p);
			}
		}
	}

	if(type == -1) {
		reverse(w, w+n+1);
		for(int i = 0; i < n; i++) ans[i] = (ans[i]*invn)%p;
	}
}

int n;
const ll P = 1051721729;
ll q[N];
int siz[N];
vector<num> v[N];
vector<num> a, b;

int main () {
	scanf("%d", &n);
	rou(P);

	a.resize(N); b.resize(N);

	for (int i = 0; i < n; i++) {
		ll a;
		scanf("%lld", &a);
		v[a-1][++q[a]] = 1;
	}

	for (int i = 0; i < n; i++) {
		v[i][0] = 1;
		siz[i] = q[i] + 1;
	}

	for (int sz = 1; sz < n; sz += sz) {
		for (int i = 0; i < n; i += sz + sz) {
			int sm = (siz[a]+siz[b]);
			siz[a] += siz[b];
			get_rou(sm,P);
			v[i].resize(sm,0);
			v[i+sz].resize(sm,0);
			while (sm&(sm-1)) sm++;
			fft_finite(v[i],a,n,1,P);
			fft_finite(v[i+sz],b,n,1,P);
			for (int j = 0; j < sm; j++) a[j] = (a[j]*b[j])%P;
			fft_finite(a,v[i],n,-1,P);
		}
	}

	for (int i = 0; i < siz[0]; i++)
		cout << v[0][i] << " ";
	cout << endl;
}

