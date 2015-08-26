#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

int n, q, t, a, b, ini;

struct BIT {
	int qtd[N];

	int add (int i, int val) {
		for (; i <= n; i += (i&-i))
			qtd[i] += val;
	}

	int count (int i) {
		int res = 0;
		for (; i > 0; i -= (i&-i))
			res += qtd[i];
		return res;
	}
};
BIT tree;

int main () {
	scanf("%d %d", &n, &q);
	ini = n;

	for (int i = 1; i <= n; i++)
		tree.add(i, 1);
	
	for (int i = 0; i < q; i++) {
		scanf("%d", &t);
		if (t == 1) {
			scanf("%d", &a);
			for (int i = 0; i < a; i++)
				tree.add(ini-a-i, tree.count(ini-a+1+i)-tree.count(ini-a+i));
			ini = ini-a;
		} else {
			scanf("%d %d", &a, &b);
			printf("%d\n", tree.count(ini-a) - tree.count(ini-b) );
		}
		for (int i = 0; i < n; i++)
			printf("%d ", tree.count(i+1) - tree.count(i));
		printf("\n");
	}
}
