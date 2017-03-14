#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

//#define debug(...) {fprintf(stderr, __VA_ARGS__);}
#define debug(...) {}

const int N = 32;
const int M = 2e3;

int visi[N][N][N][N], turn;
int seen[N][N][N][N];
ll dist[N][N][N][N];

struct node {
	int v[4];
	ll d;
	
	ll & dist () {
		if (::visi[v[0]][v[1]][v[2]][v[3]] != turn) {
			::dist[v[0]][v[1]][v[2]][v[3]] = LLONG_MAX;
            ::visi[v[0]][v[1]][v[2]][v[3]] = turn;
        }
		return ::dist[v[0]][v[1]][v[2]][v[3]];
	}

	int & seen () {
		return ::seen[v[0]][v[1]][v[2]][v[3]];
	}

	bool operator < (const node & ot) const {
		if (d != ot.d) return d < ot.d;
		for (int i = 0; i < 4; i++)
			if (v[i] != ot.v[i])
				return v[i] < ot.v[i];
		return 1;
	}

    void print () {
        for (int k = 0; k < 4; k++)
            debug("%d ", v[k]);

        debug("[%lld]\n", dist());
    }
};

vector<pair<int, ll> > adj[N];
int edge[M][2];
node t;
int n, m;
priority_queue<node> pq;
map<string, int> mp;
char str[N];
int p[4];

int transfer (int from, int to) {
    int i = 1;
    int j = 1;
    int res = 0;

    //debug("from %d to %d\n", from, to);
    while (j <= from) {
        while (i <= to && !(to&i))
            i <<= 1;
        if (i > to) {
            //debug("fails\n");
            return 0;
        }

        if (from&j)
            res |= i;

        i <<= 1;
        j <<= 1;
    }

    //debug("gets %d\n", res);
    return res;
}

pair<int, ll> get_next_edge (node curr) {
    pair<int, ll> res = pair<int, ll>(m, LLONG_MAX);
    for (int k = 0; k < 4; k++) {
        if (p[k] < adj[curr.v[k]].size()) {
            debug("%d -> (%d,%d) [%lld]\n", curr.v[k], edge[adj[curr.v[k]][p[k]].first][0], edge[adj[curr.v[k]][p[k]].first][1], adj[curr.v[k]][p[k]].second);
            res = min(adj[curr.v[k]][p[k]], res);
        }
    }
    return res;
}

int main () {
	while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
        mp.clear();
        turn++;
		int qt = 0;

		for (int i = 0; i < n; i++) {
			scanf(" %s", str);

			mp[str] = qt++;
            adj[i].clear();
		}

		for (int i = 0; i < m; i++) {
			scanf(" %s", str);
			int a = mp[str];
			scanf(" %s", str);
			int b = mp[str];

            pair<int, ll> ed;
            ed.first = i;
            scanf("%lld", &ed.second);

            edge[i][0] = a;
            edge[i][1] = b;

            adj[a].push_back(ed);
            adj[b].push_back(ed);
		}

        for (int i = 0; i < n; i++)
            sort(adj[i].begin(), adj[i].end());

		node stt;
		for (int i = 0; i < 4; i++) {
			scanf(" %s", str);
			stt.v[i] = mp[str];
			scanf(" %s", str);
			t.v[i] = mp[str];

            if (stt.v[i] > t.v[i])
                swap(stt.v[i], t.v[i]);
		}

		stt.d = stt.dist() = 0;
		pq.push(stt);
		
		while (!pq.empty() && t.seen() != turn) {
			node curr = pq.top();
			pq.pop();

			if (curr.seen() == turn)
                continue;
            curr.seen() = turn;

            curr.print();

            for (int k = 0; k < 4; k++)
                p[k] = 0;
            
            pair<int, ll> cr = get_next_edge(curr);
            while (cr < pair<int, ll>(m, LLONG_MAX)) {
                debug("edge (%d,%d) [%lld]\n", edge[cr.first][0], edge[cr.first][1], cr.second);
                int valid = 0;

                for (int k = 0; k < 4; k++)
                    if (p[k] < adj[curr.v[k]].size() && cr == adj[curr.v[k]][p[k]]) {
                        valid |= (1<<k);
                        debug("%d\n", k);
                        p[k]++;
                    }

                node nxt = curr;
                nxt.d += cr.second;
                
                for (int _msk = 1;; _msk++) {
                    int msk = transfer(_msk, valid);
                    if (!msk) break;
                    for (int k = 0; k < 4; k++)
                        if (msk&(1<<k))
                            nxt.v[k] = edge[cr.first][(edge[cr.first][0] == curr.v[k])];
                        else
                            nxt.v[k] = curr.v[k];

                    if (nxt.dist() <= nxt.d) continue;
                    nxt.dist() = nxt.d;

                    pq.push(nxt);
                }
                cr = get_next_edge(curr);
            }
		}
        while (!pq.empty())
            pq.pop();

        t.print();

        printf("%lld\n", t.dist());
	}
}
