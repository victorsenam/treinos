#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int dist[112][112];

int main () {
	int i, n, k, j;
	scanf("%d %d", &n, &k);
	memset(dist, 0x3f3f3f3f, sizeof dist);
	for(i = 0; i < n; i++) dist[i][i] = 0;
	while(k--) {
		int a, b, l;
		scanf("%d %d %d", &a, &b, &l);
		a--; b--;
		dist[a][b] = min(dist[a][b], l);
	}
	for(int k = 0; k < n; k++)
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
	ll tot = 0;
	ll count = 0;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++) {
			if(i == j || dist[i][j] > 100 * 1000) continue;
			count++;
			tot += dist[i][j];
		}
	printf("%.6f\n", double(tot) / count);
}
