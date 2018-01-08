#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back


int main () {
	int ts;
	cin >> ts;
	while (ts--) {
		int a[4];
		for (int i = 0; i < 4; i++)
			cin >> a[i];
		sort(a, a+4);
		if (a[0] == a[1] && a[2] == a[3])
			printf("YES\n");
		else
			printf("NO\n");

	}
}
