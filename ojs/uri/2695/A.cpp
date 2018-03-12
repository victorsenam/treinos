#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef double cood; cood eps = 1e-8;
struct vec {
	cood x, y;
	vec() : x(0),y(0) {} vec(cood a, cood b) : x(a), y(b) {}
	inline vec operator - (vec o) { return {x - o.x, y-o.y}; }
	inline vec operator + (vec o) { return {x + o.x, y+o.y}; }
	inline cood operator ^ (vec o) { return x*o.y - y*o.x; }
	inline cood operator * (vec o) { return x*o.x + y*o.y; }
	inline cood cross (vec a, vec b) { return ((*this)-a)^((*this)-b); }
	inline cood inner (vec a, vec b) { return ((*this)-a)*((*this)-b); }
	inline int ccw (vec a, vec b) { cood o = cross(a,b); return (eps < o) - (o < -eps); }
	inline int dir (vec a, vec b) { cood o = inner(a,b); return (eps < o) - (o < -eps); }
	vec rot90 () { return {-y,x}; }

	bool in_seg (vec a, vec b) { return ccw(a,b) == 0 && dir(a,b) <= 0; }
};
bool inter_seg (vec a, vec b, vec c, vec d) {
	if (a.in_seg(c,d) || b.in_seg(c,d) || c.in_seg(a,b) || d.in_seg(a,b)) return true;
	return (c.ccw(a,b) * d.ccw(a,b) == -1 && a.ccw(c,d) * b.ccw(c,d) == -1);
}
struct lin {
	vec p; cood c;
	lin () {} lin (vec a, cood b) : p(a), c(b) {}
	lin (vec s, vec t) : p((s-t).rot90()), c(p*s) {}
	inline lin parll (vec v) { return lin(p,v*p); }
	inline lin perp () { return lin(p.rot90(),c); }
	vec at_y (cood y) { return vec((c-y*p.y)/p.x,y); }
};

double get (vec a, vec b, vec c, vec d, double & res) {
	for (double y : {a.y,b.y,c.y,d.y}) {
		vec v = lin(a,b).at_y(y); if (y + eps < a.y || b.y + eps < y) continue;
		vec u = lin(c,d).at_y(y); if (y + eps < c.y || d.y + eps < y) continue;
		res = min(res, u.x - v.x);
	}
}

const int N = 14;
int n;
vector<vec> lf[N], rg[N];
double dist[N][N];
double res[(1<<N)][N];

double coll (int a, int b) {
	double res = 1./0.;
	int i = 0;
	for (int j = 0; j < lf[b].size() - 1; j++) {
		for (; i < rg[a].size() - 1 && rg[a][i+1].y < lf[b][j+1].y; i++)
			get(rg[a][i],rg[a][i+1],lf[b][j],lf[b][j+1],res);
		get(rg[a][i],rg[a][i+1],lf[b][j],lf[b][j+1],res);
	}
	return -res;
}

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		int k;
		scanf("%d", &k);
		vec v;
		scanf("%lf %lf", &v.x, &v.y);
		lf[i].pb(v);
		bool dn = 0;
		while (--k) {
			scanf("%lf %lf", &v.x, &v.y);
			dn = (dn || (rg[i].size() && abs(v.y - rg[i].back().y) <= eps));
			if (!dn) { rg[i].pb(v); }
			else { lf[i].pb(v); }
		}
		reverse(lf[i].begin()+1,lf[i].end());
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			dist[i][j] = coll(i,j);
		}

		res[(1<<i)][i] = 0;
		for (vec v : lf[i]) res[(1<<i)][i] = max(res[(1<<i)][i],-v.x);
	}

	for (int msk = 1; msk < (1<<n); msk++) {
		if (__builtin_popcount(msk) == 1) continue;
		for (int i = 0; i < n; i++) {
			if (!(msk&(1<<i))) continue;
			res[msk][i] = 1./0.;
			for (int j = 0; j < n; j++) {
				if (i == j || !(msk&(1<<j))) continue;
				res[msk][i] = min(res[msk][i], res[msk-(1<<i)][j] + dist[j][i]);
			}
		}
	}

	double fin = 1./0.;
	for (int i = 0; i < n; i++) {
		double loc = 0.;
		for (vec v : rg[i]) loc = max(loc,v.x);
		fin = min(fin, loc + res[(1<<n)-1][i]);
	}
	printf("%.3f\n", fin);
}
