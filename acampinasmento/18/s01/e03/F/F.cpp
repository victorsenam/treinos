#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef long double cood;

struct vec {
	cood x, y, z;
	vec() : x(0), y(0), z(0) {}
	vec(cood a, cood b, cood c) : x(a), y(b), z(c) {}
	inline vec operator - (vec o) { return {x - o.x, y - o.y, z - o.z}; }
	inline vec operator + (vec o) { return {x + o.x, y + o.y, z + o.z}; }
	inline vec operator * (cood o) { return {x * o, y * o, z * o}; }
	inline vec operator ^ (vec o) { return {y * o.z - o.y * z, z * o.x - o.z * x, x * o.y - o.x * y}; }
	inline cood operator * (vec o) { return x * o.x + y * o.y + z * o.z; }
	inline cood inner(vec a, vec b) { return (a - *this) * (b - *this); }
	inline cood sq(vec o = vec()) { return inner(o, o); }
	inline long double nr(vec o = vec()) { return sqrt(sq(o)); }
	inline cood operator() (vec a, vec b) { return *this * (a ^ b); }
	inline cood mixed(vec a, vec b, vec c) { return (a - *this)(b - *this, c - *this); }
};
cood eps = 1e-8;

vec inter(vec C, cood R, vec p, vec v) {
	cood l = 0, r = 3e4;
	for(int i = 0; i < 250; i++) {
		cood m1 = (l * 2 + r) / 3;
		cood m2 = (l + r * 2) / 3;
		if(C.sq(p + v * m1) < C.sq(p + v * m2))
			r = m2;
		else
			l = m1;
	}
	if(C.nr(p + v * l) > R + eps) throw 1;
	r = l;
	l = 0;
	for(int i = 0; i < 250; i++) {
		cood m = (l + r) / 2;
		if(C.sq(p + v * m) > R * R)
			l = m;
		else
			r = m;
	}
	return p + v * l;
}

const cood pi = acos(-1);


inline int sign(cood x) {
	return (x >= eps) - (x <= -eps);
}

inline void rd(cood &x) {
	double d;
	scanf("%lf", &d);
	x = d;
}

int main () {
	vec C;
	rd(C.x); rd(C.y); rd(C.z);
	cood r;
	rd(r);
	vec t[3];
	for(int i = 0; i < 3; i++) {
		cood alp, bet;
		rd(alp); rd(bet);
		alp = (alp / 180) * pi;
		bet = (bet / 180) * pi;
		t[i] = vec{cos(bet) * cos(alp), sin(bet) * cos(alp), sin(alp)};
	}
	vec p, v;
	rd(p.x); rd(p.y); rd(p.z);
	rd(v.x); rd(v.y); rd(v.z);
	try {
		vec in = inter(C, r, p, v);
		//printf("%.5f %.5f %.5f\n", double(in.x), double(in.y), double(in.z));
		in = in - C;
		int s = sign(in(t[0], t[1]));
		int mx = max({sign(in(t[0], t[1])), sign(in(t[1], t[2])), sign(in(t[2], t[0]))});
		int mn = min({sign(in(t[0], t[1])), sign(in(t[1], t[2])), sign(in(t[2], t[0]))});
		if(mx - mn <= 1) {
			int m1 = sign(C.mixed(C + t[0], C + t[1], C + t[2]));
			int m2 = sign((in + C).mixed(C + t[0], C + t[1], C + t[2]));
			if(m1 != 0 && m1 == m2)
				puts("NO");
			else
				puts("YES");
		} else puts("NO");
	} catch(...) {
		puts("NO");
	}
}
