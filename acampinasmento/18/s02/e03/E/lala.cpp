#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 503;
const int MM = 20006;

int M;
int n, k;
ll a, d; int c;
bool cur;
ll dp[2][MM];
int i;

template<typename line> struct fila {
	line qu[MM+MM];
	int qi, qf;
	bool empty () { return qi == qf; }
	int size () { return qf - qi; }
	line front () { return qu[qi]; }
	line back () { return qu[qf]; }
	line * begin () { return qu+qi; }
	line * end() { return qu+qf; }
	void push_back (line a) { qu[qf++] = a; }
	void push_front (line a) { qu[--qi] = a; }
	void pop_front () { qi++; } void pop_back () { qf--; }
};

typedef ll num; const num eps = 0; num INF = 1e15;
// XXX double: indicates operations specific to integers (+1,lo<hi,...), non precision-related
template<typename line> struct envelope { // if line is used, the template tag can be simply removed
	fila<line> & q; num lo,hi; envelope (fila<line> & qq, num _lo, num _hi) : q(qq), lo(_lo), hi(_hi) {q.qi = q.qf = MM;}
	void push_front (line l) { assert(q.empty() || !(q.front()<l)); // l is best at lo or never
		if (!q.empty() && q.front()(lo) < l(lo)) return;
		for (num x; q.size(); q.pop_front()) {
			x = (q.size()<=1?hi:min(max(lo,q.front().inter(*next(q.begin()))-1),hi+1));
			if (l(x) > q.front()(x)) break;
		}
		q.push_front(l);
	}
	void push_back (line l) { assert(q.empty() || !(l<q.back())); // l is best at hi or never
		if (!q.empty() && q.back()(hi) <= l(hi)) return;
		for (num x; q.size(); q.pop_back()) {
			x = (q.size()<=1?lo:min(max(lo,prev(prev(q.end()))->inter(q.back())),hi+1));
			if (l(x) >= q.back()(x)) break;
		}
		q.push_back(l);
	}
	void pop_front (num _lo) { assert(lo<=_lo+eps); for(lo=_lo;q.size()>1&&q.front()(lo)>(*next(q.begin()))(lo);q.pop_front()); } // always amort. O(1)
	void pop_back (num _hi) { assert(hi>=_hi-eps); for(hi=_hi;q.size()>1&&(*prev(prev(q.end())))(hi)<=q.back()(hi);q.pop_back()); } // always amort. O(1)
	line get (num x) { return (*lower_bound(q.begin(),q.end()-1,q.front(),[x](line & a, const line & o){ return a(x)>(*((&a)+1))(x); })); } // always O(lg(n))
};
struct generic_line { // change only parameters and () for any viable functions, env operations in amort. O(lg(hi-lo))
	envelope<generic_line> * env; int j; num operator () (int k) const { return dp[!cur][j] + a*(k-j) - d*(k-j)*(k-j-1)/2; }
	bool operator < (const generic_line & ot) const { return (*this)(env->lo) < ot(env->lo) && (*this)(env->hi) > ot(env->hi); } // first element is best at lo
	num inter (generic_line o) { assert(!(o<(*this)));
		num lo = env->lo; num hi = env->hi+1;
		while (lo < hi) {
			num md = lo+(hi-lo)/2;
			if ((*this)(md)<=o(md)) lo = md+1;
			else hi = md;
		}
		return lo;
	}
};

int ia[N], id[N], ic[N];
int ik[N];
fila<generic_line> gfl;

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
			for (envelope<generic_line> env(gfl,j,j+c); k < M && k <= j + c; k++) {
				env.pop_front(k);
				env.push_front({&env,k});
				dp[cur][k] = min(dp[cur][k],env.q.front()(k));
			}

			envelope<generic_line> env(gfl, j+c+1, j+c+c);
			if (env.hi >= M) env.hi = M-1;
			if (env.lo > env.hi) continue;

			for (k = env.hi+1; k - c < j + c; k++)
				env.push_front({&env,k-c});

			for (k = env.hi; k > j+c; k--) {
				env.pop_back(k);
				env.push_back({&env,k-c});
				dp[cur][k] = env.q.back()(k);
			}
		}
	}

	for (int i = 0; i < k; i++)
		printf("%lld\n", dp[!(n&1)][ik[i]]);
}
