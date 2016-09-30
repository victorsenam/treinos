#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 32;
const int M = 2e3;

int visi[N][N][N][N], turn;
int seen[N][N][N][N];
ll dist[N][N][N][N];

struct node {
	int v[4];
	int d;
	
	ll & dist () {
		if (::visi[v[0]][v[1]][v[2]][v[3]] == turn)
			::dist[v[0]][v[1]][v[2]][v[3]] = LLONG_MAX;
		return ::dist[v[0]][v[1]][v[2]][v[3]];
	}

	int & seen () {
		return seen[v[0]][v[1]][v[2]][v[3]];
	}

	bool operator < (const node & ot) const {
		if (d != ot.d) return d < ot.d;
		for (int i = 0; i < 4; i++)
			if (v[i] != ot.v[i])
				return v[i] < ot.v[i];
		return 1;
	}
};

vector<pair<int, ll> > adj[N];
int s[4];
int n, m;
priority_queue<node> pq;
map<string, int> mp;
char str[N];

int main () {
	while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
		int qt = 0;

		for (int i = 0; i < n; i++) {
			scanf(" %s", str);

			mp[str] = qt++;
		}

		es = 2;

		for (int i = 0; i < m; i++) {
			scanf(" %s", str);
			int a = mp[str];
			scanf(" %s", str);
			int b = mp[str];

            pair<int, ll> ed;
            scanf("%lld", &ed.second);

            ed.first = b;
            adj[a].push_back(ed);
            ed.first = a;
            adj[b].push_back(ed);
		}

        for (int i = 0; i < n; i++)
            sort(adj[i].begin(), adj[i].end());

		node stt;
		for (int i = 0; i < 4; i++) {
			scanf(" %s", str);
			stt.v[i] = mp[str];
			scanf(" %s", str);
			s[i] = mp[str];
		}

		stt.d = stt.dist() = 0;
		pq.push(stt);
		
		while (!pq.empty()) {
			node curr = pq.top();
			pq.pop();

			if (curr.seen() == turn)
                continue;
            curr.seen() = turn;

            int p[4] = {0, 0, 0, 0};

		}
	}
}
