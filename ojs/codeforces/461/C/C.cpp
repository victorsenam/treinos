#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

int n, q, t, a, b, ini, fim;
bool fli;

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

	int foldleft (int ini, int a) {
		for (int i = 0; i < a; i++)
			add(ini+a+i, count(ini+a-1-i) - count(ini+a-2-i));
		return ini+a;
	}

	int foldright (int fim, int a) {
		for (int i = 0; i < a; i++)
			add(fim-a-i, count(ini-a+1+i) - count(ini-a+i));
		return fim-a;
	}
};
BIT tree;

int main () {
	scanf("%d %d", &n, &q);
	n++;
	ini = 1;
	fim = n-1;
	fli = 0;

	for (int i = 1; i <= n; i++)
		tree.add(i, 1);
	for (int i = 0; i < n; i++)
		printf("%d ", tree.count(i+1) - tree.count(i));
	printf("\n");
	
	for (int i = 0; i < q; i++) {
		scanf("%d", &t);
		if (t == 1) {
			scanf("%d", &a);
			if (a > (fim-ini+1)/2) {
				a -= (fim-ini+1)/2;
				fli = !fli;
			}

			if (fli)
				fim = tree.foldright(fim, a);
			else
				ini = tree.foldleft(ini, a);
		} else {
			scanf("%d %d", &a, &b);

			if (fli) {
				a = fim - a;
				b = fim - b;
				swap(a,b);
			} else {
				a = ini + a - 1;
				b = ini + b - 1;
			}

			printf("[%d, %d] %d\n", a, b, tree.count(b) - tree.count(a));
		}

		for (int i = 1; i <= n; i++) {
			if (i < ini || i > fim) printf("x ");
			else printf("%d ", tree.count(i) - tree.count(i-1));
		}
		printf("\n");
	}
}
