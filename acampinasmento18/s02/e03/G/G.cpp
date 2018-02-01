#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef ll cood; cood eps = 0;
struct vec {
	cood x, y; ll w;
	inline vec operator - (vec o) { return {x-o.x,y-o.y}; }
	inline cood operator ^ (vec o) { return x*o.y - y*o.x; }
	inline cood operator * (vec o) { return x*o.x + y*o.y; }

	inline bool operator == (vec o) { return x==o.x&&y==o.y; }

	inline cood cross (vec a, vec b) { return ((*this)-a)^((*this)-b); }
	inline cood inner (vec a, vec b) { return ((*this)-a)*((*this)-b); }
};

const int N = 700, M = 1e4+7;
int n, m;
vec p[N], v[M];
ll inc[N][N], acc[N][N];

int main () {
	scanf("%d", &n);
	for (int i = n-1; i >= 0; i--)
		scanf("%lld %lld", &p[i].x, &p[i].y);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%lld %lld %lld", &v[i].x, &v[i].y, &v[i].w);
	}

	for (int i = 0; i < n; i++) {
		sort(v, v+m, [i] (vec a, vec b) { return (p[i]==a||p[i]==b)?p[i]==a:p[i].cross(a,b) > 0; });
		int k = 0, l = 0;
		acc[i][i] = inc[i][i] = 0;
		while (k < m && p[i] == v[k]) { inc[i][i]+=v[k].w; k++; }
		l = k;
		for (int j = i+1; j < n; j++) {
			acc[i][j] = acc[i][j-1];
			inc[i][j] = inc[i][j-1];
			for (; k < m && v[k].cross(p[i],p[j]) < 0; k++)
				acc[i][j] += v[k].w;
			for (; l < m && v[l].cross(p[i],p[j]) <= 0; l++)
				inc[i][j] += v[l].w;
		}
	}

	ll res = LLONG_MIN;
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			for (int k = j+1; k < n; k++) {
				res = max(res, inc[i][k] - acc[i][j] - acc[j][k]);			
			}
		}
	}
	printf("%lld\n", res);
}
