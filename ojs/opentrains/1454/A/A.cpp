#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

int curM = 1, cc = 0;
int cur = 0;
const int N = 112345;

char ans[10];
bool eq(char a, int ia, char b, int ib) {
	if(cc == 5) {
		printf("$ %d\n", cur); fflush(stdout);
		cc = 0, curM++;
	}
	printf("%c %d %c %d\n", a, ia, b, ib); fflush(stdout);
	scanf(" %s", ans);
	cc++;
	return ans[0] == 'Y';
}

bool eq_SS(int a, int b) { return eq('s', a, 's', b); }

bool eq_ST(int a, int b) {
	while(curM < b) {
		printf("$ %d\n", cur); fflush(stdout);
		curM++, cc = 0;
	}
	return eq('s', a, 't', b);
}

void finish(int m) {
	while(curM <= m) {
		curM++, cc = 0;
		printf("$ %d\n", cur); fflush(stdout);
	}
}

int F[N];

int main() {
	int n, m, i;
	scanf("%d %d", &n, &m);
	F[1] = 0;
	for(i = 2; i <= n; i++) {
		F[i] = F[i - 1];
		while(F[i] && !eq_SS(F[i] + 1, i))
			F[i] = F[F[i]];
		if(eq_SS(F[i] + 1, i))
			F[i]++;
	}
	int mx = 0;
	for(i = 1; i <= m; i++) {
		while(mx && !eq_ST(mx + 1, i))
			mx = F[mx];
		if(eq_ST(mx + 1, i))
			mx++;
		if(mx == n) {
			mx = F[mx];
			cur++;
		}
	}
	finish(m);
}
