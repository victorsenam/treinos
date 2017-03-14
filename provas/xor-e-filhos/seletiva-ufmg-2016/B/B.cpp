#include <bits/stdc++.h>

using namespace std;

const int N = 1007;

int n;
int a[N], b[N];
int memo[N][2][2];
int visi[N][2][2];

int solve () {
	int c = 0;
	for (int i = 2; i <= n; i++) {
		if (b[i-1] == 0) {
			for (int j = i-1; j <= i && j <= n; j++)
				b[j] = !(b[j]);
			c++;
		}
	}

	if (b[n]) return c;
	else return N;
}

int main () {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", a+i);

		b[i] = a[i];
	}
	
	b[n+1] = 1;

	int res = N;

	res = min(solve(), res);

	if (res == N)
		printf("-1\n");
	else
		printf("%d\n", res);
}
