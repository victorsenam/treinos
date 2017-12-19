#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 200;

vector<int> p, q;
int n;

vector<int> sum (vector<int> a, vector<int> & b) {
	if (b.size() > a.size()) a.resize(b.size(),0);

	for (int i = 0; i < b.size(); i++)
		a[i] += b[i];
	return a;
}

vector<int> sub (vector<int> a, vector<int> & b) {
	if (b.size() > a.size()) a.resize(b.size(),0);

	for (int i = 0; i < b.size(); i++)
		a[i] -= b[i];
	return a;
}

vector<int> shift (vector<int> a) {
	a.pb(0);
	for (int i = a.size() - 1; i > 0; i--)
		a[i] = a[i-1];
	a[0] = 0;
	return a;
}

int main () {
	scanf("%d", &n);
	p.pb(1); q.pb(0);

	for (int i = 0; i < n; i++) {
		vector<int> ne = sum(shift(p),q);
		bool ok = 1;
		for (int x : ne)
			ok &= (abs(x) <= 1);
		if (!ok) {
			ne = sub(shift(p),q);
			ok = 1;
			for (int x : ne)
				ok &= (abs(x) <= 1);
			assert(ok);
		}
		q = p;
		p = ne;
	}

	printf("%d\n", (int) p.size()-1);
	for (int i = 0; i < p.size(); i++)
		printf("%d ", p[i]);
	printf("\n");
	printf("%d\n", (int) q.size()-1);
	for (int i = 0; i < q.size(); i++)
		printf("%d ", q[i]);
	printf("\n");
}
