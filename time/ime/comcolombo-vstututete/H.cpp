#include <bits/stdc++.h>

using namespace std;

const int MAX = 2010;

char str[MAX];
int dp[MAX], sum[MAX], aux[MAX];

int get(int a, int b) {
	if(b < 0) return sum[a];
	else return sum[a] - sum[b];
}

char flip(char ch) {
	if(ch == 'A') return 'B';
	else return 'A';
}

int main() {
	int T;
	scanf("%d", &T);
	for(int t = 1; t <= T; t++) {
		int n, k, m;
		scanf("%d%d%d", &n, &m, &k);
		n *= 2;
		scanf(" %s", str);
		memset(dp, 0, sizeof(dp));
		for(int i = 1; i <= k; i++)
			dp[i] = 1;
		dp[0] = 0;
		sum[0] = 0;
		for(int i = 1; i <= m; i++)
			sum[i] = sum[i - 1] + dp[i];
		for(int i = n - 2; i >= 0; i--) {
			for(int j = 0; j <= m; j++) {
				if(j - k <= 0)
					dp[j] = 1;
				else if(str[i] == str[i + 1])
					dp[j] = (get(j - 1, j - k - 1) != 0);
				else
					dp[j] = (get(j - 1, j - k - 1) != k);
			}
			sum[0] = dp[0];
			for(int j = 1; j <= m; j++)
				sum[j] = sum[j - 1] + dp[j];
		}
		printf("Case #%d: ", t);
		if(dp[m]) printf("%c\n", str[0]);
		else printf("%c\n", flip(str[0]));
	}
	return 0;
}
