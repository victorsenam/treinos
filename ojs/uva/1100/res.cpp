#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const double pi = acos(-1);
typedef double cood; cood eps = 1e-8; // risky: XXX, untested: TODO
struct pnt { // TODO it's not tested at all :)
	cood x, y, z;
	pnt () : x(0), y(0), z(0) {} pnt (cood a, cood b, cood c) : x(a), y(b), z(c) {}
	friend ostream & operator << (ostream &, pnt);
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
	inline bool in_tri (pnt a, pnt b, pnt c) { return (a.mixed((*this),b,c)) <= eps && cross(a,b).z*cross(b,c).z >= -eps && cross(a,b).z*cross(c,a).z >= -eps; } // border included$

	inline pnt proj (pnt a, pnt b) { return a + (b-a)*a.inner(b,(*this))/a.sq(b); }
	inline pnt proj (pnt a, pnt b, pnt c) { pnt n = a.cross(b,c); return (*this) - n*(n*((*this)-a))/n.sq(); }

	inline double dist2_lin (pnt a, pnt b) { return cross(a,b).sq()/a.sq(b); }
	inline double dist2_seg (pnt a, pnt b) { return a.inner(b,(*this))*b.inner(a,(*this)) <= eps ? min(sq(a),sq(b)) : dist2_lin(a,b); }
	inline double dist_pln (pnt a, pnt b, pnt c) { return abs((~a.cross(b,c))*((*this)-a)); }
	inline double dist2_tri (pnt a, pnt b, pnt c) { pnt p = proj(a,b,c); return p.in_tri(a,b,c) ? sq(p) : min({ dist2_seg(a,b), dist2_seg(b,c), dist2_seg(c,a) }); }
};
inline cood area (pnt a, pnt b, pnt c) { return abs(a.cross(b,c).nr()) / 2; }
inline cood vol (pnt a, pnt b, pnt c, pnt d) { return abs(a.mixed(b,c,d)) / 6; } // thetahedra
pnt inter_lin_pln (pnt s, pnt t, pnt a, pnt b, pnt c) { pnt n = a.cross(b,c); return s + (t-s)*(n*(a-s))/(n*(t-s)); } //$
struct sph { // TODO it's also not tested at all
	pnt c; cood r;
	sph () : c(), r(0) {} sph (pnt a, cood b) : c(a), r(b) {}
	inline pnt operator () (cood lat, cood lon) { return c + pnt(cos(lat)*cos(lon), sin(lon), sin(lat))*r; } // (1,0,0) is (0,0). z is height.
	inline double area_hull (double h) { return 2.*pi*r*h; }
	inline double vol_hull (double h) { return pi*h/6 * (3.*r*r + h*h); }
};
int sgn (cood o) { return (o > eps) - (o < -eps); }

pnt v[7];

ostream & operator << (ostream & os, pnt p) { return os << "(" << p.x << " " << p.y << " " << p.z << ")"; }

int main () {
	for (int ts = 1; ; ts++) {
		for (int i = 0; i < 6; i++) {
			for (cood * p : {&v[i].x, &v[i].y, &v[i].z})
				if (scanf("%lf", p) == EOF) return 0;
			//cout << char('A'+i) << ": " << v[i] << endl;
		}

		pnt G = (v[0]+v[1]+v[2]+v[3])/4;
		pnt H = (v[0]+v[1]+v[2]+v[4])/4;
		//cout << G << " " << H << endl;
		cood V_G = vol(v[0],v[1],v[2],v[3])/6;
		cood V_H = vol(v[0],v[1],v[2],v[4])/6;
		//cout << V_G << " " << V_H << endl;
		pnt cnt = ((G*V_G)+(H*V_H))/(V_G+V_H);
		//cout << endl;
		
		double mn = 1./0., mx = 0.;
		for (int i = 0; i < 5; i++)
			for (int j = i + 1; j < 5; j++)
				for (int k = j + 1; k < 5; k++) {
					//cout << char('A'+i) << char('A'+j) << char('A'+k) << ": " << v[5].dist_pln(v[i],v[j],v[k]) << " " << v[5].proj(v[i],v[j],v[k]) << endl;
					int fnd = 0;
					for (int l = 0; l < 5; l++)
						fnd |= (1<<(sgn((v[l]-v[i])*v[i].cross(v[j],v[k])) + 1));
					if ((fnd&1) && (fnd&4))
						continue;
					pnt proj = cnt.proj(v[i],v[j],v[k]);
					bool isstable = proj.in_tri(v[i],v[j],v[k]);
					if (isstable && proj.dist2_seg(v[i],v[j]) + eps < 0.2*0.2) { isstable = false; }
					if (isstable && proj.dist2_seg(v[i],v[k]) + eps < 0.2*0.2) { isstable = false; }
					if (isstable && proj.dist2_seg(v[j],v[k]) + eps < 0.2*0.2) { isstable = false; }
					if (isstable) {
						mn = min(mn, v[5].dist_pln(v[i],v[j],v[k]));
						mx = max(mx, v[5].dist_pln(v[i],v[j],v[k]));
					}
				}
		
		printf("Case %d: %.5f %.5f\n", ts, mn, mx);
	}
}
