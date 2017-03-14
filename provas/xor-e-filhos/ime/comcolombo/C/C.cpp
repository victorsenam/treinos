#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXL = 1010;

char str[MAXL];
int pos[MAXL];

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf(" %s", str);
		int n = strlen(str), ans = 0, k = 0;
		for(int i = 0; i < n; i++) {
			if(str[i] != 'A') pos[k++] = i; 
			ans += min(str[i] - 'A', 'Z' - str[i] + 1);
		}
		if(k != 0) {
			int ans2 = min(n - pos[0], pos[k - 1]);
			for(int i = 0; i < k - 1; i++) {
				ans2 = min(ans2, min(2*pos[i] + n - pos[i + 1], pos[i] + 2*(n - pos[i + 1])));
			}
			ans += ans2;
		}
		printf("%d\n", ans);
	}
	return 0;
}
