#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+7;

int n;
int res[2*N];
int ns;

struct triple {
	int x, y, z;
	
	triple (vector<int> v) {
		sort(v.begin(), v.end());
		x = v[0]; y = v[1]; z = v[2];
	}

	bool operator < (const triple & o) const {
		if (x != o.x) return x < o.x;
		if (y != o.y) return y < o.y;
		return z < o.z;
	}
};

map<triple, pii> mp;

pii query (triple a) {
	if (mp.find(a) != mp.end()) return mp[a];
	printf("%d %d %d\n", a.x,a.y,a.z);
	fflush(stdout);
	char r;
	scanf(" %c", &r);
	
	if (r == 'X') return mp[a] = pii(a.x,a.y);
	if (r == 'Y') return mp[a] = pii(a.y,a.z);
	return mp[a] = pii(a.x,a.z);
}

void solve (const vector<int> & cur, int from) {
	if (cur.size() == 1) {
		res[cur[0]] = from;
		//printf("leaf %d from %d\n", cur[0], from);
		return;
	}

	int root = ns--;
	res[root] = from;
	/*
	printf("[%d :", root);
	for (int x : cur)
		printf(" %d", x);
	printf("] from %d\n", res[root]);
	*/


	vector<int> left, right;
	left.pb(cur[0]); right.pb(cur[1]);
	for (int i = 2; i < cur.size(); i++) {
		pii r = query(vector<int>({left[0], right[0], cur[i]}));

		if (r.first != cur[i] && r.second != cur[i]) {
			for (int j = 0; j < right.size(); j++)
				left.pb(right[j]);
			right.clear();
			right.pb(cur[i]);
		} else if (r.first != left[0] && r.second != left[0]) {
			right.pb(cur[i]);
		} else {
			left.pb(cur[i]);
		}
	}

	solve(left, root);
	solve(right, root);
}

int main () {
	srand(time(NULL)); rand(); rand();
	scanf("%d", &n);
	ns = 2*n-1;

	vector<int> cur(n);
	for (int i = 1; i <= n; i++)
		cur[i-1] = i;
	random_shuffle(cur.begin(), cur.end());

	solve(cur, -1);

	printf("-1\n");
	for (int i = 1; i <= 2*n-1; i++)
		printf("%d ", res[i]);
	printf("\n");
	fflush(stdout);
}
