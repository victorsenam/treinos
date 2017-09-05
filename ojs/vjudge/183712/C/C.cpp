#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const ll MOD = 10007;

ll mat[4][4] = {
	{ 2, 2, 0, 0},
	{ 1, 0, 0, 0},
	{ 2, 2, 2, 2},
	{ 0, 0, 1, 0}
};

inline ll mod (ll x) {
	return x%MOD;
}

ll cur[4][4];
ll res[4][4];
ll aux[4][4];
int t;
ll n;

void mult (ll a[][4], ll b[][4]) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			aux[i][j] = 0;
			for (int k = 0; k < 4; k++)
				aux[i][j] = mod(aux[i][j] + mod(a[i][k]*b[k][j]));
		}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			a[i][j] = aux[i][j];
}

int main () {
	while (scanf("%lld", &n) != EOF && n >= 0) {
		for (int i = 0; i < 4; i++)
	 		for (int j = 0; j < 4; j++) {
				res[i][j] = (i==j);
				cur[i][j] = mat[i][j];
			}

		while (n) {
			if (n&1) mult(res, cur);
			mult(cur,cur);
			n >>= 1;
		}

		printf("%lld\n", mod(res[2][2] + res[2][0]));
	}
}
