#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back
#define left asdlaisd

const int N = 3123;
int en = 0;
ll we[N];
bitset<20009> path[N];
ll dp[2][20009];

int tot[N];
int from[N];
int aa[N];
int all;

int v[N], qt[N];
void add(int i, ll q) {
	if(q == 0) return;
	assert(en < N);
	//printf("[%d] adding %lld\n", i, q);
	from[en] = i;
	aa[en] = q;
	we[en++] = q * v[i];
}

int main () {
	int i, n, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &v[i]);
		//v[i] = i + 1;
	}
	for(i = 0; i < n; i++) {
		scanf("%d", &qt[i]);
		//qt[i] = 20000;
		int j = 0;
		while((1 << (j + 1)) - 1 <= qt[i])
			j++;
		for(int k = 0; k < j; k++)
			add(i, (1ll << k));
		if(qt[i] > ((1ll << j) - 1ll))
			add(i, (qt[i] - ((1ll << j) - 1ll)));
	}
	//printf("en %d\n", en);
	ll w;
	scanf("%lld", &w);
	for(j = 1; j <= w; j++)
		dp[en & 1][j] = 1e9;
	for(i = en - 1; i >= 0; i--)
		for(int left = 1; left <= w; left++) {
			dp[i & 1][left] = dp[!(i & 1)][left];
			if(we[i] <= left && dp[!(i & 1)][left - we[i]] + aa[i] < dp[i & 1][left]) {
				dp[i & 1][left] = dp[!(i & 1)][left - we[i]] + aa[i];
				path[i][left] = 1;
			}
			//printf("dp[%d][%d] = %d\n", i, left, dp[i & 1][left]);
		}
	printf("%lld\n", dp[0][w]);
	i = 0;
	while(w) {
		//printf("%d, %lld\n", i, w);
		if(path[i][w]) {
			tot[from[i]] += aa[i];
			w -= we[i];
		}
		i++;
		//assert(i < 20);
	}
	for(i = 0; i < n; i++)
		printf("%d%s", tot[i], i == n - 1? "\n" : " ");
}
