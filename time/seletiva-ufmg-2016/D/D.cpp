#include <bits/stdc++.h>

using namespace std;

const int N = 107;
const int INF = 1000;

int n, m;
int adj[N][N];


int main () {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			adj[i][j] = (i==j)?0:INF;

	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;

		adj[a][b] = min(adj[a][b], 1);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				int a = min(i, j);
				int b = max(i, j);
				adj[a][b] = min(
					adj[a][b], 
					adj[min(i, k)][max(i, k)] + 
					adj[min(j, k)][max(j, k)]
				);
			}
		}
	}
	int maxi = 0;
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			maxi = max(adj[i][j], maxi);

	if (maxi > 6)
		printf("N\n");
	else
		printf("S\n");
}
