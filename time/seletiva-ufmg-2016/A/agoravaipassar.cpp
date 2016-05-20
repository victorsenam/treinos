#include <bits/stdc++.h>
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define DEBUG(args...) fprintf(stderr, args)
#else
#define DEBUG(args...)
#endif
using namespace std;
const int N = 123;
int a[N], b[N], n, m;
int cnt, cnt2, ans;
int fix;

int cmp (int i, int j){
	double ed = double(60-b[i])/double(a[i]-b[i]);
	double dd = double(60-b[j])/double(a[j]-b[j]);
	int esq = (60-b[i]) * (a[j]-b[j]);
	int dir = (60-b[j]) * (a[i]-b[i]);
	DEBUG("%.2f < %.2f ~ %d < %d\n",100*ed, 100*dd, esq, dir);
	int inv = (a[i]-b[i] < 0) + (a[j]-b[j] < 0);
	return (esq < dir)^(inv&1);
}

int main() {
	scanf("%d",&m);
	n = 0;
	for(int i = 0; i < m; i++, n++){
		scanf("%d %d",a+n, b+n);
		if(a[n] >= 60) cnt++;
		if(b[n] >= 60) cnt2++;
		if(min(a[n], b[n]) >= 60) {
			n--;
			fix++;
		} else if (max(a[n], b[n]) < 60) {
			n--;
		}
	}
	ans = max(cnt,cnt2);

	for(int i = 0; i < n; i++){
		cnt = 0;
		for(int j = 0; j < n; j++){
			DEBUG("Tenta %d %d\n",i,j);
			if (cmp (i,j) == cmp (j,i)) { cnt++; DEBUG("Mesmo W critico\n"); }
			else {
				if(a[j] > b[j]) { cnt += cmp(j, i); DEBUG("Reta do J crescente, somei %d\n", cmp(j,i)); }
				else { cnt += cmp(i,j); DEBUG("Reta do J crescente, somei %d\n", cmp(j,i)); }
			}
		}
		ans = max(ans,cnt+fix);
	}
	printf("%d\n",ans);

}
