#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

char let[] = "MARCH";
char str[20];
ll cnt[6];
int n;

int main () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf(" %s", str);
		for (int j = 0; j < 5; j++)
			if (str[0] == let[j])
				cnt[j]++;
	}

	ll res = 0;
	for (int i = 0; i < 5; i++) for (int j = i+1; j < 5; j++) for (int k = j+1; k < 5; k++)
		res += cnt[i]*cnt[j]*cnt[k];
	printf("%lld\n", res);
}
