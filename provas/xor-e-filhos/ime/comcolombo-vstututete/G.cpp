#include <bits/stdc++.h>

using namespace std;

const int MAX = 1010;

bool isPrime(int num) {
	for(int i = 2; i*i <= num; i++)
		if(!(num % i)) return false;
	return true;
}

int prime[50], ips = 0, help[MAX];

int main() {
	for(int i = 2; i*i <= 1000; i++)
		if(isPrime(i)) prime[ips++] = i;
	for(int i = 2; i <= 1000; i++) {
		int num = i;
		for(int j = 0; j < ips; j++) {
			while(!(num % prime[j])) num /= prime[j];
		}
		help[i] = num;
	}
	int T;
	scanf("%d", &T);
	for(int t = 1; t <= T; t++) {
		int n, k, ans = 0;
		int sw[MAX], fre[MAX];
		int isw = 0, ifre = 0;
		scanf("%d%d", &n, &k);
		for(int i = 0; i < k; i++) {
			int x;
			bool inlist = false;
			scanf("%d", &x);
			for(int j = 0; j < ips; j++) {
				if(prime[j] == x) {
					inlist = true;
					break;
				}
			}
			if(inlist) {
				sw[isw++] = x;
			} else {
				fre[ifre++] = x;
			}
		}
		int maxi = 0;
		for(int i = 0; i < (1 << isw); i++) {
			int aux = 0;
			int lig[MAX], cnt[MAX];
			for(int j = 1; j <= n; j++) cnt[j] = lig[j] = 0;
			for(int j = 1; j <= n; j++) {
				for(int l = 0; l < isw; l++) {
					if((i) & (1 << l)) {
						if(!(j % sw[l])) {
							lig[j] ^= 1;
						}
					}
				}
				if(lig[j]) {
					cnt[help[j]]++;
					aux++;
				}
			}
			for(int j = 0; j < ifre; j++) {
				int gan = (n / fre[j]) - cnt[fre[j]];
				if(gan > 0) aux += gan;
			}
			maxi = max(maxi, aux);
		}
		printf("Case #%d: %d\n", t, maxi + ans);
	}
	return 0;
}
