#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5 + 7;
int amt[N];
int n, m;
int v[N];

int lis[N];
int a[N], b[N];

int main () {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		int l, r;
		scanf("%d %d", &l, &r);
		v[r]++; v[l-1]--;
	}

	int mx = 0;
	for (int i = m; i >= 1; i--) {
		v[i] += v[i+1];
	}

	int ss = 0;
	for (int i = 1; i <= m; i++) {
		//cout << v[i] << " ";
		int p = upper_bound(lis, lis+ss, v[i]) - lis;
		lis[p] = v[i];
		if (ss == p) ss++;
		a[i] = p+1;
	}
	//cout << endl;
	reverse(v+1,v+m+1);
	ss = 0;
	for (int i = 1; i <= m; i++) {
		int p = upper_bound(lis, lis+ss, v[i]) - lis;
		lis[p] = v[i];
		if (ss == p) ss++;
		b[i] = p+1;
	}
	reverse(b+1,b+m+1);

	for (int i = 1; i <= m; i++) {
		//cout << a[i] << " " << b[i] << endl;
		mx = max(mx, a[i] + b[i] - 1);
	}
	printf("%d\n", mx);

}
