#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

vector<int> oc[1123456];
int lst;
inline int qt(int l, int r, int x) {
	lst = x;
	return upper_bound(oc[x].begin(), oc[x].end(), r) - lower_bound(oc[x].begin(), oc[x].end(), l);
}

int a[1123456];

int main () {
	srand(time(NULL));
	int i, n, m, l, r;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		oc[a[i]].pb(i);
	}
	while(m--) {
		scanf("%d %d", &l, &r); l--; r--;
		int k;
		for(k = 0; k < 22; k++)
			if(qt(l, r, a[rand() % (r - l + 1) + l]) * 2 > (r - l + 1))
				break;
		if(k < 22) printf("%d\n", lst);
		else puts("0");
	}

}
