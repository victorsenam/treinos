#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 5e3+7;

int memo[2][N][2];
char str[2][N];
int n, m;

int main () {
	int t;
	scanf("%d", &t);

	while (t--) {
		scanf("%d %d", &n, &m);
		scanf(" %s %s", str[0], str[1]);

		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= m; j++) {
				if (i == 0 && j == 0)
					memo[i&1][j][0] = memo[i&1][j][1] = 1;
				else if (i == 0)
					memo[i&1][j][1] = memo[i&1][j-1][1] + (j >= 2 && str[1][j-1] != str[1][j-2]);
				else if (j == 0)
					memo[i&1][j][0] = memo[!(i&1)][j][0] + (i >= 2 && str[0][i-1] != str[0][i-2]);
				else {
					memo[i&1][j][0] = min((i >= 2)?memo[!(i&1)][j][0] + (str[0][i-1] != str[0][i-2]):n+m+1, memo[!(i&1)][j][1] + (str[0][i-1] != str[1][j-1]));
					memo[i&1][j][1] = min((j >= 2)?memo[i&1][j-1][1] + (str[1][j-1] != str[1][j-2]):n+m+1, memo[i&1][j-1][0] + (str[0][i-1] != str[1][j-1]));
				}
			}
		}

		printf("%d\n", min(memo[n&1][m][0], memo[n&1][m][1]));
	}

}
