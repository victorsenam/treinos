#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const ll MOD = 1e9+7;

int n;
int k;
queue<int> qu;
ll sum;

int main () {
	scanf("%d %d", &n, &k);

	if (n <= k) {
		printf("1\n");
		return 0;
	}

	sum = k;
	for (int i = 1; i <= k; i++)
		qu.push(1);

	for (int i = k+1; i < n; i++) {
		qu.push(sum);
		sum = (sum + sum)%MOD;
		sum = (((sum - qu.front())%MOD) + MOD)%MOD;
		qu.pop();
	}
	
	printf("%lld\n", sum);
}
