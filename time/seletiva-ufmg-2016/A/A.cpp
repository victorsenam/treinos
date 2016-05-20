#include <bits/stdc++.h>

using namespace std;

const int N = 107;

int a[N], b[N];
int n;

bool cmp_t (int i, int j) {
	int vi = (60-b[i])*(a[j]-b[j]);
	int vj = (60-b[j])*(a[i]-b[i]);
	bool v = (vi < vj);
	return v;
}

int main () {
	scanf("%d", &n);

	int cnt = 0;
	int cnt2 = 0;
	int maxi = 0;

	for (int i = 0; i < n; i++) {
		scanf("%d %d", a+i, b+i);
		if (b[i] >= 60) cnt++;
		if (a[i] >= 60) cnt2++;
	}

	maxi = max(cnt, cnt2);

	for (int i = 0; i < n; i++) {
		cnt = 0;

		if (a[i] < 60 && b[i] < 60) continue;
		if (a[i] == b[i]) continue;

		for (int j = 0; j < n; j++) {
			int ls = cnt;
			if (a[j] == b[j]) {
				cnt += (a[j] >= 60);
			}
			else if (cmp_t(i, j) == cmp_t(j,i)) {
				cnt++; 
			}
			else {
				if(a[j] > b[j]) {
					cnt += cmp_t(i,j);
				} else {
					cnt += cmp_t(j,i);
				}
			}
		}
		maxi = max(maxi, cnt);
	}
	printf("%d\n", maxi);
}
