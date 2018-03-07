#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 200123;
const int M = 1e6+100;
const int L = 1e6+2;
const int T = 8*M;
//const int M = 30;
//const int L = 28;
struct Point {
	int i, j;

	bool operator < (const Point & o) const { return (j!=o.j)?j<o.j:i<o.i; }
};

struct Fence;

struct Flower {
	Point p;
	Fence * f;
};

struct Cow {
	int id;
	Point p;
	ll ans;
	Fence * f;
};

struct Fence { 
	Point s, t;
	Fence * f;
	Cow * r, * d;
	vector<Cow*> cow;
	vector<Flower*> flower;
	vector<Fence*> fence; 
	int id;
};

int v[4*M];
struct FenceSeg {
	int lz[4*M];
	int l_l[4*M], l_r[4*M];
	void build (int u, int l, int r, int x) {
		v[u] = x; lz[u] = -1;
		l_l[u] = l; l_r[u] = r;
		if (l == r) return;
		int md = (l+r)/2;
		build(u+u, l, md, x);
		build(u+u+1, md+1, r, x);
	}
	void refresh (int u) {
		if (lz[u] != -1) {
			v[u] = lz[u];
			if (l_l[u] != l_r[u]) lz[u+u] = lz[u+u+1] = lz[u];
			lz[u] = -1;
		}
	}
	int get (int u, int i) { 
		refresh(u);
		if (l_l[u] == i && l_r[u] == i) return v[u];
		return (l_r[u+u]>=i)?get(u+u,i):get(u+u+1,i);
	}
	void set (int u, int l, int r, int x) {
		refresh(u);
		if (l > l_r[u] || l_l[u] > r) return;
		if (l <= l_l[u] && l_r[u] <= r) lz[u] = x;
		else { set(u+u,l,r,x); set(u+u+1,l,r,x); }
	}
};

FenceSeg open_fence;

struct PersSeg {
	int es;
	int ls;
	int hd[M];
	int ch[T][2];
	int sm[T];
	int l_l[T], l_r[T];

	int get (int u, int l, int r) {
		if (u == -1 || r < l_l[u] || l_r[u] < l) return 0;
		return get(ch[u][0],l,r) + get(ch[u][1],l,r);
	}

	int after (Point p) {
		if (ls > p.j) return get(hd[ls],p.i,M);
		return get(hd[p.j],p.i,M);
	}

	int create (int l, int r) { ch[es][0] = ch[es][1] = -1; sm[es] = 0; l_l[es] = l; l_r[es] = r; return es++; }
	int create (int u) { ch[es][0] = ch[u][0]; ch[es][1] = ch[u][1]; sm[es] = sm[u]; l_l[es] = l_l[u]; l_r[es] = l_r[u]; return es++; }

	void add (int & u, int i) {
		u = create(u);
		if (l_l[u] == l_r[u]) { sm[u]++; return; }
		int md = (l_l[u]+l_r[u])/2;
		if (ch[u][0] == -1) ch[u][0] = create(l_l[u],md);
		if (ch[u][1] == -1) ch[u][1] = create(md+1,l_r[u]);
		if (i <= md) add(ch[u][0],i);
		else add(ch[u][1],i);
		sm[u] = sm[ch[u][0]] + sm[ch[u][1]];
	}

	void add (Point p) {
		if (ls > p.j) { hd[p.j] = hd[ls]; ls = p.j; }
		add(hd[p.j],p.i);
	}
};

PersSeg cnt_flow;
Fence fence[N];

void go (Fence * f) {
	reverse(f->cow.begin(), f->cow.end());
	reverse(f->flower.begin(), f->flower.end());
	reverse(f->fence.begin(), f->fence.end());

	auto c_f = f->fence.begin(); auto c_n = f->cow.begin(); auto c_m = f->flower.begin();
	cnt_flow.es = 0; cnt_flow.ls = M+2; cnt_flow.hd[cnt_flow.ls] = cnt_flow.create(0,M-1);

	int ls = -1;
	while (c_f != f->fence.end() || c_n != f->cow.end() || c_m != f->flower.end()) {
		Point p_f, p_n, p_m, p;
		p = p_f = p_n = p_m = {M,M};
		int ch = 2;
		if (c_f != f->fence.end()) p_f = (*c_f)->s;
		if (c_n != f->cow.end()) p_n = (*c_n)->p;
		if (c_m != f->flower.end()) p = p_m = (*c_m)->p;

		if (p < p_n) { ch = 1; p = p_n; }
		if (p < p_f) { ch = 0; p = p_f; }

		if (ch == 0) {
			open_fence.set(1,(*c_f)->s.i,(*c_f)->t.i-1,(*c_f)->id);
			ls = (*c_f)->id;
			c_f++;
		} else if (ch == 1) {
			(*c_n)->ans = cnt_flow.after((*c_n)->p);
			int i = open_fence.get(1,(*c_n)->p.i);
			if (fence[i].f == (*c_n)->f) {
				(*c_n)->ans += fence[i].d->ans;
				(*c_n)->ans -= cnt_flow.after({fence[i].d->p.j,(*c_n)->p.i});
			}
			/* eu preciso descobrir aqui, de alguma forma, quem está abaixo de **c_n. Talvez seja legal guardar, no primeiro sweep, essa informação para cada vaca, me parece que a ordem lá não é ruim para isso
			if (ls != -1 && fence[ls].s.j == c_n->j) {
				(*c_n)->ans -= fence[ls].d->ans;
				(*c_n)->ans += fence[ls].r->ans;
			}
			*/
			c_n++;
		} else {
			cnt_flow.add((*c_m)->p);
			c_m++;
		}
	}
}

int f, m, n, ini_n;
Flower flower[N];
Cow cow[4*N];

ostream & operator << (ostream & os, const Point & p) { return os << "(" << p.i << "," << p.j << ")"; }
ostream & operator << (ostream & os, const Flower & f) { return os << "Flower{"<<f.p<<"}"; }
ostream & operator << (ostream & os, const Cow & c) { return os << "Cow{"<<c.i<<","<<c.p<<"}"; }
ostream & operator << (ostream & os, const Fence & f) { return os << "Fence{"<<f.s<<f.t<<"}"; }

int main () {
while (scanf("%d", &f) != EOF) {
	for (int i = 0; i <= f; i++) {
		if (i < f) {
			scanf("%d %d %d %d", &fence[i].s.i, &fence[i].s.j, &fence[i].t.i, &fence[i].t.j);
			fence[i].t.i++; fence[i].t.j++;
		}
		else fence[i] = { {0,0}, {L,L} };
		fence[i].cow.clear();
		fence[i].flower.clear();
		fence[i].fence.clear();
	}
	
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &flower[i].p.i, &flower[i].p.j);
	}

	scanf("%d", &n); ini_n = n;
	for (int i = 0; i < n; i++) {
		cow[i].i = i;
		scanf("%d %d", &cow[i].p.i, &cow[i].p.j);
	}
	
	for (int i = 0; i < f; i++) {
		cow[n] = { ini_n, { fence[i].t.i, fence[i].t.j } };
		fence[i].r = &cow[n++];
		cow[n] = { ini_n, { fence[i].s.i, fence[i].t.j } };
		fence[i].d = &cow[n++];
	}

	sort(fence, fence+f, [] (Fence & a, Fence & b) { return a.s < b.s; });
	sort(cow, cow+n, [] (Cow & a, Cow & b) { return a.p < b.p; });
	sort(flower, flower+m, [] (Flower & a, Flower & b) { return a.p < b.p; });

	for (int i = 0; i <= f; i++) fence[i].i = i;

	open_fence.build(1,0,M-1,f);
	fence[f]->f = NULL;
	int c_f = 0, c_n = 0, c_m = 0;
	while (c_f < f || c_n < n || c_m < m) {
		Point p_f, p_n, p_m, p;
		p = p_f = p_n = p_m = {M,M};
		int ch = 0;
		if (c_f < f) p = p_f = fence[c_f].s;
		if (c_n < n) p_n = cow[c_n].p;
		if (c_m < m) p_m = flower[c_m].p;

		if (p_n < p) { ch = 1; p = p_n; }
		if (p_m < p) { ch = 2; p = p_m; }

		Fence * parent = fence + open_fence.get(1,p.i);
		while (parent->t.j <= p.j) {
			open_fence.set(1,parent->s.i,parent->t.i-1,parent->f-fence);
			parent = fence + open_fence.get(1,p.i);
		}
		
		if (ch == 0) {
			fence[c_f].f = parent;
			open_fence.set(1,fence[c_f].s.i,fence[c_f].t.i-1,c_f);
			parent->fence.pb(fence+c_f);
			c_f++;
		} else if (ch == 1) {
			cow[c_n].f = parent;
			parent->cow.pb(cow+c_n);
			c_n++;
		} else {
			flower[c_m].f = parent;
			parent->flower.pb(flower+c_m);
			c_m++;
		}
	}

	open_fence.build(1,0,M-1,f);
	for (int i = 0; i < f; i++) go(fence+i);
}
}
