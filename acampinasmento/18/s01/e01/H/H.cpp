#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int dist[112][112];

int di[] = {1, -1, 1, -1};
int dj[] = {1, -1, -1, 1};
int N, M;

pii lst[112][112];

void go(pii x, queue<pii> &qq, int p, int q) {
	for(int d = 0; d < 4; d++) {
		pii y(x.first + p * di[d], x.second + q * dj[d]);
		if(y.first < 0 || y.first >= M || y.second < 0 || y.second >= N) continue;
		if(dist[y.first][y.second] != -1) continue;
		dist[y.first][y.second] = dist[x.first][x.second] + 1;
		lst[y.first][y.second] = x;
		qq.push(y);
	}
}

int main () {
	int p, q, x1, y1, x2, y2;
	cin >> M >> N >> p >> q >> x1 >> y1 >> x2 >> y2;
	memset(dist, -1, sizeof dist); x1--; y1--; x2--; y2--;
	dist[x1][y1] = 0;
	queue<pii> qq;
	qq.push(pii(x1, y1));
	lst[x1][y1] = pii(-1, -1);
	while(!qq.empty()) {
		pii x = qq.front(); qq.pop();
		go(x, qq, p, q);
		go(x, qq, q, p);
	}
	printf("%d\n", dist[x2][y2]);
	if(dist[x2][y2] == -1) return 0;
	vector<pii> path;
	pii x(x2, y2);
	while(x.first != -1) {
		path.pb(x);
		x = lst[x.first][x.second];
	}
	while(!path.empty()) {
		printf("%lld %lld\n", path.back().first + 1, path.back().second + 1);
		path.pop_back();
	}
}
