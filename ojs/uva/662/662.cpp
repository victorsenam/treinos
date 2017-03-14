#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 203;
const int K = 37;

num memo[N][K];
int cen[N][K];
int to[N][K];
int n, k;
num d[N];
num ls[N];

inline num price(int i, int j, int c) {
	if (c > j)
		return LLONG_MAX;

	return (2ll*(num)c-(num)i-(num)j)*d[c] + ls[j+1] - ls[c+1] - ls[c] + ls[i];
}

num solve (int i, int k) {
	if (i == n)
		return 0;
	if (k == 0)
		return LLONG_MAX;
	
	num & m = memo[i][k];
	if (m != -1)
		return m;
	
	int c = i;

	m = LLONG_MAX;
	
	for (int j = i; j < n; j++) {
		num res = price(i, j, c);
		num resb = price(i, j, c+1);

		while (resb < res) {
			c++;
			res = resb;
			resb = price(i, j, c+1);
		}

		res = max(res + solve(j+1, k-1), max(res, solve(j+1, k-1)));

		if (m > res) {
			to[i][k] = j;
			cen[i][k] = c;
			m = res;
		}
	}

	return m;
}

int main () {
	int ts = 0;
	while (scanf("%d %d", &n, &k) != EOF && (n || k)) {
		for (int i = 0; i < n; i++)
			scanf("%lld", d+i);
		
		ls[0] = 0;
		for (int i = 0; i < n; i++) {
			ls[i+1] = ls[i] + d[i];
			for (int j = 0; j <= k; j++) {
				memo[i][j] = -1;
			}
		}

		num ans = solve(0, k);

		printf("Chain %d\n", ++ts);

		int ini = 0;
		int dep = 0;
		while (ini < n) {
			if (ini == to[ini][k])
				printf("Depot %d at restaurant %d serves restaurant %d\n", ++dep, cen[ini][k]+1, ini+1);
			else
				printf("Depot %d at restaurant %d serves restaurants %d to %d\n", ++dep, cen[ini][k]+1, ini+1, to[ini][k]+1);
			ini = to[ini][k]+1;
			k--;
		}
		printf("Total distance sum = %lld\n\n", ans);
	}
}
