#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back
ll modn = 1000000007;

inline void rd(int &x) {
	char c;
	while(isspace(c = getchar_unlocked()));
	x = (c - '0');
	while(isdigit(c = getchar_unlocked()))
		x = (x << 2) + (x << 1) + (c - '0');
}

const int N = 112345;
int n[N], l[N], r[N], p[N], ans[N];
int dp[2][112][112];

int main() {
	int m, i;
	rd(m);
	for(i = 0; i < m; i++) {
		rd(n[i]); rd(l[i]); rd(r[i]);
		p[i] = i;
	}
	sort(p, p + m, [](int i, int j) { return n[i] < n[j]; });
	dp[1][1][0] = 1;
	i = 0;
	for(int n = 2; n <= 49999; n++) {
		for(int l = 1; l <= 99; l++)
			for(int r = 0; r <= 99; r++) {
				dp[n & 1][l][r] = (dp[!(n & 1)][l][r] * (n - 1) + dp[!(n & 1)][l - 1][r] + dp[!(n & 1)][r][l - 1]) % modn;
				//printf("ans(%d, %d, %d) = %d\n", n, l, r, dp[n & 1][l][r]);
			}
		for(; i < m && ::n[p[i]] - 1 <= n; i++) {
			ans[p[i]] = dp[!(::n[p[i]] & 1)][::l[p[i]] - 1][::r[p[i]] - 1] + dp[!(::n[p[i]] & 1)][::r[p[i]] - 1][::l[p[i]] - 1];
		}
	}
	for(i = 0; i < m; i++)
		printf("%d\n", ans[i]);
}
