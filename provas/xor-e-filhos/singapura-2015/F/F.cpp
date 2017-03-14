#include <bits/stdc++.h>

using namespace std;


const int N = 1007;
int n;
int l[N], r[N], p[N];

bool cmp_t (int i, int j) {
	if (r[i] == r[j])
		return l[i] > l[j];
	return r[i] < r[j];
}

int main () {
	while(scanf("%d", &n) != EOF){

		for (int i = 0; i < n; i++) {
			scanf("%d %d", l+i, r+i);
			p[i] = i;
		}

		sort(p, p+n, cmp_t);
		int ans = 0;
		int last = -1;
		for (int i = 0; i < n; i++) {
			if(last >= l[p[i]]) continue;
			ans++;
			last = r[p[i]];
		}
		printf("%d\n",ans);
	}
}
