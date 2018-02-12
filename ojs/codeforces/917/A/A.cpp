#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 5e3+7;

int memo[N][N];
char str[N];
int n;

int dp (int u, int q) {
	if (q < 0) return 0;
	int & me = memo[u][q];
	if (me != -1) return me;
	me = (q == 0);
	if (u == n) return me;
	if (str[u] != ')') me += dp(u+1, q+1);
	if (str[u] != '(') me += dp(u+1, q-1);
	return me;
}

int main () {
	memset(memo, -1, sizeof memo);
	scanf(" %s", str);
	n = strlen(str);

	int res = 0;
	for (int i = 0; i < n; i++) {
		int mn = 0, mx = 0;
		for (int j = i; j < n; j++) {
			if (str[j] == ')') { 
				mn--; mx--;
				if (mx < 0) break;
				if (mn < 0) mn += 2;
			} else if (str[j] == '(') { mn++; mx++; }
			else { if (mn > 0) { mn--; } else { mn++; } mx++; }
			if (mn == 0) res++;
		}
	}
	printf("%d\n", res);
}
