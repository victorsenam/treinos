#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e4+7;

int n;
int a[N], acc[N];

int main () {
	scanf("%d", &n);
	for (int i = 0 ; i < n; i++) scanf("%d", &a[i]);
	for (int i = 1; i < n+n+2; i++) acc[i] = acc[i-1] + a[(i+n-1)%n];

	int mn = 0, mn_v = INT_MAX;
	for (int i = 0; i < n; i++) {
		int loc = INT_MAX;
		for (int j = 1; j < n; j++) loc = min(loc, max(acc[i+j-1] - acc[i], acc[i+n] - acc[i+j]));
		cout << loc << endl;
		if (loc < mn_v) { mn = i; mn_v = loc; }
	}
	printf("%d\n", mn+1);
}
