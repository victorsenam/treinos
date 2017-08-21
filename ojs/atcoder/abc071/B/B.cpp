#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;

int app[500];
char str[N];

int main () {
	scanf(" %s", str);

	for (int i = 0; str[i]; i++) {
		app[str[i]] = 1;
	}

	for (int a = 'a'; a <= 'z'; a++) {
		if (!app[a]) {
			printf("%c\n", a);
			return 0;
		}
	}
	printf("None\n");
}
