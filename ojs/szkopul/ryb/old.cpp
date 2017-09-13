#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int dr[8][2] = {
	{0,-1},
	{-1,0},
	{0,1},
	{1,0},
	{-1,-1},
	{-1,1},
	{1,-1},
	{1,1}
};

typedef pair<int, pii> stru;

const int N = 1e3+7;
const int M = 1e4+7;

int h, w, n;
char mat[N][N];
int visi[N][N], turn;
int x, y, k;
char str[M];
map<vector<int>, int> cic;
map<vector<int>, vector<int> > com;
vector<int> lin[N];
int uf[N*N], wf[N*N];
int ttim[N][N];

inline int ctop (char c) {
	if (c == 'N')
		return 0;
	if (c == 'W')
		return 1;
	if (c == 'S')
		return 2;
	return 3;
}

int find (int u) {
	if (uf[u] == u) return u;
	return uf[u] = find(uf[u]);
}

void join (int u, int v) {
	if ((u = find(u)) == (v = find(v))) return;
	if (wf[u] > wf[v]) swap(u,v);
	uf[u] = v;
	wf[v] += wf[u];
}

int main () {
	scanf("%d %d", &h, &w);

	for (int i = 0; i < w; i++) {
		scanf(" %s", mat[i]);
	}

	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			if (mat[i][j] == '#') {
				uf[i*h+j] = i*h + j;
				wf[i*h+j] = 1;
			}

	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			if (mat[i][j] == '#') {
				for (int k = 0; k < 8; k++) {
					int ni = i + dr[k][0];
					int nj = j + dr[k][1];
					if (ni < 0 || ni >= w || nj < 0 || nj >= h || mat[ni][nj] != '#')
						continue;
					join(i*h+j,ni*h+nj);
				}
			}
	
	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
			if (mat[i][j] == '#' && uf[i*h+j] == i*h + j) {
				lin[i].pb(j);
			}

	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		cout << "Fish " << i + 1 << endl;
		turn++;
		scanf("%d %d %d %s", &x, &y, &k, str);
		x--; y--;

		int ts = 0;
		deque<stru> ps;
		vector<int> v;
		bool ign = 1;
		for (int j = 0; j < k; j++) {
			visi[y][x] = turn;
			ttim[y][x] = ts++;

			if (lin[y].size() && !ign) {
				int id = lower_bound(lin[y].begin(), lin[y].end(), x) - lin[y].begin() - 1;
				if (id == -1)
					id = -y - 1;
				else
					id = lin[y][id];

				if (ps.size() && id == ps.back().first)
					ps.pop_back();
				else
					ps.push_back(pair<int,pii>(id, pii(y,x)));
			}
			ign = 0;

			x += dr[ctop(str[j])][0];
			y += dr[ctop(str[j])][1];

			if (visi[y][x] == turn) {
				deque<stru> st;
				cout << "collision" << endl;
				ign = 1;

				while (ps.size()) {
					int cy = ps.back().second.first;
					int cx = ps.back().second.second;
					if (ttim[cy][cx] <= ttim[y][x]) break;
					cout << ps.back().first << "(" << ps.back().second.first << "," << ps.back().second.second << ")" << endl;
					st.push_front(ps.back());
					ps.pop_back();
				}
				if (st.size()%2)
					st.pop_front();
				while (!st.empty() && st.front().first == st.back().first) {
					st.pop_front();
					st.pop_back();
				}

				int mn = 0;
				for (int i = 1; i < st.size(); i++)
					if (st[i].second < st[mn].second)
						mn = i;

				while (mn--) {
					st.push_back(st.front());
					st.pop_front();
				}

				vector<int> cr(st.size());
				for (int i = 0; i < st.size(); i++) {
					cr[i] = st[i].first;
					cout << st[i].first << " ";
				}
				cout << endl;

				if (cr.empty()) continue;
				int & cc = cic[cr];
				if (cc == 0)
					cc = cic.size();
				v.pb(cc);
			}
		}
		
		com[v].pb(i);
	}

	printf("%d\n", (int) com.size());
	for (auto it : com) {
		for (int x : it.second)
			printf("%d ", x+1);
		printf("\n");
	}
}
