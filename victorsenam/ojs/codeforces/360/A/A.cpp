#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 5007;
const num MAXI = 1000000000;

num a[N];
bool mx[N];
int n, m;
num opr[N][4];
num val[N], used[N];
bool sol[N];

void fail () {
	printf("NO\n");
	exit(0);
}

void reverse (int k, int op) {
	if (opr[op][1] < k || opr[op][2] >= k)
		return;

	if (opr[op][0] == 1) {
		val[k] -= opr[op][3];
	} else {
		val[k] = min(val[k], opr[op][3]);
	}
}

bool apply (int k, int op) {
	if (op >= m)
		return 1;

	if (opr[op][1] < k || opr[op][2] >= k)
		return apply(k, op);

	if (opr[op][0] == 1) {
		val[k] += opr[op][3];
		if (val[k] >= MAXI || val[k] <= -MAXI || !apply(k, op+1)){
			val[k] -= opr[op][3];
			return 0;
		}
	} else {
		bool usedop = 0;
		if (val[k] == opr[op][3] && !sol[op]) {
			sol[op] = 1;
			usedop = 1;
		}
		if (val[k] > opr[op][3] || !apply(k, op+1)) {
			if (usedop)
				sol[op] = 0;
			return 0;
		}
	}
	return 1;
}

void restr (int op, int k) {
	if (used[k])
		return;

	val[k]= opr[op][3];
	used[k] = 1;
	for (int i = op-1; i >= 0; i--)
		reverse(k, i);

	if (!apply(k, 0))
		used[k] = 0;
}

int main ( ) {
	scanf("%d %d", &n, &m);

	for (int i = 0; i < m; i++) {
		scanf("%d %d %d %d", &opr[i][0], &opr[i][1], &opr[i][2], &opr[i][3]);
		opr[i][1]--;
	}

	for (int i = 0; i < m; i++) {
		if (opr[i][0] == 1)
			sol[i] = 1;
		else {
			for (int j = opr[i][1]; !sol[i] && j < opr[i][2]; j++)
				restr(i, j);
			if (!sol[i])
				fail();
		}
	}

	printf("YES\n");
	for (int i = 0; i < n; i++)
		printf("%d ", val[i]);
}
