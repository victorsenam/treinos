#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const ll INF = 1e15;
const int N = 503;
const int MM = 20006;

int M;
int n, k;
ll a, d; int c;
bool cur;
ll dp[2][MM];
int i;

typedef ll num; const num eps = 0;
// XXX double warnings means there's some specific integer operation (+1, lo<hi, etc...), not precision-related
struct line {
	int j; // qual furniture, tira até onde
	inline ll cost (ll x) const {
		//assert(x >= 0 && x <= c[i]);
		return a*x - d*x*(x-1)/2;
	}
	inline num operator () (int k) const {
		return dp[!cur][j] + cost(k-j);
	}
	//bool operator < (const line & ot) const { return a > ot.a; } // decreasing slope, if function ties, the smallest in this order is chosen
};
line qu[MM+MM];
struct envelope { // min envelope, the first element is the best at the beggining
	int qi, qf; num lo, hi; envelope (num a, num b) : lo(a), hi(b) {qi = qf = MM;}
	num inter (line a, line b) { // first point where b beats (properly) a XXX double
		/*swap(a,b);
		ll up = 2ll*(dp[!cur][b.j]-dp[!cur][a.j]-::a*(a.j-b.j)) + a.j*(a.j+1) - b.j*(b.j+1);
		ll dw = 2ll*::d*(a.j - b.j);
		ll r = up/dw + 1;
		return min(max(r,lo),hi+1);*/
		num lo = this->lo; num hi = this->hi + 1;
		while (lo < hi) {
			num md = lo + (hi - lo)/2;
			if (a(md) <= b(md)) lo = md+1;
			else hi = md;
		}
		return lo;
	}
	void push_back (line l) { // insert a line that is best at hi or never
		if (qf > qi && qu[qf-1](hi) <= l(hi)) return;
		for (num x; qf > qi; qf--) {
			x = (qf==qi+1?lo:inter(qu[qf-2],qu[qf-1]));
			if (l(x) >= qu[qf-1](x)) break;
		}
		qu[qf++] = l;
	}
	void push_front (line l) { // insert a line that is best at lo or never
		if (qf > qi && qu[qi](lo) < l(lo)) return;
		for (num x; qf > qi; qi++) {
			x = (qf==qi+1?hi:inter(qu[qi],qu[qi+1]));
			if (l(x) > qu[qi](x)) break;
		}
		qu[--qi] = l;
	}
	inline line pop_front (num lo) {
		for (this->lo = lo; qf > qi+1 && qu[qi](lo) > qu[qi+1](lo); qi++);
	}
	inline line pop_back (num hi) {
		for (this->hi = hi; qf > qi+1 && qu[qf-2](hi) <= qu[qf-1](hi); qf--);
	}
};

int ia[N], id[N], ic[N];
int ik[N];

int main () {
	scanf("%d %d", &n, &k);
	M = 10;
	for (int i = 0; i < n; i++) scanf("%d %d %d", &ia[i], &id[i], &ic[i]);
	for (int i = 0; i < k; i++) { scanf("%d", &ik[i]); M = max(M,ik[i]); }
	M += 2;
	for (int i = 1; i < M; i++) dp[1][i] = INF;

	for (i = 0; i < n; i++) {
		a = ia[i]; d = id[i]; c = ic[i];
		cur = (i&1);
		for (int j = 0; j < M; j++)
			dp[cur][j] = INF;
		
		for (int j = 0; j < M; j += c+1) {
			int k = j;
			for (envelope env(j,j+c); k < M && k <= j + c; k++) {
				env.pop_front(k);
				env.push_front({k});
				dp[cur][k] = min(dp[cur][k],qu[env.qi](k));
			}

			envelope env(j+c+1, j+c+c);
			if (env.hi >= M) env.hi = M-1;
			if (env.lo > env.hi) continue;

			for (k = env.hi+1; k - c < j + c; k++)
				env.push_front({k-c});

			for (k = env.hi; k > j+c; k--) {
				env.pop_back(k);
				env.push_back({k-c});
				dp[cur][k] = qu[env.qf-1](k);
			}
		}
	}

	for (int i = 0; i < k; i++)
		printf("%lld\n", dp[!(n&1)][ik[i]]);
}
