#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e3 + 3;
const int M = 4*N;

int n, m;
int hd[N], nx[M], to[M], es;

int vs[N];
stack<int> st;
int pre[N], low[N], os;
int sc[N], cs;

int ssc (int fr) {
	int u = to[fr];
	if (vs[u] == 1)
		return pre[u];
	if (vs[u] == 2)
		return N+N;
	int cn = 0;

	cout << "open " << u << endl;

	vs[u] = 1;
	pre[u] = low[u] = os++;
	st.push(u);

	for (int ed = hd[u]; ed; ed = nx[ed]) {
		cn++;
		low[u] = min(low[u], ssc(ed));
	}

	if (low[u] == pre[u]) {
		cout << "make component from " << u << ":";
		while (vs[u] != 2) {
			int v = st.top();
			cout << " " << v;
			vs[v] = 2;
			sc[v] = cs;
			st.pop();
		}
		cout << endl;
		cs++;
	}

	cout << "close " << u << endl;
	vs[u] = 2;

	return low[u];
}

int main () {
	while (scanf("%d %d", &n, &m) != EOF) {
		cout << "=========================" << endl;
		es = 1; cs = 1; os = 0;
		for (int i = 0; i < n+n; i++) {
			vs[i] = 0;
			hd[i] = 0;
		}

		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			a = (abs(a)-1)*2 + (a < 0);
			b = (abs(b)-1)*2 + (b < 0);

			nx[es] = hd[a^1]; to[es] = b; hd[a^1] = es++;
			nx[es] = hd[b^1]; to[es] = a; hd[b^1] = es++;
		}

		nx[es] = hd[1]; to[es] = 0; hd[1] = es++;

		bool ok = 1;
		for (int i = 0; ok && i < n+n; i++) {
			to[0] = i;
			ssc(0);

			if ((i&1) && sc[i] == sc[i-1])
				ok = 0;
		}
		
		if (ok)
			printf("yes\n");
		else
			printf("no\n");
	}
}
