#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int t;
int n;
int cn[4];

int main () {
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 0; i < 4; i++)
			cn[i] = 0;
		for (int i = 0; i < n; i++) {
			int a;
			cin >> a;
			cn[a%4]++;
		}

		int res = min(cn[1],cn[3]);
		cn[1] -= res; cn[3] -= res;

		if ((cn[1] + cn[3])%2) {
			printf("-1\n");
			continue;
		}

		res += (cn[1] + cn[3])/2;
		cn[2] += (cn[1] + cn[3])/2;
		
		if (cn[2]%2) {
			printf("-1\n");
			continue;
		}
		res += cn[2]/2;
		printf("%d\n", res);
	}
}
