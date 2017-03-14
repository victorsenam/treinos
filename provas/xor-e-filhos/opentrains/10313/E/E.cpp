#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1607;
const int K = 27;

double curr[N];
int visi[N], turn;
int st[N*K], ss;

inline double sq (double a) {
	return a * a;
}

struct vtx {
	int u;
	double x, y;
	int fr;

	double & curr () {
		if (visi[u] != turn)
			::curr[u] = 1./0.;
		visi[u] = turn;
		return ::curr[u];
	}

	double dist (const vtx & ot) {
		return sqrt(sq(x-ot.x) + sq(y-ot.y));
	}
};

int n, m, k;
int p[N];
int a, b;
vtx v[N];
double vr, vf;
bool adj[N][N];

void rebuild (int a) {
	if (v[a].fr == a) return;
	rebuild(v[a].fr);
	st[ss++] = a;
}

double solve (int u, int to) {
	turn++;
	v[u].curr() = 0;
	
	for (int _u = n-1; _u >= 0; _u--) {
		for (int j = 0; j < _u; j++) {
			if (v[p[j]].curr() < v[p[_u]].curr())
				swap(p[j], p[_u]);
		}

		u = p[_u];

		if (u == to) break;

		for (int _j = 0; _j < _u; _j++) {
			int j = p[_j];
			double loc = v[u].curr();
			if (adj[u][j]) {
				loc += v[u].dist(v[j])/vr;
			} else {
				loc += v[u].dist(v[j])/vf;
			}

			if (loc < v[j].curr()) {
				v[j].curr() = loc;
				v[j].fr = u;
			}
		}
	}

	rebuild(to);
	return v[to].curr();
}

int main () {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d %d %d %lf %lf", &n, &m, &k, &vr, &vf);
	ss = 0;

	for (int i = 0; i < n; i++) {
		v[i].u = i;
		scanf("%lf %lf", &v[i].x, &v[i].y);
		p[i] = i;
	}
	
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		a--; b--;
		adj[a][b] = adj[b][a] = 1;
	}

	a = 0;
	double res = 0.;
	for (int i = 0; i <= k; i++) {
		if (i < k) scanf("%d", &b);
		else b = n;
		b--;

		for (int j = 0; j < n; j++)
			v[j].fr = j;
		res += solve(a, b);
		a = b;
	}

	printf("%.20f\n", res);
	printf("1");
	for (int i = 0; i < ss; i++)
		printf(" %d", st[i]+1);
	printf("\n");
}
