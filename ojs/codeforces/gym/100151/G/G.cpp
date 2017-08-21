#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 3e4+7;

int n, s;
ll vl[2];
ll x[N], r[N], g[N], d[N];

struct evt { 
	ll t, x;
	int i;
	bool tored;

	bool operator < (const evt & ot) const { 
		if (x * ot.t == t * ot.x)
			return tored > ot.tored; 
			// se estou virando vermelho, devo vir depois, portanto, sou menor
		return x * ot.t < t * ot.x;
	}
};

ostream & operator << (ostream & os, const evt & x) {
	os << "[" << x.i << "](t:" << x.t << ",x:" << x.x << ")" << " tored? " << x.tored;
}

priority_queue<evt> pq;
int cnt;

ll res_t, res_x;
int res_cnt;

ll nextred (int i, ll p, ll q) {
	ll t = (p+q-1)/q;
	ll k = (t - d[i] + g[i] + r[i] - 1)/(g[i] + r[i]);
	return d[i] + k * (g[i] + r[i]);
}

ll nextgreen (int i, ll p, ll q) {
	ll t = p/q;
	ll k = (t - d[i] + g[i] + g[i] + r[i])/(g[i] + r[i]);
	return d[i] - g[i] + k * (g[i] + r[i]);
}

int isred (int i, ll p, ll q) {
	return (nextgreen(i, p, q) < nextred(i, p, q));
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d %d %lld %lld", &n, &s, &vl[0], &vl[1]);

	res_x = vl[1]; res_t = 1;
	cnt = 0;

	for (int i = 0; i < n; i++) {
		scanf("%lld %lld %lld %lld", &x[i], &r[i], &g[i], &d[i]);
		
		evt ev;
		ev.x = x[i];
		ev.tored = !isred(i, x[i], vl[1]);
		ev.i = i;
		if (ev.tored) {
			ev.t = nextred(i, x[i], vl[1]);
		} else {
			ev.t = nextgreen(i, x[i], vl[1]);
			cnt++;
		}

		cout << "colocando " << ev << endl;
		pq.push(ev);
	}

	res_cnt = cnt;

	while (!pq.empty()) {
		evt ev = pq.top();
		if (ev.x < vl[0] * ev.t) break;
		cout << "saindo com " << double(ev.x)/double(ev.t) << endl;

		while (!pq.empty() && !(ev < pq.top()) && !(pq.top() < ev)) {
			evt cur = pq.top();
			cout << "tira " << cur << endl;
			pq.pop();
			cout << cur.i << " fica ";

			if (cur.tored) {
				cout << "vermelho";
				cnt++;
				cur.tored = 0;
				cur.t = nextgreen(cur.i, cur.t, 1);
			} else {
				cout << "verde";
				cnt--;
				cur.tored = 1;
				cur.t = nextred(cur.i, cur.t, 1);
			}
			cout << endl;

			cout << "coloca " << cur << endl;
			pq.push(cur);
		}

		if (cnt < res_cnt) {
			res_cnt = cnt;
			res_x = ev.x;
			res_t = ev.t;
		}
	}

	printf("%.20f\n%d\n", double(res_x)/double(res_t), res_cnt);

	for (int i = 0; i < n; i++) {
		if (isred(i, x[i]*res_t, res_x)) {
			printf("%d ", i+1);
			res_cnt--;
		}
	}

	assert(res_cnt == 0);
	printf("\n");
}
