#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 23;
const int S = 2e6+7;
int a[N];
int n;
int v[N];
vector<int> r[3];
int sz[3];

void printa (int a) {
	return;
	for (int i = 0; i < sz[a]; i++)
		cout << " " << r[a][i];
}

void gen (int p) {
	for (int i = 0; i < a[p]; i++)
		r[1][i] = v[p];
	sz[1] = a[p];
	cout << "gen " << p << "(" << a[p] << ") : ";
	printa(1);
	cout << endl;
}

void rec (int a, int b) {
	swap(r[a], r[b]);
	swap(sz[a], sz[b]);
}

void mix () {
	int a = 0, b = 1;
	sz[2] = 0;
	if (sz[a]&1) swap(a,b);
	cout << "join " << a << "(" << sz[a] << ") with " << b << "(" << sz[b] << ")" << endl;

	if (sz[a]&1) {
		for (int i = 0; i < sz[a] - 1; i += 2) {
			for (int j = 0; j < sz[b] - 2; j++)
				r[2][sz[2]++] = r[b][j];
			r[2][sz[2]++] = r[a][i];
			for (int j = sz[b] - 3; j >= 0; j--)
				r[2][sz[2]++] = -r[b][j];
			r[2][sz[2]++] = r[a][i+1];
		}
		for (int j = 0; j < sz[b]-1; j++)
			r[2][sz[2]++] = r[b][j];
		for (int i = sz[a]-2; i >= 0; i--)
			r[2][sz[2]++] = -r[a][i];
		r[2][sz[2]++] = r[b][sz[b]-1];
	} else {
		for (int i = 0; i < sz[a]; i += 2) {
			for (int j = 0; j < sz[b]-1; j++)
				r[2][sz[2]++] = r[b][j];
			r[2][sz[2]++] = r[a][i];
			for (int j = sz[b] - 2; j >= 0; j--)
				r[2][sz[2]++] = -r[b][j];
			r[2][sz[2]++] = r[a][i+1];
		}
	}

	cout << "result ";
	printa(2);
	cout << endl;
	assert(sz[2] == sz[a]*sz[b]);
	rec(0,2);
}

int main () {
	scanf("%d", &n);
	int vv = 1;

	for (int i = 0; i <= 2; i++)
		r[i].resize(S);

	for (int i = 0; i < n; i++, vv++) {
		scanf("%d", &a[i]);
		if (a[i] == 1) {
			i--;
			n--;
		} else {
			v[i] = vv;
		}
	}

	gen(0);
	rec(0,1);
	for (int i = 1; i < n; i++) {
		gen(i);
		mix();
	}

	for (int i = 0; i < sz[0]; i++)
		printf("%d %d\n", abs(r[0][i]), r[0][i]/abs(r[0][i]));
}
