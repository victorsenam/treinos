#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;

int n;
int a[N];

int main () {
	scanf("%d", &n);

	int lv = 0;

	for (int i = 0; i <= n; i++) {
		scanf("%d", &a[i]);
		
		if (i && a[i] > 1 && a[i-1] > 1)
			lv = i;
	}

	if (lv == 0) {
		printf("perfect\n");
		return 0;
	}

	printf("ambiguous\n");
	int st = 0;
	int qt = 0;
	for (int i = 0; i <= n; i++) {
		int cur = qt + 1;
		for (int j = 0; j < a[i]; j++) {
			printf("%d ", st);
			qt++;
		}
		st = cur;
	}
	printf("\n");

	st = qt = 0;
	for (int i = 0; i <= n; i++) {
		int cur = qt + 1;
		if (i == lv) {
			printf("%d ", st + 1);
			qt++;
		}
		for (int j = (i == lv); j < a[i]; j++) {
			printf("%d ", st);
			qt++;
		}
		st = cur;
	}
	printf("\n");

}
