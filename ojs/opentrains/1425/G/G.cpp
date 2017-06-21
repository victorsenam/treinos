#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll gcd (ll a, ll b) {
    while (b) {
        a %= b;
        swap(a,b);
    }
    return a;
}

typedef double cood;
cood eps = 1e-9;
double pi = acos(-1.);

struct vec { // vector
	// === BASIC ===
	cood x, y;
	vec () : x(0), y(0) {}
	vec (cood a, cood b) : x(a), y(b) {}
	friend ostream& operator<<(ostream& os, vec o);

    bool operator < (const vec & o) const
    { return x + eps < o.x || (!(o.x + eps < x) && y + eps < o.y); }
	vec operator - (vec o)
	{ return vec(x - o.x, y - o.y); }
	vec operator + (vec o)
	{ return vec(x + o.x, y + o.y); }
	vec operator * (cood o)
	{ return vec(x * o, y * o); }
	vec operator / (cood o)
	{ return vec(x / o, y / o); }
	cood operator ^ (vec o)
	{ return x * o.y - y * o.x; }
	cood operator * (vec o)
	{ return x * o.x + y * o.y; }

	cood sq (vec o = vec())
	{ return ((*this)-o)*((*this)-o); }
	double nr (vec o = vec())
	{ return sqrt(double(sq(o))); }

	cood ar (vec a, vec b) // ccw signed area (positive if this is to the left of ab)
	{ return (b - a) ^ ((*this) - a); }
	int sd (vec a, vec b) // which side is this from ab? (-1 left, 0 over, 1 right)
	{ cood o = ar(a, b); return (o < -eps) - (eps < o); }

	// === ADVANCED ===
	// is this inside segment st? (tip of segment included, change for < -eps otherwise)
	bool in_seg (vec s, vec t)
	{ return (sd(s, t) == 0) && !(-eps < ((*this) - s) * ((*this) - t)); }
};

// tests TODO
struct lin { // line
	cood a, b, c;

	lin () {}
	lin (cood x, cood y, cood z) : a(x), b(y), c(z) {}
	lin (vec s, vec t) : a(t.y - s.y), b(s.x - t.x), c(a * s.x + b * s.y) {}

	// parallel to this through p
	lin parll (vec p) { return lin(a, b, a * p.x + b * p.y); }

	// line intersection
	vec inter (lin o) {
		cood d = a * o.b - o.a * b;
		if (!(d < -eps) && !(eps < d)) throw 0; // parallel
		return vec(cood((o.b * c - b * o.c) / d), cood((a * o.c - o.a * c) / d));
	}
};

// tests TODO
// returns any point on the intersection of ab and cd (including all tips)
bool seg_inter (vec a, vec b, vec c, vec d) {
	if (a.in_seg(c, d) || b.in_seg(c, d) || c.in_seg(a, b) || d.in_seg(a, b))
		return true;
	return (c.sd(a, b) * d.sd(a, b) == -1 && a.sd(c, d) * b.sd(c, d) == -1);
}
ostream & operator << (ostream & o, vec x)
{ return o << "(" << x.x << "," << x.y << ")"; }

const int N = 1e6;

int n, m;
vec v[N];
int ls[N][2];
vector<int> inl[N];

int visi[N];
bool istp[N];
int snk;
int src;
vector<int> adj[N];

bool mark (int u) {
    if (visi[u])
        return 1;
    //cout << v[u] << endl;
    if (u == src)
        return 0;
    visi[u] = 1;
    if (istp[u])
        return 1;

    for (int v : adj[u])
        if (!mark(v))
            return 0;
    return 1;
}

double dfs (int u, int v) {
    if (visi[u])
        return 0;
    visi[u] = 1;

    double res = 0.;
    for (int w : adj[u]) {
        if (w == v) continue;
        res += ::v[u].nr(::v[w]);
        res += dfs(w, u);
    }

    return res;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    double chk = 0;
    map<vec, int> mp;
    cin >> n >> m;
    int qs = 0;
    for (int i = 0; i < n+n+m+2; i++) {
        cin >> v[qs].x >> v[qs].y;

        int cur = qs;
        if (mp.find(v[qs]) == mp.end()) {
            mp[v[qs]] = qs++;
        } else {
            cur = mp[v[qs]];
        }

        if (i < n+n) {
            ls[i/2][i%2] = cur;
            if (i%2 == 1)
                chk += v[ls[i/2][0]].nr(v[ls[i/2][1]]);
        } else if (i < n+n+m) {
            istp[cur] = 1;
        } else if (i == n+n+m) {
            src = cur;
        } else {
            snk = cur;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < qs; j++) {
            if (v[j].in_seg(v[ls[i][0]],v[ls[i][1]])) {
                //cout << j << ": " << v[j] << " in " << i << ": " << v[ls[i][0]] << " " << v[ls[i][1]] << endl;
                inl[i].push_back(j);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        inl[i].push_back(ls[i][0]);
        inl[i].push_back(ls[i][1]);
        for (int j = i+1; j < n; j++) {
            if (seg_inter(v[ls[i][0]], v[ls[i][1]], v[ls[j][0]], v[ls[j][1]])) {
                int cur = qs;
                if (v[ls[i][0]].in_seg(v[ls[j][0]], v[ls[j][1]]))
                    cur = ls[i][0];
                else if (v[ls[i][1]].in_seg(v[ls[j][0]], v[ls[j][1]]))
                    cur = ls[i][1];
                else if (v[ls[j][0]].in_seg(v[ls[i][0]], v[ls[i][1]]))
                    cur = ls[j][0];
                else if (v[ls[j][1]].in_seg(v[ls[i][0]], v[ls[i][1]]))
                    cur = ls[j][1];
                else {
                    v[qs] = lin(v[ls[i][0]], v[ls[i][1]]).inter(lin(v[ls[j][0]], v[ls[j][1]]));

                    if (mp.find(v[qs]) == mp.end()) {
                        mp[v[qs]] = qs++;
                    } else {
                        cur = mp[v[qs]];
                    }
                }

                inl[i].push_back(cur);
                inl[j].push_back(cur);
            }
        }
    }

    double res = 0;
    for (int i = 0; i < n; i++) {
        sort(inl[i].begin(), inl[i].end(), [i] (int a, int b) {
            cood da = v[ls[i][0]].sq(v[a]); cood db = v[ls[i][0]].sq(v[b]);
            if (da < db) return true;
            if (db < da) return false;
            assert(a == b);
            return a < b;
        });

        inl[i].resize(unique(inl[i].begin(), inl[i].end()) - inl[i].begin());

/*
        for (int vv : inl[i])
            cout << v[vv] << " ";
        cout << endl;
*/

        for (int j = 1; j < inl[i].size(); j++) {
            adj[inl[i][j-1]].push_back(inl[i][j]);
            adj[inl[i][j]].push_back(inl[i][j-1]);
            res += double(v[inl[i][j]].nr(v[inl[i][j-1]]));
        }
    }

    assert(abs(res-chk) < eps);

    if (!mark(snk)) {
        cout << -1 << endl;
        return 0;
    }
    res -= dfs(src, src);
    cout << setprecision(20) << res << endl;
}
