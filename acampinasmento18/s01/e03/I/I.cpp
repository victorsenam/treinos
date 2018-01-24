#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

#define y1 aslasd
#define y2 asdasd


int n, a, b;

const int N = 11234;
vector<pii> to[N];
int seen[N];

vector<int> ans;

bool test(int s, int t) {
	//printf("test(%d, %d)\n", s, t);
	if(s == t) {
		return true;
	}
	if(seen[s]) return false;
	seen[s] = true;
	for(pii p : to[s]) {
		if(p.first > t) continue;
		ans.pb(p.second);
		if(test(p.first, t)) return true;
		ans.pop_back();
	}
	return false;
}

void go(int W, int l[], int r[], int a, int b) {
	if(max(l[a], l[b]) < min(r[a], r[b])) return;
	//puts("BBBB");
	int i;
	for(i = 0; i <= W; i++) to[i].clear();
	for(i = 0; i < n; i++)
		if(i != a && i != b)
			to[l[i]].pb(pii(r[i], i));

	if(l[a] > l[b]) swap(a, b);
	memset(seen, 0, sizeof seen);
	ans.clear();
	if(!test(0, l[a])) return;
	//puts("ok1");
	memset(seen, 0, sizeof seen);
	ans.pb(a);
	if(!test(r[a], l[b])) return;
	//puts("ok2");
	memset(seen, 0, sizeof seen);
	ans.pb(b);
	if(!test(r[b], W)) return;
	printf("%d\n", int(ans.size()));
	for(int x : ans) printf("%d ", x + 1);
	putchar('\n');
	exit(0);
}

int x1[N], y1[N], x2[N], y2[N];
int main () {
	int i, W, H;
	scanf("%d %d", &W, &H);
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d %d %d %d", &x1[i], &y1[i], &x2[i], &y2[i]);
	scanf("%d %d", &a, &b); a--; b--;
	go(W, x1, x2, a, b);
	go(H, y1, y2, a, b);
	puts("-1");
}
