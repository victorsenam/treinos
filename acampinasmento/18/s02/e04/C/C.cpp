#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll pr, p, a;

int main () {
	scanf("%lld %lld", &pr, &a);
	p = pr/2;
	ll mn = p-1;
	ll mx = (p/2)*(p - p/2);
	if (a < mn || a > mx || pr%2) {
		printf("NIE\n"); return 0;
	}

	if (a == 1) {
		printf("LLLL\n");
		return 0;
	}

	ll n = p/2, m = (p+1)/2;
	a = mx - a;

	ll full = a/(m-1);
	ll rem = a%(m-1);

	//cout << full << " " << rem << endl;

	int x = 0, y = 0;
	putchar('B'); x++;
	if (full) { putchar('L'); y++; }
	while (y < full) { putchar('B'); y++; }
	if (full) { putchar('P'); x++; }
	while (x < m-rem) { putchar('B'); x++; }
	if (rem) { putchar('L'); y++; putchar('P'); x++; }
	while (x < m ) { putchar('B'); x++; }
	putchar('L'); y++;
	while (y < n ) { putchar('B'); y++; }
	putchar('L'); x--;
	while (x > 0) { putchar('B'); x--; }
	putchar('L'); y--;
	while (y > 0) { putchar('B'); y--; }
	putchar('\n');

	/*
	putchar('B');
	if (full) putchar('L');
	for (int i = 1; i < full; i++) putchar('B');
	if (full) putchar('P');
	if (rem) {
		full++;
		int i = 1;
		for (i = 1; i + rem < n; i++) putchar('B');
		putchar('L');
		putchar('P');
		for (i++; i < n; i++) putchar('B');
	} else {
		for (int i = 2; i < m; i++) putchar('B');
	}
	putchar('L');
	for (int i = full+1; i < n; i++) putchar('B');
	putchar('L');
	for (int i = 1; i < m; i++) putchar('B');
	putchar('L');
	for (int i = 1; i < n; i++) putchar('B');
	putchar('\n');
	*/
}
