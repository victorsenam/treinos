#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX = 1010;

typedef pair<int, int> pii;

pii dp[MAX][MAX];
int vis[MAX][MAX], n;
pii v[MAX];

bool cmp(pii a, pii b) {
	if(a.first == b.first) return a.second < b.second;
	else return a.first > b.first;
}

pii f(int i, int p) {
	if(i == n) return {0, 0};
	if(!vis[i][p]) {
		vis[i][p] = 1;
		if(p == 0) dp[i][p] = {f(i + 1, p + 1).first, f(i + 1, p + 1).second + v[i].first};
		else dp[i][p] = max((pii){f(i + 1, p + 1).first, f(i + 1, p + 1).second + v[i].first}, (pii){f(i + 1, p - 1).first + v[i].second, f(i + 1, p - 1).second});
	}
	return dp[i][p];
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		memset(vis, 0, sizeof vis);
		char name[10];
		scanf(" %s", name);
		for(int i = 0; i < n; i++) {
			scanf("%d%d", &v[i].first, &v[i].second);
		}
		sort(v, v + n, cmp);
		if(name[0] == 'P') printf("%d %d\n", f(0, 0).second, f(0, 0).first);
		else printf("%d %d\n", f(0, 1).second, f(0, 1).first);
	}
	return 0;
}
