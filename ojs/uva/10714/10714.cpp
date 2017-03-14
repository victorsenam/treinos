#include <bits/stdc++.h>

using namespace std;

const int N = 1000007;
typedef long long int num;

int pos[N];
bool dir[N];
int t, n, l;
int mini, maxi;

int main () {
	scanf("%d", &t);

	while (t--) {
		scanf("%d %d", &l, &n);
		mini = 0;
		maxi = 0;

		for (int i = 0; i < n; i++) {
			scanf("%d", pos+i);

			mini = max(min(pos[i], l-pos[i]), mini);
			maxi = max(maxi, pos[i]);
			maxi = max(maxi, l-pos[i]);
		}

		printf("%d %d\n", mini, maxi);
	}
}
