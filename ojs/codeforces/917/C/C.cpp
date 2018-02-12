#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int M = 12;

int x, k, n, q;
ll c[10];
ll dp[M];
ll aux[M];
pii spec[30];
int pp[M];
int cur;
int p;

ll res[10][10];

void walk (ll cost) {
	dp[p] = LLONG_MAX;
	for (int i = 1; i <= k; i++)
		dp[p] = min(dp[p], dp[(p-i+M)%M] + c[i]);
	dp[p] += cost;
	//cout << cur << " = " << dp[p] << endl;
	cur++;
	p = (p+1)%M;
}

void jump (ll to) {
	for (int j = 1; j <= k; j++) aux[(p-j+M)%M] = LLONG_MAX;
	for (int i = 1; i <= k; i++)
		for (int j = 1; j <= k; j++) {
			ll a = cur - i;
			ll b = to - j;
			if (a > b) continue;
			for (int step = 1; step <= k; step++) {
				if ((b-a)%step) continue;
				if (dp[(p-i+M)%M] == LLONG_MAX) continue;
				aux[(p-j+M)%M] = min(aux[(p-j+M)%M], dp[(p-i+M)%M] + ((b-a)/step)*c[i]);
			}
		}
	for (int i = k; i >= 1; i--) {
		dp[(p-i+M)%M] = aux[(p-i+M)%M];
		//cout << to - i << " = " << dp[(p-i+M)%M] << endl;
	}
	cur = to;
}

int main () {
	scanf("%d %d%d %d", &x, &k, &n, &q);
	for (int i = 1; i <= k; i++) {
		scanf("%lld", &c[i]);
	}

	for (int i = 0; i < q; i++) {
		scanf("%lld %lld", &spec[i].first, &spec[i].second);
	}
	sort(spec, spec+q);
	spec[q].first = n;
	spec[q].second = 0;
	q++;

	for (int i = 1; i <= x; i++) {
		cout << "starting from " << i << endl;
		for (int j = 0; j < M; j++)
			dp[j] = LLONG_MAX - 2e9;
		dp[0] = 0;
		p = 1;
		cur = i+1;

		for (int s = 0; s < q; s++) {
			int kk;
			for (kk = 0; cur < spec[s].first && kk < k*k; kk++)
				walk(0);
			jump(spec[s].first);
			walk(spec[s].second);
		}

		for (int j = 1; j <= x; j++) {
			res[i-1][x-j] = dp[(p-j+M)%M];
			cout << i << "->" << x-j+1 << ": " << res[i-1][x-j] << endl;
		}
	}

	ll fin = LLONG_MAX;
	for (int i = 0; i < x; i++) pp[i] = i;
	do {
		ll loc = 0;
		for (int i = 0; i < x; i++)
			loc += res[i][pp[i]];
		fin = min(fin, loc);
	} while (next_permutation(pp,pp+x));
	printf("%lld\n", fin);
}
