#include <bits/stdc++.h>

const int N = 32007;

int freq[N];
struct BIT {
	int qtd[N];

	void inc (int i) {
		for (; i < N; i += (-i&i))
			qtd[i]++;
	}

	int cnt (int i) {
		int res = 0;
		for (; i > 0; i -= (-i&i))
			res += qtd[i];
		return res;
	}
};
BIT tree;

int main () {
	int n, x, y;

	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d %d", &x, &y);
		freq[tree.cnt(x+1)]++;
		tree.inc(x+1);
	}

	for (int i = 0; i < n; i++) {
		printf("%d\n", freq[i]);
	}
}
