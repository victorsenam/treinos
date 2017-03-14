#include <bits/stdc++.h>

using namespace std;

const int N = 20007;

int a[N];
int n;
int t;

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);

		for (int i = 0; i < n; i++)
			scanf("%d", a+i);

		sort(a, a+n);

		int res = 0;
		for (int i = n-3; i >= 0; i-=3)
			res += a[i];
		
		printf("%d\n", res);
	}
}
