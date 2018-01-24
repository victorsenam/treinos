#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int lst[1123];
int nx[1123];

int memo[312][312];
int dp(int l, int r) {
	if(l >= r) return 0;
	int &ret = memo[l][r];
	if(ret != -1) return ret;
	ret = dp(l + 1, r);
	for(int k = nx[l]; k != -1 && k <= r; k = nx[k]) {
		ret = max(ret, dp(l + 1, k - 1) + dp(k, r) + 1);
	}
	//printf("dp(%d, %d) = %d\n", l, r, ret);
	return ret;
}

int a[1123];

int main () {
	int i, n;
	memset(memo, -1, sizeof memo);
	scanf("%d %*d", &n);
	for(i = 0; i < n; i++) scanf("%d", &a[i]);
	memset(lst, -1, sizeof lst);
	memset(nx, -1, sizeof nx);
	for(i = 0; i < n; i++) {
		if(lst[a[i]] != -1) nx[lst[a[i]]] = i;
		lst[a[i]] = i;
	}
	//for(i = 0; i < n; i++) printf("nx[%d] = %d\n", i, nx[i]);
	printf("%d\n", n - 1 - dp(0, n - 1));
}
