#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+7;
const int M = 2e4+7;

const ll P = 1e6+3;
const ll MOD = 1e9+7;

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

inline ll mod (ll x) {
	return ((x%MOD) + MOD)%MOD;
}

char mat[N][N];
char str[M];
int n, m, q;
int i, j, k;
int val[N][N], vs;
int visi[N][N], turn;
vector<int> res[N];

int sa_p[M+M];
pii sa_r[M+M];

struct hashed {
	ll val;
	int n;
	ll p;

	hashed () {
		p = 1;
		val = 0;
		n = 0;
	}

	void add (ll x) {
		if (x < 0) x = vs - x;
		p = mod(p*P);
		val = mod(val*P);
		val = mod(val + x);
		n++;
	}

	void sub (ll fr, ll to) {
		if (fr < 0) fr = vs - fr;
		if (to < 0) to = vs - to;
		val = mod(val*P);
		val = mod(val - mod(fr*p));
		val = mod(val + to);
	}

	bool operator < (const hashed & that) const {
		if (n != that.n)
			return n < that.n;
		return val < that.val;
	}
};

map<hashed, int> mp;

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

int getshift (deque<int> & ev) {
	int s = ev.size();
	int n = s + s;
	if (n == 0) return 0;

	for (int i = 0; i < n; i++) {
		sa_p[i] = i;
		sa_r[i].first = ev[i%s];
	}

	for (int k = 1; k < n; k += k) {
		for (int i = 0; i < n; i++) {
			if (i + k >= n)
				sa_r[i].second = -1;
			else
				sa_r[i].second = sa_r[i+k].first;
		}

		sort(sa_p, sa_p+n, [] (int i, int j) {
			return sa_r[i] < sa_r[j];
		});

		pii ls(-1,-1);
		int rn = -1;
		for (int _i = 0; _i < n; _i++) {
			int i = sa_p[_i];
			pii nx = sa_r[i];
			if (nx == ls)
				sa_r[i].first = rn;
			else
				sa_r[i].first = ++rn;
			ls = nx;
		}
	}

	for (int i = 0; i < n; i++)
		if (sa_p[i] < s)
			return sa_p[i];
	assert(false);
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

	assert(vs < P);

	scanf("%d", &q);

	turn = 2;
	for (int qq = 1; qq <= q; qq++) {
		vector<int> v;
		turn++;
		scanf("%d %d %d", &j, &i, &k);
		i--; j--;
		scanf(" %s", str);

		deque<int> ev;
		for (int p = 0; p < k; p++) {
			int dt = ctod(str[p]);
			int ni = i + dr[dt][0], nj = j + dr[dt][1];
			if (i != ni) {
				int pi = max(i,ni);
				int pj = j;
				int vl = val[pi][pj];
				if (pi == i)
					vl = -vl;

				if (val[pi][pj]) {
					if (ev.size() && ev.back() == -vl)
						ev.pop_back();
					else
						ev.push_back(vl);
				}
			}
			i = ni; j = nj;
		}
		while (ev.size() && ev.front() == -ev.back()) {
			ev.pop_front();
			ev.pop_back();
		}

		hashed h, mn;
		for (int i = 0; i < ev.size(); i++) {
			h.add(ev[i]);
			cout << ev[i] << " ";
		}
		mn = h;
		cout << ": " << mn.val << " ";
		for (int i = 0; i < ev.size(); i++) {
			h.sub(ev[i], ev[i]);
			if (h < mn)
				mn = h;
			cout << h.val << " ";
		}
		cout << endl;


		int & pp = mp[mn];
		if (pp == 0)
			pp = mp.size();
		res[pp].pb(qq);
	}

	printf("%d\n", (int) mp.size());
	for (int i = 1; i <= mp.size(); i++) {
		for (int x : res[i])
			printf("%d ", x);
		printf("\n");
	}
}
