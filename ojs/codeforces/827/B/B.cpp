#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e5+7;

int n, k;
int qt[N];

int main () {
	scanf("%d %d", &n, &k);

	if (k == 2) {
		printf("%d\n", n-1);
		for (int i = 1; i < n; i++)
			printf("%d %d\n", i, i+1);
	} else {
		for (int i = 0; i < k; i++)
			qt[i] = 1;
		for (int i = 0; i < n-k-1; i++)
			qt[i%k]++;

		int d = qt[0] + qt[1];
		printf("%d\n", d);

		int cur = 2;
		for (int i = 0; i < k; i++) {
			int ls = 1;
			for (int j = 0; j < qt[i]; j++) {
				printf("%d %d\n", ls, cur);
				ls = cur;
				cur++;
			}
		}
	}
	
}
