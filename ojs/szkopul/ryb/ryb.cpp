#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+7;
const int M = 1e4+7;

int dr[8][2] = {
	{-1, 0},
	{0,1},
	{1,0},
	{0,-1},
	{-1,-1},
	{-1,1},
	{1,-1},
	{1,1}
};

char mat[N][N];
char str[M];
int n, m, q;
int i, j, k;
int val[N][N], vs;
int visi[N][N], turn;

map<vector<int>, vector<int> > mp;
map<deque<int>, int> cyc;

char ctod (char c) {
	if (c == 'N')
		return 0;
	else if (c == 'E')
		return 1;
	else if (c == 'S')
		return 2;
	else
		return 3;
}

void get (int i, int j, int nw = 1) {
	if (i < 0 || i >= n || j < 0 || j >= m || visi[i][j] || mat[i][j] != '#')
		return;
	visi[i][j] = 1;
	if (nw)
		val[i][j] = ++vs;
	for (int k = 0; k < 8; k++)
		get(i + dr[k][0], j + dr[k][1], 0);
}

int main () {
	scanf("%d %d", &m, &n);

	for (int i = 0; i < n; i++)
		scanf(" %s", mat[i]);
	
	for (int i = 0; i < n; i++) {
		int ls = vs;
		for (int j = 0; j < m; j++) {
			val[i][j] = val[i][j-!!j];
			get(i,j);
		}

		if (ls != vs) {
			vs++;
			for (int j = 0; j < m; j++)
				if (val[i][j] == 0)
					val[i][j] = vs;
		}
	}

	scanf("%d", &q);

	turn = 2;
	for (int qq = 1; qq <= q; qq++) {
		vector<int> v;
		turn++;
		scanf("%d %d %d", &j, &i, &k);
		i--; j--;
		scanf(" %s", str);

		stack<pii> st;
		for (int p = 0; p < k; p++) {
			int dt = ctod(str[p]);
			st.push(pii(i,j));
			visi[i][j] = turn;
			
			i += dr[dt][0]; j += dr[dt][1];

			if (visi[i][j] != turn) continue;

			deque<pii> dq;
			deque<int> ev;

			while (visi[i][j] == turn) {
				pii cur = st.top();
				st.pop();
				visi[cur.first][cur.second] = 0;
				dq.push_back(cur);
			}
			
			int mn = 0;
			for (int cand = 1; cand < dq.size(); cand++) {
				if (dq[cand] < dq[mn])
					mn = cand;
			}

			while (mn--) {
				dq.push_back(dq.front());
				dq.pop_front();
			}

			for (int c = 0; c < dq.size(); c++) {
				pii a = dq[c];
				pii b = dq[(c+dq.size()-1)%dq.size()];

				if (a.first == b.first) continue;
				
				int pi = max(a.first, b.first);
				int pj = a.second;

				if (val[pi][pj] == 0) continue;
				int vl = val[pi][pj];
				if (ev.size() && ev.back() == vl)
					ev.pop_back();
				else
					ev.push_back(vl);
			}

			while (ev.size() && ev.front() == ev.back()) {
				ev.pop_front();
				ev.pop_back();
			}

			if (ev.empty()) continue;
			int & id = cyc[ev];
			if (id == 0)
				id = cyc.size();
			v.pb(id);
		}

		mp[v].pb(qq);
	}

	printf("%d\n", (int) mp.size());
	for (auto el : mp) {
		for (int x : el.second)
			printf("%d ", x);
		printf("\n");
	}
}
