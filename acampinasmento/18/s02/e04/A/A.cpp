#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int T = 30000;
ll p;

void mul(ll a[2][2], ll b[2][2], ll c[2][2]) {
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++) {
			c[i][j] = 0;
			for(int k = 0; k < 2; k++)
				c[i][j] += a[i][k] * b[k][j];
			c[i][j] %= p;
		}
}

void cp(ll a[2][2], ll b[2][2]) {
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
			b[i][j] = a[i][j];
}

ll aux[2][2];

int main () {
	ll x, a, b, y;
	int i;
	cin >> p >> x >> a >> b >> y;
	if(a == 0) {
		if(y == x) puts("0");
		else if(y == b) puts("1");
		else puts("NIE");
		return 0;
	}
	//cin >> k; k += 3;
	//i = 0;
	//while(k--) {
	//	x = (x * a + b) % p;
	//	printf("[%d] = %d\n", ++i, x);
	//	cout << x << endl;
	//}
	//cout << x << endl;
	//return 0;
	ll mat[2][2];
	mat[0][0] = mat[1][1] = 1;
	mat[0][1] = mat[1][0] = 0;
	ll base[2][2];
	base[0][0] = a;
	base[0][1] = b;
	base[1][0] = 0;
	base[1][1] = 1;
	for(i = 0; i < T; i++) {
		mul(base, mat, aux);
		cp(aux, mat);
	}
	map<ll, ll> mp;
	for(i = T; ; i += T) {
		x = (mat[0][0] * x + mat[0][1]) % p;
		//printf("[%d] nx %lld\n", i, x);
		mp[x] = i;
		if(i > p + 3) break;
	}
	for(ll i = 0; i < 2000000000 / T; i++) {
		if(mp.count(y)) {
			printf("%lld\n", mp[y] - i);
			return 0;
		}
		y = (a * y + b) % p;
	}
	puts("NIE");
}
