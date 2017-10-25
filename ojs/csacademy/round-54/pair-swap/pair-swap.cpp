#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;

int n, k;
multiset<pii> s;
int a[N];

int main () {
	scanf("%d %d", &n, &k);

	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	for (int i = 0; i < k; i++) {
		s.insert(pii(a[i],-i));
	}

	for (int i = 0; i < n; i++) {
		if (i + k < n)
			s.insert(pii(a[i+k],-i-k));
		s.erase(s.find(pii(a[i],-i)));

		if (s.lower_bound(pii(a[i],-N)) != s.begin()) {
			pii x = *(s.begin());
			swap(a[i],a[-x.second]);
			for (int j = 0; j < n; j++)
				printf("%d ", a[j]);
			printf("\n");
			return 0;
		}
	}
	for (int i =0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}
