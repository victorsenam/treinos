#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e3+7;

int v[N];
int fs[N];
int sn[N];
int res;
int n;
int memo[N][N];
int memo2[N][N];

int dp (int i, int ls) {
	if (i == n) return 0;
	int & me = memo[i][ls];
	if (me != -1) return me;
	me = dp(i+1,ls);
	if (v[ls] <= v[i]) me = max(me, dp(i+1,i) + 1);
	return me;
}

int inv (int i, int ls) {
	if (i == -1) return 0;
	int & me = memo2[i][ls];
	if (me != -1) return me;
	me = inv(i-1,ls);
	if (v[ls] >= v[i]) me = max(me, inv(i-1,i) + 1);
	return me;
}

int main () {
	memset(memo, -1, sizeof memo);
	memset(memo2, -1, sizeof memo2);
	scanf("%d", &n);

	for (int i = 0; i < n; i++) scanf("%d", &v[i]);

	res = 0;
	for (int i = 0; i < n; i++) {
		int s = 0;
		for (int j = i; j < n; j++) {
			int p = upper_bound(sn, sn+s, -v[j]) - sn;
			s += (p == s);
			sn[p] = -v[j];
			res = max(p+1+dp(j+1,i)+inv(i-1,j), res);
		}
	}
	printf("%d\n", res);
}
