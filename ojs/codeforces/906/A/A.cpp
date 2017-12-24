#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;

int possible;
int n;
char str[N];
char r;

int main () {
	scanf("%d", &n);

	int qt = 0;
	possible = (1<<26) - 1;
	for (int i = 0; i < n; i++) {
		scanf(" %c %s", &r, str);

		int cont = 0;
		for (int j = 0; str[j]; j++)
			cont |= (1<<((str[j]-'a')));

		if (r == '!') {
			if (__builtin_popcount(possible) == 1)
				qt++;
			possible &= cont;
		} else if (r == '.') {
			cont = (1<<26) - 1 - cont;
			possible &= cont;
		} else if (r == '?') {
			if (__builtin_popcount(possible) == 1 && cont != possible)
				qt++;
			possible &= (1<<26) - 1 - cont;
		}
	}

	printf("%d\n", qt);
}
