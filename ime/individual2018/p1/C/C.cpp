#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const ll MOD = 1e9+7;

int t, r, k;
ll n;
ll s[24], a[24];
ll mat[4][24][24];

inline ll mod (ll x) { return x%MOD; }

void mult (int t, int a, int b) {
	for (int i = 1; i <= r+1; i++) {
		for (int j = 1; j <= r+1; j++) {
			mat[2][i][j] = 0;
			for (int k = 1; k <= r+1; k++) {
				mat[2][i][j] = mod(mat[2][i][j] + mod(mat[a][i][k]*mat[b][k][j]));
			}
		}
	}
	for (int i = 1; i <= r+1; i++)
		for (int j = 1; j <= r+1; j++)
			mat[t][i][j] = mat[2][i][j];
}

void printa (int t) {
	cout << "=== Mat " << t << endl;
	for (int i = 1; i <= r+1; i++) {
		for (int j = 1; j <= r+1; j++) {
			cout << mat[t][i][j] << " ";
		}
		cout << endl;
	}
	cout << "=========" << endl;
}

int main () {
	scanf("%d", &t);

	while (t--) {
		scanf("%lld %d %d", &n, &r, &k);
		ll res = 0;

		for (int i = 1; i <= r; i++)
			scanf("%lld", &s[i]);
		for (int i = r; i >= 1; i--)
			scanf("%lld", &a[i]);

		while (r%k) {
			s[r+1] = 0;
			for (int i = 1; i <= r; i++) s[r+1] = mod(s[r+1] + mod(a[i]*s[i]));
			for (int i = r; i >= 1; i--) a[i+1] = a[i];
			a[1] = 0;
			r++;
		}

		for (int i = 1; i <= r+1; i++)
			for (int j = 1; j <= r+1; j++) {
				mat[1][i][j] = (i==j);
				mat[0][i][j] = 0;
			}
		
		for (int i = 1; i <= r; i++)
			for (int j = 1; j <= r; j++) {
				if (j >= i) { mat[0][i][j] = a[j-i+1]; }
				for (int k = 1; k < i; k++) { mat[0][i][j] = mod(mat[0][i][j] + mod(mat[0][k][j]*a[r+1-(i-k)])); }
			}

		for (int j = 1; j <= r; j++) mat[0][r+1][j] = (j%k == 0);
		mat[0][r+1][r+1] = 1;

		ll rm = n%(r/k);
		n = n/(r/k);

		while (n) {
			if (n&1) mult(1, 1, 0);
			mult(0, 0, 0);
			n >>= 1;
		}
		ll sm = 0;
		for (int j = 1; j <= r; j++) {
			sm = mod(sm + mod(s[j]*mat[1][r+1][j]));
		}
		for (int i = k; i <= r && rm; i += k, rm--) {
			for (int j = 1; j <= r; j++)
				sm = mod(sm + mod(s[j]*mat[1][i][j]));
		}
		printf("%lld\n", sm);
		//if (t) printf("\n");
	}
}
