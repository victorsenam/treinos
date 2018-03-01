#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 5e5;
const int T = (1<<20) + 2;
const int D = 12;
const int MOD = 1e9+7;

int dp[D][T];
int n, d;
int v[N];
int tp[D][2];

int main () {
	scanf("%d %d", &n, &d);
	
	for (int i = 0; i < n; i++)
		scanf("%d", &v[i]);
	sort(v,v+n);

	dp[0][0] = 1;
	for (int i = 0; i < n; i++) {
		for (int xr = 0; !xr || __builtin_clz(xr) >= __builtin_clz(v[i]); xr++) if (xr < (xr^v[i])) {
			for (int q = 0; q < d; q++) {
				tp[q][0] = dp[q][xr]; 
				tp[q][1] = dp[q][xr^v[i]];
			}
			for (int q = 0; q < d; q++) {
				dp[q][xr] = (tp[(q+1)%d][0] + tp[q][1])%MOD;
				dp[q][xr^v[i]] = (tp[(q+1)%d][1] + tp[q][0])%MOD;
			}
		}
	}
	printf("%d\n", (dp[0][0] + MOD - !(n%d))%MOD);
}
