#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const double pi = acos(-1);
 typedef  double cood; cood eps = 1e-7; // risky: XXX, untested: TODO
struct pnt { // TODO it's not tested at all :)
	cood x, y, z;
	pnt () : x(0), y(0), z(0) {} pnt (cood a, cood b, cood c) : x(a), y(b), z(c) {}
	inline pnt operator - (pnt o) { return pnt(x - o.x, y - o.y, z - o.z); }
	inline pnt operator + (pnt o) { return pnt(x + o.x, y + o.y, z + o.z); }
	inline pnt operator * (cood o) { return pnt(x*o, y*o, z*o); }
	inline pnt operator / (cood o) { return pnt(x/o, y/o, z/o); }
	inline cood operator * (pnt o) { return x*o.x + y*o.y + z*o.z; } // inner: |this||o|*cos(ang)
	inline pnt operator ^ (pnt o) { return pnt(y*o.z - z*o.y, z*o.x - x*o.z, x*o.y - y*o.x); } // cross: oriented normal to the plane containing the two vectors, has norm |this||o|*sin(ang)
	inline cood operator () (pnt a, pnt b) { return (*this)*(a^b); } // mixed: positive on the right-hand rule (thumb=this,index=a,mid=b)

	inline cood inner (pnt a, pnt b) { return (a-(*this))*(b-(*this)); }
	inline pnt cross (pnt a, pnt b) { return (a-(*this))^(b-(*this)); } // its norm is twice area of triangle
	inline cood mixed (pnt a, pnt b, pnt c) { return (a-(*this))(b-(*this),c-(*this)); } // 6 times the oriented area of thetahedra

	inline cood sq (pnt o = pnt()) { return inner(o,o); }
	inline double nr (pnt o = pnt()) { return sqrt(sq(o)); }
	inline pnt operator ~ () { return (*this)/nr(); }

	inline bool in_seg (pnt a, pnt b) { return cross(a,b).sq() <= eps && inner(a,b) <= eps; } // tips included
	inline bool in_tri (pnt a, pnt b, pnt c) { return abs(mixed(a,b,c)) <= eps && cross(a,b)*cross(b,c) >= -eps && cross(a,b)*cross(c,a) >= -eps; } // border included

	inline pnt proj (pnt a, pnt b) { return a + (b-a)*a.inner(b,(*this))/a.sq(b); }
	inline pnt proj (pnt a, pnt b, pnt c) { pnt n = a.cross(b,c); return (*this) - n*(n*((*this)-a))/n.sq(); }

	inline double dist2_lin (pnt a, pnt b) { return cross(a,b).sq()/a.sq(b); }
	inline double dist2_seg (pnt a, pnt b) { return a.inner(b,(*this))*b.inner(a,(*this)) <= eps ? min(sq(a),sq(b)) : dist2_lin(a,b); }
	inline double dist_pln (pnt a, pnt b, pnt c) { return abs((~a.cross(b,c))*((*this)-a)); }
	inline double dist2_tri (pnt a, pnt b, pnt c) { pnt p = proj(a,b,c); return p.in_tri(a,b,c) ? sq(p) : min({ dist2_seg(a,b), dist2_seg(b,c), dist2_seg(c,a) }); }
};
inline cood area (pnt a, pnt b, pnt c) { return abs(a.cross(b,c).nr()) / 2; }
inline cood vol (pnt a, pnt b, pnt c, pnt d) { return abs(a.mixed(b,c,d)) / 6; } // thetahedra
pnt inter_lin_pln (pnt s, pnt t, pnt a, pnt b, pnt c) { pnt n = a.cross(b,c); return s + (t-s)*(n*(a-s))/(n*(t-s)); }
struct sph { // TODO it's also not tested at all
	pnt c; cood r;
	sph () : c(), r(0) {} sph (pnt a, cood b) : c(a), r(b) {}
	inline pnt operator () (cood lat, cood lon) { return c + pnt(cos(lat)*cos(lon), sin(lon), sin(lat))*r; } // (1,0,0) is (0,0). z is height.
	inline double area_hull (double h) { return 2.*pi*r*h; }
	inline double vol_hull (double h) { return pi*h/6 * (3.*r*r + h*h); }
};

int t;
pnt v[2][3];

bool in_seg (pnt a, pnt s, pnt t) { return s.cross(a,t).sq() <= eps && s.inner(a,t)*t.inner(a,s) <= eps; }
bool seg_inter (pnt a, pnt b, pnt c, pnt d) {
	if (abs(a.mixed(b,c,d)) > eps) return false;
	//if (in_seg(a,c,d) || in_seg(b,c,d) || in_seg(c,a,b) || in_seg(d,a,b)) return true;
	pnt p = c.proj(a,b), q = a.proj(c,d);
	return (p.inner(c,d) <= eps && q.inner(a,b) <= eps);
}

int main () {
	scanf("%d", &t);

	while (t--) {
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 3; j++)
				for (cood * x : {&v[i][j].x, &v[i][j].y, &v[i][j].z})
					scanf("%lf", x);

		bool ok = 0;

		for (int i = 0; !ok && i < 2; i++)
			for (int j = 0; !ok && j < 3; j++) {
				if (v[i][j].in_tri(v[!i][0],v[!i][1],v[!i][2]))
					ok = 1;

				for (int k = 0; k < 3; k++) {
					if (seg_inter(v[!i][k], v[!i][(k+1)%3], v[i][j], v[i][(j+1)%3]))
						ok = 1;
				}

				pnt p = inter_lin_pln(v[i][j], v[i][(j+1)%3], v[!i][0], v[!i][1], v[!i][2]);
				if (p.in_tri(v[!i][0],v[!i][1],v[!i][2])) ok = 1;
			}
		printf("%d\n", ok);
	}

}
