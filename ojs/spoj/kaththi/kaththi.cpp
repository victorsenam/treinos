#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+8;
const int mv[][2] = {
	{1,0}, {0,1}, {-1,0}, {0,-1}
};

struct pos {
	int i, j;
};

int t, r, c;
char mat[N][N];
int dist[N][N];

int main () {
	scanf("%d", &t);

	while (t--) {
		scanf("%d %d", &r, &c);

		for (int i = 0; i < r; i++) {
			scanf(" %s", mat[i]);
			for (int j = 0; j < c; j++)
				dist[i][j] = INT_MAX;
		}

		deque<pos> qu;
		dist[0][0] = 0;
		qu.push_back(pos({0,0}));

		while (!qu.empty()) {
			pos cur = qu.front();
			qu.pop_front();

			for (int k = 0; k < 4; k++) {
				pos nw = cur;
				nw.i += mv[k][0];
				nw.j += mv[k][1];

				if (nw.i < 0 || nw.i >= r || nw.j < 0 || nw.j >= c) continue;

				int nd = dist[cur.i][cur.j] + (mat[cur.i][cur.j] != mat[nw.i][nw.j]);

				if (nd < dist[nw.i][nw.j]) {
					dist[nw.i][nw.j] = nd;
					if (nd == dist[cur.i][cur.j])
						qu.push_front(nw);
					else
						qu.push_back(nw);
				}
			}
		}

		printf("%d\n", dist[r-1][c-1]);
	}
}
