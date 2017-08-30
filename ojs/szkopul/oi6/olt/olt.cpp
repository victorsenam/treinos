#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

// NOT STANDART FROM HERE

// area de calota 2.pi.R.h (h altura)
// volume de calota pi.h/6 * (3r^2 + h^2)

typedef ll cood;
cood eps = 0;

const double pi = acos(-1.);

struct vec { // vector
	// === BASIC ===
	cood x, y;
	vec () : x(0), y(0) {}
	vec (cood a, cood b) : x(a), y(b) {}
	friend ostream& operator<<(ostream& os, vec o);
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
	{ return sqrt(sq(o)); }

	inline cood ar (vec a, vec b) // ccw signed area (positive if this is to the left of ab)
	{ return (b - a) ^ ((*this) - a); }
	inline int sd (vec a, vec b) // which side is this from ab? (-1 left, 0 over, 1 right)
	{ cood o = ar(a, b); return (o < -eps) - (eps < o); }

	// === ADVANCED ===
	// rotate ccw by a (fails with ll)
	vec rotate (double a)
	{ return vec(cos(a) * x - sin(a) * y, sin(a) * x + cos(a) * y); }

	// divide the plane relative to anc
	// 0 if the ccw angle from anc to this is in [0,pi) and 1 otherwise, origin goes to 0
	inline bool halfplane (vec anc = vec(1,0)) {
		int l = sd(vec(), anc);
		if (l == 0)
			return (x < -eps);
		return (l == 1);
	}

	// ordering (ccw angle from anc, distance to origin)
	// is this < o?
	// PRECISION : ok with double if norm in [-1e4,1e3]
	inline bool compare (vec o, vec anc = vec(1,0)) {
		bool s[2] = {halfplane(anc), o.halfplane(anc)};
		if (s[0] != s[1])
			return s[0] < s[1];

		int l = sd(o, vec());
		if (l == 0)
			return sq() - o.sq() < -eps;
		return (l == -1);
	}

	// is this inside segment st? (tip of segment included, change for < -eps otherwise)
	bool in_seg (vec s, vec t)
	{ return (sd(s, t) == 0) && !(eps < ((*this) - s) * ((*this) - t)); }
};
ostream& operator<<(ostream& os, vec o)
{ return os << '(' << o.x/4. << ", " << o.y/4. << ')'; }

const int N = 2e3+7;

int n;
vec v[N][2], inp[N][2];
char c[N];
int fnd[N];
vec alt;

struct evt {
	int i;
	vec p;
};

int evs;
evt ev[4*N];

void flip (int j) {
	vec r[2] = {v[j][0], v[j][1]};
	
	v[j][0].x = -r[1].x;
	v[j][0].y = r[0].y;
	v[j][1].x = -r[0].x;
	v[j][1].y = r[1].y;
}

void turn (int j) {
	vec r[2] = {v[j][0], v[j][1]};

	v[j][0].x = -r[0].y;
	v[j][0].y = r[1].x;
	v[j][1].x = -r[1].y;
	v[j][1].y = r[0].x;
}

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		for (int k = 0; k < 2; k++) {
			scanf("%lld %lld", &inp[i][k].x, &inp[i][k].y);
			inp[i][k].x *= 4;
			inp[i][k].y *= 4;
		}
		scanf(" %c", &c[i]);
	}

	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			v[j][0] = inp[j][0];
			v[j][1] = inp[j][1];
			
			if (c[i] == 'S' || c[i] == 'N') 
				turn(j);
			if (c[i] == 'W' || c[i] == 'N')
				flip(j);

		}
		
		alt = vec((v[i][0].x + v[i][1].x)/2, (v[i][0].y + v[i][1].y)/2);

		evs = 0;
		ev[evs].i = i;
		ev[evs++].p = vec(v[i][1].x, (v[i][0].y + 3*v[i][1].y)/4);
		ev[evs].i = i;
		ev[evs++].p = vec(v[i][1].x, (3*v[i][0].y + v[i][1].y)/4);

		int opn = 0;
		for (int j = 0; j < n; j++) {
			fnd[j] = 0;
			if (i == j || v[j][1].x <= v[i][0].x)
				continue;

			vec mn, mx;
			mn = v[j][0];
			mx = v[j][1];

			if (alt.sd(mx, mn) < 0)
				swap(mx, mn);

			vec cur(v[j][0].x, v[j][1].y);
			if (alt.sd(cur,mn) < 0)
				mn = cur;
			else if (alt.sd(mx,cur) < 0)
				mx = cur;

			cur = vec(v[j][1].x, v[j][0].y);
			if (alt.sd(cur,mn) < 0)
				mn = cur;
			else if (alt.sd(mx,cur) < 0)
				mx = cur;

			if (alt.sd(mn, ev[0].p) < 0) {
				fnd[j]++;
				opn++;
			} else if (alt.sd(mn, ev[1].p) <= 0) {
				ev[evs++] = evt({j,mn});
			}
			if (alt.sd(mx, ev[0].p) < 0) {
				if (fnd[j]) {
					fnd[j]++;
					opn--;
				}
			} else if (alt.sd(mx, ev[1].p) <= 0) {
				ev[evs++] = evt({j,mx});
			}
		}

		sort(ev, ev+evs, [] (evt a, evt b) {
			return alt.sd(a.p, b.p) < 0;
		});

		for (int j = 0; j < evs;) {
			vec fs = ev[j].p;
			while (j < evs && alt.sd(ev[j].p,fs) == 0) {
				if (ev[j].i != i) {
					if (fnd[ev[j].i] == 0)
						opn++;
					if (fnd[ev[j].i] == 1)
						opn--;
				}
				fnd[ev[j].i]++;
				j++;
			}
			cout << endl;

			if (opn == 0 && fnd[i] == 1) {
				cnt++;
				printf("%d\n", i+1);
				break;
			}
		}
	}

	if (cnt == 0)
		printf("BRAK\n");
}
