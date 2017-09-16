#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef double num;
const num eps = 1e-8;

const int N = 1e6+7;

struct vec { 
	num x, y;
	num st;

	num eval (num al) {
		return x * cos(al) + y * sin(al);
	}

	// esse cara ganha de t daqui pra frente
	// x >= t.x
	num beats (vec t) {
		if (abs(x - t.x) < eps) {
			if (y < t.y)
				return 0.;
			else
				return 1.;
		}
		num lo = 0.;
		num hi = 1.;

		int ts = 70;
		while (ts--) {
			num md = (lo + hi)*.5;
			if (eval(md) + eps <= t.eval(md))
				hi = md;
			else
				lo = md;
		}

		return lo;
	}

	bool operator < (const vec & ot) const {
		if (abs(x - ot.x) > eps)
			return x < ot.x;
		return y + eps < ot.y;
	}
};

num evt[N]; int t_evt[N], i_evt[N], evs;

struct env {
 	vec v[N];
	int n;

	void add (vec t) {
		if (n && t.beats(v[n-1]) + eps >= 1.)
			return;
		while (n && t.beats(v[n-1]) + eps <= v[n-1].st)
			n--;

		if (n)
			t.st = t.beats(v[n-1]);
		else
			t.st = 0.;
		v[n++] = t;
	}

	num get (double al) {
		int lo = 0;
		int hi = n-1;

		while (lo < hi) {
			int md = (lo+hi+1)/2;
			if (v[md].st < al)
				lo = md;
			else
				hi = md-1;
		}

		return v[lo].eval(al);
	}

	void inter (int i, vec t) {
		cout << "(" << t.x << "," << t.y << ")";
		int nx = upper_bound(v, v+n, t, [] (vec a, vec b) { return a.x < b.x; }) - v;
		int pr = nx-1;
		t_evt[evs] = 0;
		i_evt[evs] = i;
		if (pr == -1) {
			evt[evs++] = eps;
		} else {
			int lo = 0, hi = pr;
			while (lo < hi) {
				int md = (lo+hi+1)/2;

				if (t.eval(v[md].st) + eps <= v[md].eval(v[md].st))
					hi = md-1;
				else
					lo = md;
			}
			evt[evs++] = t.beats(v[lo]) + eps;
		}
		cout << "[" << evt[evs-1] << ",";
		
		t_evt[evs] = 1;
		i_evt[evs] = i;
		if (nx == n) {
			evt[evs++] = 1. - eps;
		} else {
			int lo = nx, hi = n-1;
			while (lo < hi) {
				int md = (lo+hi)/2;
				
				if (v[md].eval(v[md+1].st) + eps <= t.eval(v[md+1].st))
					hi = md;
				else
					lo = md+1;
			}
			evt[evs++] = v[lo].beats(t) - eps;
		}

		cout << evt[evs-1] << "]" << endl;
	}
} e[2];

int n;
vec f[N], a[N];
int p[N];
int fs, as;
set<vec> s;

int main () {
	cout << setprecision(10) << fixed;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		vec v; int t;
		scanf("%lf %lf %d", &v.x, &v.y, &t);
		if (t) {
			f[fs++] = v;
			s.insert(v);
		} else {
			if (s.find(v) == s.end())
				a[as++] = v;
		}
	}

	if (fs == 1) {
		printf("1\n");
		return 0;
	}

	sort(f, f+fs, [] (vec a, vec b) {
		return a.x < b.x;
	});

	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < fs; i++) {
			f[i].x = -f[i].x; 
			f[i].y = -f[i].y; 
		}
		for (int i = 0; i + i < fs; i++)
			swap(f[i], f[fs-i-1]);
		
		for (int i = 0; i < fs; i++) {
			e[k].add(f[i]);
		}

		cout << "env " << k << endl;
		for (int i = 0; i < e[k].n; i++)
			cout << "(" << e[k].v[i].x << "," << e[k].v[i].y << ") : " << e[k].v[i].st << endl;

	}

	for (int k = 0; k < 2; k++) {
		cout << "env " << k << endl;
		for (int i = 0; i < as; i++) {
			a[i].x = -a[i].x;
			a[i].y = -a[i].y;
			e[k].inter(i, a[i]);
		}
	}

	for (int i = 0; i < evs; i++)
		p[i] = i;

	sort(p, p+evs, [] (int i, int j) {
		return evt[i] < evt[j];
	});

	int cnt = n;
	int mn = cnt;
	map<int, int> mp;
	for (int _ev = 0; _ev < evs; _ev++) {
		int ev = p[_ev];
		int i = i_evt[ev];

		if (t_evt[ev]) {
			if (--mp[i] == 0)
				cnt++;
		} else {
			if (mp[i]++ == 0)
				cnt--;
		}

		cout << evt[ev] << ": " << t_evt[ev] << " " << i << "  (cnt = " << cnt << ")" << endl;
		mn = min(mn, cnt);
	}

	printf("%d\n", mn);
}
