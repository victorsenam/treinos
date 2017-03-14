#include <bits/stdc++.h>

using namespace std;

int n, p, res, w, cst, bud, av;

int main () {
	while (scanf("%d %d %d %d", &p, &bud, &n, &w) != EOF) {
		res = INT_MAX;
		for (int i = 0; i < n; i++) {
			scanf("%d", &cst);
			for (int j = 0; j < w; j++) {
				scanf("%d", &av);
				if (av >= p && cst*p <= bud)
					res = min(res, cst*p);
			}
		}

		if (res == INT_MAX)
			printf("stay home\n");
		else
			printf("%d\n", res);

	}
}
