#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 3e5+7;

int n;
ll v[N];
int p[N], q[N];
int sq;

namespace qr {
	int n;
	int ans[N][3];
	int l[N], r[N];

	int p[N];
	int cur;
};

int turn;
int _pr[N], _nx[N], _vs[N];
int s_pr[N], s_nx[N];

int & pr (int i) {
	if (_vs[i] != turn) _pr[i] = s_pr[i], _nx[i] = s_nx[i], _vs[i] = turn;
	return _pr[i];
}
int & nx (int i) {
	if (_vs[i] != turn) _pr[i] = s_pr[i], _nx[i] = s_nx[i], _vs[i] = turn;
	return _nx[i];
}

int rem (int i,bool save = false) {
	assert(i >= 0);
	if (pr(i) != -1) { nx(pr(i)) = nx(i); if (save) s_nx[pr(i)] = nx(pr(i)); }
	if (nx(i) != -1) { pr(nx(i)) = pr(i); if (save) s_pr[nx(i)] = pr(nx(i)); }
	pr(i) = nx(i) = -2; if (save) { s_pr[i] = s_nx[i] = -2; }
}

int go (int i, int cur) {
	assert(pr(i) != -2);
	int c = i;
	int b = pr(c);
	if (b == -1) return 0;
	int a = pr(b);
	if (a == -1) return 0;
	if (v[c] >= v[a] + v[b]) return 0;
	qr::ans[cur][0] = a;
	qr::ans[cur][1] = b;
	qr::ans[cur][2] = c;
	return 1;
}

int main () {
	scanf("%d %d", &n, &qr::n);
	sq = sqrt(n);

	for (int i = 0; i < n; i++) {
		scanf("%lld", &v[i]);
		p[i] = i;
	}
	sort(p, p+n, [] (int i, int j) { return v[i] < v[j]; });
	for (int i = 0; i < n; i++) { q[p[i]] = i; }

	for (int i = 0; i < qr::n; i++) {
		scanf("%d %d", &qr::l[i], &qr::r[i]);
		qr::l[i]--; qr::r[i]--;
		qr::p[i] = i;
	}
	sort(qr::p, qr::p+qr::n, [] (int i, int j) { return pii(qr::l[i]/sq,-qr::r[i]) < pii(qr::l[j]/sq,-qr::r[j]); });
	qr::cur = 0;

	for (int i = 0; i < n; i += sq) {
		turn++;
		for (int k = 0; k < n; k++) {
			s_pr[k] = (q[k]>0)?p[q[k]-1]:-1;
			s_nx[k] = (q[k]<n-1)?p[q[k]+1]:-1;
		}
		for (int j = 0; j < i; j++) rem(j,true);

		int ts = n-1;
		for (int j = n-1; j >= i; j--) {
			while (qr::cur < qr::n && qr::l[qr::p[qr::cur]]/sq == i/sq && qr::r[qr::p[qr::cur]] == j) {
				turn++;			
				int cur = qr::p[qr::cur];
				for (int k = i; k < qr::l[cur]; k++) rem(k);
				//cout << "[" << qr::l[cur] << " " << qr::r[cur] << "] ";
				//for (int k = 0; k < n; k++) cout << pr(k) << "<" << k << ">" << nx(k) << " ";
				//cout << endl;
				ts = min(ts,j);
				bool ok = 0;
				qr::ans[cur][0] = -1;
				while (ts/sq > i/sq) {
					if (ok = go(ts,cur)) break;
					ts--;
				}
				for (int k = qr::l[cur]; !ok && (k-4)/sq <= i/sq && k <= j; k++) ok = go(k,cur);
				qr::cur++;
			}
			turn++;			
			rem(j,true);
		}
	}

	for (int i = 0; i < qr::n; i++) {
		if (qr::ans[i][0] == -1) printf("-1\n");
		else printf("%d %d %d\n", qr::ans[i][0]+1, qr::ans[i][1]+1, qr::ans[i][2]+1);
	}
}
