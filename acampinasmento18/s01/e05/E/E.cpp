#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+4;
const int K = 1e4+4;
const ll MOD = 1e9+9;

int f[K][N];
ll c[K][N];
int k;
int n;
char str[N];

int main () {
	scanf("%s", str+1);
	n = strlen(str+1);
	scanf("%d", &k);

	f[0][0] = f[0][1] = 0;
	for (int i = 2; i <= n; i++) {
		f[0][i] = f[0][i-1];
		while (f[0][i] && str[f[0][i]+1] != str[i])
			f[0][i] = f[0][f[0][i]];
		if (str[f[0][i] + 1] == str[i])
			f[0][i]++;
	}

	for (int j = 1; j <= 2; j++) {
		for (int i = 0; i < n; i++) {
			if(str[i+1] == 'a'+j-1) {
				if (i == n-1)
					f[j][i] = f[0][n];
				else 
					f[j][i] = i+1;
			} else {
				f[j][i] = f[0][i];
				while(f[j][i] && str[f[j][i] + 1] != ('a' + j - 1))
					f[j][i] = f[0][f[j][i]];
				if(str[f[j][i] + 1] == ('a' + j - 1))
					f[j][i]++;
			}
			c[j][i] = (i==n-1)&&(str[i+1] == 'a'+j-1);
		}
	}

	for (int j = 3; j <= k; j++) {
		for (int i = 0; i < n; i++) {
			f[j][i] = f[j-1][f[j-2][i]];
			c[j][i] = (c[j-2][i] + c[j-1][f[j-2][i]])%MOD;
		}
	}
	printf("%lld\n", c[k][0]);
}
