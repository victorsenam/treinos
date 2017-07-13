#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e6+7;

const int mv[4][2] = {
	{-1, 0},
	{0, 1},
	{1, 0},
	{0, -1}
};

vector<vector<char> > mat;
vector<vector<vector<vector<int> > > > mrk;
vector<vector<vector<int> > > sm;
vector<vector<bool> > res;
int n, m, k;
string cm[N];
ll qt[N];
ll cnt;

int getdir (int i) {
	if (cm[i][0] == 'u')
		return 0;
	if (cm[i][0] == 'r')
		return 1;
	if (cm[i][0] == 'd')
		return 2;
	if (cm[i][0] == 'l')
		return 3;
	assert(false);
}

void printa () {
	cout << "=============" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (res[i][j])
				cout << "#";
			else
				cout << ".";
		}
		cout << endl;
	}
	cout << endl;

	for (int a = 0; a < 2; a++) {
	for (int b = 0; b < 2; b++) {
		cout << endl;
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= m; j++) {
				cout << mrk[a][b][i][j] << " ";
			}
			cout << endl;
		}
	}
	}
}

void add (int p, int d, ll & i, ll & j, ll k) {
	if (d == 0) { // up
		mrk[i+1][j][p][0]--;
		mrk[i-k][j][p][0]++;
	} else if (d == 1) { // right
		mrk[i][j][p][1]++;
		mrk[i][j+k+1][p][1]--;
	} else if (d == 2) { // down
		mrk[i][j][p][0]++;
		mrk[i+k+1][j][p][0]--;
	} else { // left
		mrk[i][j+1][p][1]--;
		mrk[i][j-k][p][1]++;
	}

	//cout << p << " from " << i << "," << j << " : ";

	i += mv[d][0]*k;
	j += mv[d][1]*k;
	//cout << i << "," << j << endl;
}

ll solve (ll x) {
    for (int i = 0; i < n; i++)
        for (int a = 0; a < 2; a++)
			sm[i][a][1] = 0;
    for (int j = 0; j < m; j++)
        for (int a = 0; a < 2; a++)
			sm[j][a][0] = 0;

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int a = 0; a < 2; a++)
                for (int b = 0; b < 2; b++)
                    mrk[i][j][a][b] = 0;
	 

	ll i = n-1;
	ll j = 0;

	ll y = 0;
	bool p = 1;
	for (int z = 0; z < k; z++) {
		int d = getdir(z);
		if (p && y + qt[z] >= x) {
			add(1, d, i, j, x - y);
			add(0, d, i, j, y + qt[z] - x);
			p = 0;
		} else {
			add(p, d, i, j, qt[z]);
		}

		y += qt[z];
	}

	ll c = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int a = 0; a < 2; a++) {
				sm[j][a][0] += mrk[i][j][a][0];
				sm[i][a][1] += mrk[i][j][a][1];
			}
			res[i][j] = (!sm[j][0][0] && !sm[i][0][1] && (sm[j][1][0] || sm[i][1][1]));
			c += res[i][j];
		}
		//cout << endl;
	}
	//printa();
	return c;
}

ll bb (ll lo, ll hi, ll x) {
	ll cc = 0;

	while (lo < hi) {
		ll md = (lo+hi)/2;

		if (solve(md) < x)
			lo = md + 1;
		else
			hi = md;
	}

	return lo;
}

void fail () {
	cout << "-1 -1" << endl;
	exit(0);
}

int main () {
	cin >> n >> m >> k;

    mat = vector<vector<char> >(n+2, vector<char>(m+2));
    res = vector<vector<bool> >(n+2, vector<bool>(m+2));

    mrk = vector<vector<vector<vector<int> > > >(n+2,
            vector<vector<vector<int> > >(m+2,
            vector<vector<int> >(2,
            vector<int>(2))));
    
    sm = vector<vector<vector<int> > >(n+m,
            vector<vector<int> >(2,
            vector<int>(2)));

	cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> mat[i][j];
			if (mat[i][j] == '#')
				cnt++;
		}
	}

	ll qtd = 1;
	for (int i = 0; i < k; i++) {
		cin >> cm[i] >> qt[i];
		qtd += qt[i];
	}
	
	ll l = bb(0, qtd, cnt);
	ll r = bb(l, qtd, cnt+1);

	solve(l);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if ((mat[i][j] == '#') != res[i][j])
				fail();
		}
	}
	//printa();
	cout << l << " " << max(l,r-1) << endl;
}

