#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+8;

int x, y;
char str[N];

int main () {
	scanf(" %s", str);

	for (int i = 0; str[i]; i++) {
		if (str[i] == 'N')
			x++;
		else if (str[i] == 'S')
			x--;
		else if (str[i] == 'E')
			y++;
		else
			y--;
	}

	printf("%d\n", abs(x) + abs(y));
}
