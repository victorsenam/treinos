#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

int f[4];
char str[N];

int main () {
	scanf(" %s", str);
	for (int i = 0; str[i]; i++) {
		if (str[i] == 'P') f[0]++;
		else if (str[i] == 'K') f[1]++;
		else f[2]++;
	}
	sort(f, f+3);
	printf("%d\n", f[0] == f[2]);
}
