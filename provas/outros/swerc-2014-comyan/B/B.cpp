#include <bits/stdc++.h>

using namespace std;

const int N = 10003;
const int M = 2*250003;

int hd[N], nx[M], to[M], wg[M], ds[M], es;
int dist[N];
int visi[N];
char used[M];
int n, m;
int a, b, d;

struct edge {
	int i;
	int p;
	bool operator < (const edge & a) const {
		return p > a.p;
	}
};

int main () {
	while (scanf("%d %d", &n, &m) != EOF) {
		priority_queue<edge> pq;
		queue<int> q;

		memset(used, 0, sizeof used);
		memset(visi, 0, sizeof visi);
		memset(hd, -1, sizeof hd);
		for (int i = 0; i < n; i++)
			dist[i] = INT_MAX;
		
		es = 0;
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &d);
			nx[es] = hd[a]; hd[a] = es; to[es] = b; wg[es] = d; ds[es] = INT_MAX; es++;
			nx[es] = hd[b]; hd[b] = es; to[es] = a; wg[es] = d; ds[es] = INT_MAX; es++;
		}

		edge aux;
		aux.i = 0;
		aux.p = 0;
			pq.push(aux);

		while (!pq.empty()) {
			edge att = pq.top();
			pq.pop();

			if (visi[att.i])
				continue;
			dist[att.i] = att.p;
			visi[att.i] = 1;

			for (int ed = hd[att.i]; ed != -1; ed = nx[ed]) {
				edge aux;
				aux.i = to[ed];
				aux.p = att.p + wg[ed];

				pq.push(aux);
			}
		}

		q.push(n-1);
		memset(visi, 0, sizeof visi);

		int res = 0;
		while (!q.empty()) {
			int att = q.front();
			q.pop();
			
			for (int ed = hd[att]; ed != -1; ed = nx[ed]) {
				if (dist[to[ed]] + wg[ed] == dist[att]) {
					used[ed] = 1;
					if (!visi[to[ed]]) {
						visi[to[ed]] = 1;
						q.push(to[ed]);
					}
				}
			}
		}

		for (int i = 0; i < 2*m; i+=2) {
			if (used[i] || used[i^1]) {
				res += wg[i];
			}
		}
		printf("%d\n", 2*res);
	}
}
