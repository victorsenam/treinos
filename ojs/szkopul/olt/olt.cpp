#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+7;
const char dr[] = "SENW";

typedef ll cood;
cood eps = 0;

struct vec { 
	cood x, y;

	vec () {}
	vec (cood a, cood b) : x(a), y(b) {}
	friend ostream& operator<<(ostream& os, vec o);

	vec operator - (vec o)
	{ return vec(x - o.x, y - o.y); }
	vec operator + (vec o)
	{ return vec(x + o.x, y + o.y); }
	vec operator / (cood a)
	{ return vec(x/a, y/a); }
	cood operator ^ (vec o)
	{ return x * o.y - y * o.x; }
	cood operator * (vec o)
	{ return x * o.x + y * o.y; }
	cood sq (vec o = vec())
	{ return ((*this)-o)*((*this)-o); }

	cood ar (vec a, vec b) // ccw signed area (positive if this is to the left of ab)
	{ return (b - a) ^ ((*this) - a); }
	int sd (vec a, vec b) // which side is this from ab? (-1 left, 0 over, 1 right)
	{ cood o = ar(a, b); return (o < -eps) - (eps < o); }

	// on which half plane is this point?
	// 0 is upper half plane (y > 0) and (x,0) where x >= 0, 1 is otherwise
	inline bool halfplane ()
	{ return (y < eps || (abs(y) <= eps && x < eps)); }

	// full ordering (ccw angle from this+(1,0), distance to this)
	// is a < b?
	// PRECISION : ok with double if norm in [-1e9,5e3]
	inline bool compare (vec a, vec b) {
		if ((a-(*this)).halfplane() != (b-(*this)).halfplane())
			return (b-(*this)).halfplane();
		return sd(a,b) < 0;
	}

	vec flip () {
		return vec({ y, -x });
	}
};
ostream& operator << (ostream & os, vec a) {
	return os << "(" << a.x << "," << a.y << ")";
}

int n;
vec v[N][2]; char d[N];
int cnt[N];
bool isa[N];
vec anc;
int yes;

struct evt { 
	int i, ty;
	vec p;
	friend ostream& operator<<(ostream& os, evt o);
	
	evt () {}
	evt (int a, int b) { 
		i = a; ty = b;
		if (ty == -1)
			p = vec({v[i][0].x, (3*v[i][0].y + v[i][1].y)/4});
		else if (ty == -2)
			p = vec({v[i][0].x, (3*v[i][1].y + v[i][0].y)/4});
		else if (ty == 1)
			p = vec({v[i][1].x, v[i][0].y});
		else if (ty == 3)
			p = vec({v[i][0].x, v[i][1].y});
		else
			p = v[i][!!ty];
	}

	bool operator < (const evt & ot) const {
		return anc.sd(p, ot.p) < 0;
	}
};
ostream& operator << (ostream & os, evt a) {
	return os << "[" << a.i+1 << " " << a.ty << "](" << a.p.flip().x/4. << "," << a.p.flip().y/4. << ")";
}


evt p[4*N];
int ps;

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2; j++) {
			scanf("%d %d", &v[i][j].x, &v[i][j].y);
			v[i][j].x *= 4;
			v[i][j].y *= 4;
		}
		scanf(" %c", &d[i]);
	}

	for (int k = 0; k < 4; k++) { 
		for (int i = 0; i < n; i++) {
			v[i][0] = v[i][0].flip();
			v[i][1] = v[i][1].flip();
			swap(v[i][0].x, v[i][1].x);
		}

		for (int i = 0; i < n; i++) {
			if (d[i] != dr[k]) continue;
			cout << "FROM " << i + 1 << endl;
			ps = 0;
			
			anc = (v[i][0] + v[i][1])/2;
			vec ini = evt({ i, -1 }).p;
			vec end = evt({ i, -2 }).p;

			int qt = 0;
			for (int j = 0; j < n; j++) {
				cnt[j] = 0;
				if (i == j || v[j][0].x >= v[i][0].x)
					continue;
				for (int t = 0; t < 4; t++) {
					p[ps] = evt({ j, t });

					if (!anc.compare(ini, p[ps].p)) {
						if (cnt[p[ps].i] == 0)
							qt++;
						else if (cnt[p[ps].i] == 3)
							qt--;
						cnt[p[ps].i]++;
					} else if (anc.compare(p[ps].p, end)) {
						ps++;
					}
				}
			}
			sort(p, p+ps);

			if (!qt) {
				isa[i] = 1;
				yes++;
			}

			for (int j = 0; !isa[i] && j < ps;) {
				evt cur = p[j];
				while (j < ps && !(cur < p[j])) {
					cout << p[j] << " ";
					if (cnt[p[j].i] == 0)
						qt++;
					else if (cnt[p[j].i] == 3)
						qt--;
					cnt[p[j].i]++;
					j++;
				}
				cout << endl;

				if (!qt) {
					isa[i] = 1;
					yes++;
				}
			}
		}
	}
	
	if (!yes) {
		printf("BRAK\n");
	} else {
		for (int i = 0; i < n; i++)
			if (isa[i])
				printf("%d\n", i+1);
	}
}
