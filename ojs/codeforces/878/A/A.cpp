#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

int n;

char t[N];
int v[N];

int run (int x) {
	for (int i = 0; i < n; i++)
		if (t[i] == '|')
			x |= v[i];
		else if (t[i] == '&')
			x &= v[i];
		else
			x ^= v[i];
	return x;
}

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf(" %c %d", t+i, v+i);

	int c_or = 0;
	int c_and = 0;
	int c_xor = 0;

	int z = run(0);
	int o = run((1<<10) - 1);
	for (int i = 0; i < 10; i++) {

		int one = (o&(1<<i));
		int zer = (z&(1<<i));

		if (one && zer)
			c_or |= (1<<i);
		else if (one)
			c_and |= (1<<i);
		else if (zer)
			c_xor |= (1<<i);
	}

	printf("3\n");
	printf("| %d\n^ %d\n& %d\n", c_or, c_xor, c_and + c_or + c_xor);
}
