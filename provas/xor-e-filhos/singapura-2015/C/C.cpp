#include <bits/stdc++.h>

using namespace std;

const int N = 200007;
const int M = 600007;

int n, m;
int uf[M], wf[M];
int v[M];

int find (int i ) {
	if (i == uf[i]) return i;
	return uf[i] = find(uf[i]);
}

void join (int i, int j) {
	if ((i = find(i)) == (j = find(j))) return;
	if (wf[i] < wf[j]) swap(i, j);
	wf[i] += wf[j];
	uf[j] = i;
}

int main () {
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < M; i++) {
			uf[i] = i;
			wf[i] = 1;
		}
		int res= 0;

		for (int i = 0; i < n; i++) {
			scanf("%d", &m);

			set<int> s;
			int a;
			int sum = 0;
			for (int j = 0; j < m; j++) {
				scanf("%d", v+j);
				a = find(v[j]);
				if (s.find(a) == s.end())
					sum += wf[a];
				s.insert(a);
			}

			if (sum == m) {
				res++;
				for (int j = 1; j < m; j++)
					join(v[0], v[j]);
			}
		}

		printf("%d\n", res);
	}
}
