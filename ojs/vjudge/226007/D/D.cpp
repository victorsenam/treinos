#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int K = 16;
const int N = 8;
char str[K][10];
int ts, k;
int id[K];

bool go (int s, int n) {
	for (int i = 0; i < k; i++) id[i] = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++)
			id[j] += (str[j][id[j]] == ((s&(1<<i))?'B':'G'));
	}
	
	for (int j = 0; j < k; j++)
		if (str[j][id[j]]) return false;
	return true;
}

void printa (int s, int n) {
	for (int i = 0; i < n; i++) putchar((s&(1<<i))?'B':'G');
	putchar('\n');
}

int main () {
	scanf("%d", &ts);
	while (ts--) {
		scanf("%d", &k);
		for (int i = 0; i < k; i++)
			scanf(" %s", str[i]);

		bool ok = 0;
		for (int i = 1; !ok && i <= 16; i++) {
			for (int s = 0; !ok && s < (1<<i); s++)
				if (go(s,i)) { printa(s,i); ok = 1; }
		}
	}
}
