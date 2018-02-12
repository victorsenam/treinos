#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n - 1; i++) putchar('9');
	putchar('8');
	for(i = 0; i < n; i++) putchar('9');
	putchar('\n');
	for(i = 0; i < n; i++) putchar('9');
	for(i = 0; i < n - 1; i++) putchar('9');
	putchar('8');
	putchar('\n');
}
