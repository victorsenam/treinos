#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int beg[256], f[256]; ll wei[256];
char s[12][12], all[10000];
int p[10];
int tot;
int cnt, ln, n;
void solve() {
	int i;
	ll t = 0;
	for(i = 0; i < tot; i++) {
		f[all[i]] = p[i];
		t += p[i] * wei[all[i]];
		if(p[i] == 0 && beg[all[i]]) return;
	}
	ll t2 = 0, w = 1;
	for(i = ln - 1; i >= 0; i--) {
		t2 += w * f[s[n - 1][i]];
		w *= 10ll;
	}
	if(t == t2) cnt++; 
}

void gen(int i) {
	if(i == tot) solve();
	for(int j = i; j < 10; j++) {
		swap(p[i], p[j]);
		gen(i + 1);
		swap(p[i], p[j]);
	}
}

int main() {
	int i, j;
	while(scanf("%d", &n) != EOF) {
		memset(beg, 0, sizeof beg);
		memset(wei, 0, sizeof wei);
		tot = 0;
		for(i = 0; i < n; i++) {
			scanf("%s", s[i]);
			beg[s[i][0]] = 1;
			strcpy(all + tot, s[i]);
			int k = strlen(s[i]);
			tot += k;
			if(i == n - 1) continue;
			ll w = 1;
			for(j = k - 1; j >= 0; j--) {
				wei[s[i][j]] += w;
				w *= 10ll;
			}
		}
		sort(all, all + tot);
		tot = unique(all, all + tot) - all;
		//for(i = 0; i < tot; i++)
		//	printf("wei[%c] = %d\n", all[i], wei[all[i]]);
		//puts("--------------");
		for(i = 0; i < 10; i++)
			p[i] = i;
		cnt = 0;
		ln = strlen(s[n - 1]);
		gen(0);
		printf("%lld\n", cnt);

	}
}
