#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define fs first
#define sc second

const double pi = acos(-1.0);
const int size = 100 * 1000;
const double inf = 1e15;
const double eps = 1e-8;

int n;
double lb, rb, db, ub;
int x[size], y[size];

map <pair <int, int>, int> num;
double ans[size];

double sqr(double x) {
	return x * x;
}

struct point {
	double x, y;
	point(double x_ = 0.0, double y_ = 0.0): x(x_), y(y_) {}

	double dist(const point& p) const {
		return sqrt(sqr(p.x - x) + sqr(p.y - y));
	}

	void read() {
	    cin >> x >> y;
	}

	void print() {
		cout << x << ' ' << y << '\n';
	}

	void norm() {
		double k = sqrt(sqr(x) + sqr(y));
		x /= k;
		y /= k;
	}
};

double smult(const point& a, const point& b) {
	return a.x * b.x + a.y * b.y;
}

double vmult(const point& a, const point& b) {
	return a.x * b.y - a.y * b.x;
}

point operator + (const point& a, const point& b) {
	return point(a.x + b.x, a.y + b.y);
}

point operator - (const point& a, const point& b) {
	return point(a.x - b.x, a.y - b.y);
}

point operator * (const point& a, double k) {
	return point(a.x * k, a.y * k);
}

struct line {
	double a, b, c;
	line(double a_ = 1.0, double b_ = 0.0, double c_ = 0.0): a(a_), b(b_), c(c_) {
		norm();
    }

	line(const point& p1, const point& p2) {
		a = p2.y - p1.y;
		b = p1.x - p2.x;
		c = -a * p1.x - b * p1.y;

		norm();
	}

	void norm() {
		double k = sqrt(sqr(a) + sqr(b));
		a /= k;
		b /= k;
		c /= k;
	}

	double dist(const point& p) const {
		return a * p.x + b * p.y + c;
	}
};

bool crosslines(const line& l1, const line& l2, point& p) {
	double d = l1.a * l2.b - l1.b * l2.a;
	if (fabs(d) < eps)
		return false;

	p.x = (l1.b * l2.c - l1.c * l2.b) / d;
	p.y = (l1.c * l2.a - l1.a * l2.c) / d;

	return true;
}

line serper(const point& p1, const point& p2) {
	point mid = (p1 + p2) * 0.5;
	point vec = p2 - p1;
	vec.norm();
	vec = point(-vec.y, vec.x);

	return line(mid, mid + vec);
}

vector <point> cutconvex(const vector <point>& convex, const line& ln) {
	vector <point> res;	
	int n = convex.size();
	vector <double> dst(n);

	for (int i = 0; i < n; i++) {
		dst[i] = ln.dist(convex[i]);		
	}	

	for (int i = 0; i < n; i++) {
		if (dst[i] > -eps)
			res.pb(convex[i]);
 		int cur = i;
 		int nxt = (i + 1) % n;
 		if (fabs(dst[cur]) > eps && fabs(dst[nxt]) > eps && dst[cur] * dst[nxt] < -eps) {
 			line h(convex[cur], convex[nxt]);
 			point p;
            assert(crosslines(ln, h, p));
 			res.pb(p);
 		}
	}

	return res;
}

inline long long sqrd(long long x) {
	return x * x;
}

long long cx, cy;

bool comp(const pair <long long, long long>& a, const pair <long long, long long>& b) {
	long long d = (a.fs - cx) * (b.sc - cy) - (a.sc - cy) * (b.fs - cx);
	if (d == 0ll)
		return sqrd(a.fs - cx) + sqrd(a.sc - cy) < sqrd(b.fs - cx) + sqrd(b.sc - cy);
	else
		return d < 0ll;
}


vector <pair <int, int> > build_convex(vector <pair <int, int> > hpts) {
	sort(hpts.begin(), hpts.end());
	hpts.resize(unique(hpts.begin(), hpts.end()) - hpts.begin());
	vector <pair <long long, long long> > pts;
	for (int i = 0; i < (int) hpts.size(); i++)
		pts.pb(mp(hpts[i].fs, hpts[i].sc));

	int n = pts.size();
	int b = 0;
	for (int i = 1; i < n; i++) {
		if (pts[i].sc < pts[b].sc || (pts[i].sc == pts[b].sc && pts[i].fs < pts[b].fs))
			b = i;
	} 
	swap(pts[0], pts[b]);
	cx = pts[0].fs;
	cy = pts[0].sc;

	sort(pts.begin() + 1, pts.end(), comp);
	vector <pair <long long, long long> > st;
	st.pb(pts[0]);
	for (int i = 1; i < n; i++) {
		//cerr << "convex: " << pts[i].fs << ' ' << pts[i].sc << endl;
		while (st.size() > 1u) {
			int j = (int) st.size() - 1;
			int k = (int) st.size() - 2;
			if ((pts[i].fs - st[k].fs) * (st[j].sc - st[k].sc) - (st[j].fs - st[k].fs) * (pts[i].sc - st[k].sc) <= 0)
				st.pop_back();
			else {
				break;
			}
		} 
		st.pb(pts[i]);			
	}

	vector <pair <int, int> > res;
	for (int i = 0; i < (int) st.size(); i++)
		res.pb(mp((int) st[i].fs, (int) st[i].sc));

	return res;
}

double getsquare(const vector <point>& convex) {
	double sum = 0.0;

	int n = convex.size();
	for (int i = 0; i < n; i++)
		sum += vmult(convex[i], convex[(i + 1) % n]);

	return fabs(sum) / 2.0;;
}

int main() {
    cout.precision(20);
	ios::sync_with_stdio(false);

    freopen("euclid.in", "r", stdin);
    freopen("euclid.out", "w", stdout);

    cin >> lb >> db >> rb >> ub;
    point ld(lb, db);
    point rd(rb, db);
    point lu(lb, ub);
    point ru(rb, ub);

    line leftbound(ld, lu);
    line downbound(rd, ld);
    line rightbound(ru, rd);
    line upbound(lu, ru);

    cin >> n;
    for (int i = 0; i < n; i++) {
    	cin >> x[i] >> y[i];

    	num[mp(x[i], y[i])] = i;
    }

    vector <pair <int, int> > pts;
    for (int i = 0; i < n; i++)
    	pts.pb(mp(x[i], y[i]));
    vector <pair <int, int> > convex = build_convex(pts);

    int m = convex.size();

    if (m == 1) {
    	printf("1.0\n");
    	return 0;
    }

  //  cerr << m << endl;
    //for (int i = 0; i < m; i++)
    //	cerr << convex[i].fs << ' ' << convex[i].sc << endl;

    for (int i = 0; i < m; i++) {
    	vector <line> lines;
    	vector <point> pts;
    	
    	for (int j = 1; j < m; j++) {
    		int nxt = (i + j) % m;
    		line ln = serper(point(convex[i].fs, convex[i].sc), point(convex[nxt].fs, convex[nxt].sc));
    		if (ln.dist(point(convex[nxt].fs, convex[nxt].sc)) < 0.0) {
    			ln.a *= -1.0;
    			ln.b *= -1.0;
    			ln.c *= -1.0;
    		}

    		while (!pts.empty() && ln.dist(pts.back()) < eps) {
   				pts.pop_back();
   				lines.pop_back();
   			}
    		if (!lines.empty()) {
    			point p;
    			crosslines(lines.back(), ln, p);
    			pts.pb(p);
    		}

    		lines.pb(ln);
    	}
    //	cerr << lines.size() << ' ' << pts.size() << endl;
    
       		if (lines.size() == 1u) {
//       			cerr << pts.size() << endl;
    			assert(pts.empty());
    			pts.pb(ld);
    			pts.pb(rd);
    			pts.pb(ru);
    			pts.pb(lu);

    			pts = cutconvex(pts, lines[0]);
//    			cerr << lines[0].a << ' ' << lines[0].b << ' ' << lines[0].c << endl;
  //  			cerr << pts.size() << endl;
    		} else {
                int c = lines.size();
    //            for (int j = 0; j < c; j++)
      //          	cerr << lines[j].a << ' ' << lines[j].b << ' ' << lines[j].c << endl;
                point vec(-lines[c - 1].b, lines[c - 1].a);
    			point online(lines[c - 1].a, lines[c - 1].b);
    			online = online * (-lines[c - 1].c);
    			assert(lines[c - 1].dist(online) < eps);

    			point p1 = online + vec * inf;
    			point p2 = online - vec * inf;
    			if (lines[0].dist(p1) > 0)
    				pts.pb(p1);
    			if (lines[0].dist(p2) > 0)	
    				pts.pb(p2);

    			vec = point(-lines[0].b, lines[0].a);
    			online = point(lines[0].a, lines[0].b);
    			online = online * (-lines[0].c);
    			assert(lines[0].dist(online) < eps);
    			p1 = online + vec * inf;
    			p2 = online - vec * inf;
    			if (lines[c - 1].dist(p1) > 0)
    				pts.pb(p1);
    			if (lines[c - 1].dist(p2) > 0)	
    				pts.pb(p2);

    	//		cerr << pts.size() << endl;
    			pts = cutconvex(pts, leftbound);
    			//cerr << pts.size() << endl;
    			
    			pts = cutconvex(pts, rightbound);
	   			//cerr << pts.size() << endl;
    			
	   			pts = cutconvex(pts, downbound);
	   			//cerr << pts.size() << endl;
    			
	   			pts = cutconvex(pts, upbound);
//	   			cerr << pts.size() << endl;

//	   			cerr << endl;

//	   			for (int j = 0; j < (int) pts.size(); j++)
	   		}	

//	   		cerr << convex[i].fs << ' ' << convex[i].sc << ' ' << num[convex[i]] << endl << endl;
	   		ans[num[convex[i]]] = getsquare(pts);
   
    }

    double sq = (rb - lb) * (ub - db);
    for (int i = 0; i < n; i++)
    	ans[i] /= sq;

    for (int i = 0; i < n; i++)
    	printf("%.10lf\n", ans[i]);

    return 0;
}