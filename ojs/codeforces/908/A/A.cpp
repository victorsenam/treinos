#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 100;
int n;
char str[N];

int main () {
	scanf(" %s", str);

	for (int i = 0; str[i]; i++) {
		if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
			n++;
		else if (str[i] >= '0' && str[i] <= '9' && (str[i] - '0')%2 == 1)
			n++;
	}

	printf("%d\n", n);
}
