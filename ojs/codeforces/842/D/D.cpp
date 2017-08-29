#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 3e5+7;

int n, m;
int x, y;
int a[N];

int countless (int v) {
	int cnt = 0;
	//printf("COUNT %d\n", v);
	for (int i = 22; i >= 0; i--) {
		if (v&(1<<i)) {
			int p = (1<<23) - (1 << i);
			int s = ((v^x)&p);
			s ^= (1<<i);
			int cur = lower_bound(a, a+n, s + (1<<i)) - lower_bound(a, a+n, s);
			//printf("%d nums between %d and %d\n", cur, s, s + (1<<i));
			cnt += cur;
		}
	}
	//printf("cnt = %d\n", cnt);
	return cnt;
}

int main () {
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);

	sort(a, a+n);
	n = unique(a, a+n) - a;

	x = 0;
	for (int i = 0; i < m; i++) {
		scanf("%d", &y);
		x ^= y;
		//printf("XOR %d\n", x);

		int res = 0;
		int cnt = 0;

		for (int i = 22; i >= 0; i--) {
			int p = (1<<23) - (1 << i);
			int s = ((res^x)&p);
			//s ^= (1<<i);
			int cur = lower_bound(a, a+n, s + (1<<i)) - lower_bound(a, a+n, s);
			
			//printf("[%d,%d) -> %d || ", s, s+(1<<i), cur);
			//printf("cnt(%d) = %d\n", res + (1<<i), cur+cnt);
			if (cur + cnt >= res + (1<<i)) {
				res += (1<<i);
				cnt += cur;
			}
		}

		printf("%d\n", res);
	}
}
