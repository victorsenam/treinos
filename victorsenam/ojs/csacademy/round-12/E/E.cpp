#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

//#define debug(...) {fprintf(stderr, __VA_ARGS__);}
#define debug(...) {}

const int N = 1e6+7;
const ll MOD = 1e9+7;

char str[2][N];
int n;
int k;
int z[N];

ll memo[N][2];

ll pd (int i, bool pr) {
	if (i == n)
		return 1ll;

	ll & me = memo[i][pr];

	if (me != -1) return me;
	me = 0;

	char a = 0;
	char b = 0;
	char lc = '0';
	char gc = '9';
	if (i < k)
		a = str[1][i];
	if (i + k >= n) {
		b = str[1][i-n+k];
	}

	if (a && b && a != b) return me;
	if (a || b) lc = gc = max(a, b);
	
	for (char x = lc; x <= gc; x++) {
		if (x < str[0][i] || pr)
			me = (me + pd(i+1, 1))%MOD;
		else if (x == str[0][i])
			me = (me + pd(i+1, pr))%MOD;
		else
			break;
	}
	return me;
}

void calcz () {
	int L = 0, R = 0;
	for (int i = 1; i < k; i++) {
		if (i > R) {
			L = R = i;
			while (R < k && str[1][R-L] == str[1][R]) R++;
			z[i] = R-L; R--;
		} else {
			int c = i-L;
			if (z[c] < R-i+1) z[i] = z[c];
			else {
				L = i;
				while (R < k && str[1][R-L] == str[1][R]) R++;
				z[i] = R-L; R--;
			}
		}
	}
	z[k] = 0;
}

int main () {
	memset(memo, -1, sizeof memo);
	scanf(" %s %s", str[0], str[1]);

	n = strlen(str[0]);
	k = strlen(str[1]);

	if (k > n) {
		printf("0\n");
		return 0;
	}

	calcz();

	ll res = (k < n);

	for (int i = 1; i <= k && i + k < n; i++) {
		if (i + z[i] == k) {
			res++;
		}
	}

	ll summ = 10;
	for (int i = k + k + 1; i < n; i++)  {
		res = (res + summ)%MOD;
		summ = (summ * 10)%MOD;
	}


	res = (res + pd(0, 0))%MOD;

	printf("%lld\n", res);
}
