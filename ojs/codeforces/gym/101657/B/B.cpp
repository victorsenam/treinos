#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int M = 1504;
const int N = 3002;

int dp[M][M], rv[M][M];
char s[N], t[N];
int n, m;

int main () {
	while (scanf(" %s %s", s, t) != EOF) {
		n = strlen(s);
		m = strlen(t);
		
		int ans = 0;
		for (int k = 0; k < 2; k++) {
			memset(dp, 0, sizeof dp);
			memset(rv, 0, sizeof rv);

			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= m; j++) {
					dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
					if (s[i-1] == t[j-1]) dp[i][j] = max(dp[i][j], dp[i-1][j-1] + 1);
				}
			}
			for (int i = n; i > 0; i--) {
				for (int j = m; j > 0; j--) {
					rv[i][j] = max(rv[i+1][j],rv[i][j+1]);
					if (s[i-1] == t[j-1]) rv[i][j] = max(rv[i][j], rv[i+1][j+1] + 1);
				}
			}
			for (int i = 1; i <= n+1; i++)
				for (int j = 1; j <= m+1; j++)
					ans = max(ans, dp[i-1][j-1] + rv[i][j]);

			for (int i = 0; i <= m/2; i++)
				swap(t[i], t[m-i-1]);
		}
		printf("%d\n" , ans+ans);
	}
}
