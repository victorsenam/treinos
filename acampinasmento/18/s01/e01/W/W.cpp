#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

#define y2 lakjsdalsdj

int main () {
	int n, i;
	scanf("%d", &n);
	int X1 = -10000, Y1 = -10000, X2 = 10000, Y2 = 10000;
	for(i = 0; i < n; i++) {
		int x1, x2, y1, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		X1 = max(X1, x1);
		X2 = min(X2, x2);
		Y1 = max(Y1, y1);
		Y2 = min(Y2, y2);
	}
	if(X1 >= X2 || Y1 >= Y2)
		puts("0");
	else printf("%d\n", (X2 - X1) * (Y2 - Y1));
}
