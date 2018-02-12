#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 103;

int memo[N][N];
char a[N], b[N];
vector<int> ra, rb;
int n, m;

int pd (int i, int j) {
	if (i == n || j == m) return 0;
	int & me = memo[i][j];
	if (me != -1) return me;
	me = 0;
	if (a[i] == b[j]) return me = pd(i+1,j+1) + 1;
	else return me = max(pd(i+1,j),pd(i,j+1));
}

void build (int i, int j) {
	if (i == n || j == m) return;
	int me = pd(i,j);
	if (a[i] == b[j]) {
		ra.pb(i+1); rb.pb(j+1);
		build(i+1,j+1);
	} else if (pd(i+1,j) == pd(i,j)) {
		build(i+1,j);
	} else {
		build(i,j+1);
	}
}

int main () {
	memset(memo, -1, sizeof memo);
	scanf(" %s %s", a, b);
	n = strlen(a); m = strlen(b);
	build(0,0);
	printf("%d\n", pd(0,0));
	for (int x : ra)
		printf("%d ", x);
	printf("\n");
	for (int x : rb)
		printf("%d ", x);
	printf("\n");
}
