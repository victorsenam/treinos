#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 107;

struct vec {
	int x, y;

	bool operator < (const vec & o) const {
		return (x!=o.x)?x<o.x:y<o.y;
	}
};

struct seg {
	int s, t, x;
	bool open;

	bool operator < (const seg & ot) const {
		return x < ot.x;
	}
};

struct node {
	ll l, r;
	int mn, lz;
	ll rc;
	int ch[2];
};

int n, m;
vector<seg> v, u;
ll area;

node tree[N*N*4];
int es;

int create (ll l, ll r) {
	tree[es].ch[0] = tree[es].ch[1] = tree[es].mn = tree[es].lz = 0;
	tree[es].l = l; tree[es].r = r;
	tree[es].rc = tree[es].r - tree[es].l + 1;
	return es++;
}

void refresh (int u) {
	if (tree[u].ch[0] == 0 && tree[u].l != tree[u].r) {
		ll md = tree[u].l + (tree[u].r - tree[u].l)/2;
		tree[u].ch[0] = create(tree[u].l, md);
		tree[u].ch[1] = create(md+1, tree[u].r);
	}
	tree[u].mn += tree[u].lz;
	if (tree[u].l != tree[u].r)
		for (int k = 0; k < 2; k++)
			tree[tree[u].ch[k]].lz += tree[u].lz;
	tree[u].lz = 0;
}

void add (int u, ll l, ll r, int x) {
	refresh(u);
	if (tree[u].r < l || r < tree[u].l) return;
	if (l <= tree[u].l && tree[u].r <= r) {
		//cout << "[" << tree[u].l << ".." << tree[u].r << "] ";
		tree[u].lz += x;
		refresh(u);
	} else {
		add(tree[u].ch[0],l,r,x);
		add(tree[u].ch[1],l,r,x);
		tree[u].mn = min(tree[tree[u].ch[0]].mn, tree[tree[u].ch[1]].mn);
		tree[u].rc = 0;
		for (int k = 0; k < 2; k++)
			tree[u].rc += tree[tree[u].ch[k]].mn == tree[u].mn ? tree[tree[u].ch[k]].rc : 0;
	}
	//if (u == 1) cout << "added " << x << endl;
}

int get (int u, ll l, ll r) {
	refresh(u);
	if (tree[u].r < l || r < tree[u].l) return INT_MAX;
	if (l <= tree[u].l && tree[u].r <= r) return tree[u].mn;
	return min(get(tree[u].ch[0],l,r),get(tree[u].ch[1],l,r));
}

void go (vector<seg> & v) {
	cout << "go " << endl;
	area = 0;
	sort(v.begin(), v.end());

	es = 1;
	create(INT_MIN,INT_MAX);

	int ls = INT_MIN;

	for (seg & s : v) {
		area += ll(s.x - ls)*(tree[1].r - tree[1].l + 1 - (tree[1].mn == 0)*tree[1].rc);

		ll x = get(1, s.s, s.t);
		s.open = (x==0)?true:false;
		add(1, s.s, s.t, s.open?1:-1);

		ls = s.x;
	}
	cout << area << endl;
}

set<vec> s;

bool solve (vec d) {
	if (s.find(d) != s.end()) return 0;
	s.insert(d);
	ll res = 0;
	
	es = 1;
	create(INT_MIN,INT_MAX);

	ll ls = INT_MIN;
	int j = 0;
	for (int i = 0; i < v.size(); i++) {
		seg cur = v[i];
		cur.s += d.y; cur.t += d.y; cur.x += d.x;

		if (j < u.size() && u[j].x <= cur.x) {
			i--;
			cur = u[j++];
		}

		res += ll(cur.x - ls)*(tree[1].r - tree[1].l + 1 - (tree[1].mn == 0)*tree[1].rc);
		cout << cur.x << " open(" << cur.open << ") [" << cur.s << ".." << cur.t << "] -> " << res  << endl;
		add(1, cur.s, cur.t, cur.open?1:-1);
		ls = cur.x;
	}

	if (j == u.size()) cout << "res (" << d.x << "," << d.y << ") = " << res << endl;
	return (j == u.size() && res == area);
}

void add (vector<seg> & v, vec a, vec b) {
	if (a.x != b.x) return;
	seg cur;
	cur.x = a.x;
	cur.s = a.y;
	cur.t = b.y;
	if (cur.s > cur.t) swap(cur.s,cur.t);
	cout << "add (" << cur.x << "[" << cur.s << ".." << cur.t << "]" << endl;
	v.pb(cur);
}

int main () {
	int tt = 1;
	while (scanf("%d %d", &n, &m) != EOF && n && m) {
		v.clear(); v.reserve(n);
		u.clear(); u.reserve(m);
		s.clear();
		vec lst, fst;
		cout << "hole" << endl;
		for (int i = 0; i < n; i++) {
			vec cur;
			scanf("%d %d", &cur.x, &cur.y);
			if (i) add(v,cur,lst);
			else fst = cur;
			lst = cur;
		}
		add(v,lst,fst);
		cout << "cover" << endl;
		for (int i = 0; i < m; i++) {
			vec cur;
			scanf("%d %d", &cur.x, &cur.y);
			if (i) add(u,cur,lst);
			else fst = cur;
			lst = cur;
		}
		add(u,lst,fst);

		go(v);
		go(u);

		bool ok = 0;
		for (seg a : v) for (seg b : v) for (seg c : u) for (seg d : u)
			for (int e : {b.s,b.t}) for (int f : {d.s,d.t}) {
				ok = solve(vec({c.x - a.x, f - e}));
				if (ok) goto fim;
			}
		fim:
		printf("Hole %d: %s\n", tt++, ok?"Yes":"No");
	}
}
