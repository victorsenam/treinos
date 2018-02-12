#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int best;
const int N = 1000009;
char s[N]; int n;
int nx[26][N];

inline void go(int a, int b) {
	if(nx[a][0] == n || nx[b][0] == n) return;
	bool fst = true, has = false;
	int i = 0, sum = 0;
	while(true) {
		if(nx[a][i] < nx[b][i]) {
			sum++;
			if(has) { if(sum > best) best = sum; }
			i = nx[a][i] + 1;
		} else if(nx[b][i] < nx[a][i]) {
			sum--; has = true;
			if(sum > best) best = sum;
			if(sum < 0) {
				sum = 0;
				has = false;
			}
			i = nx[b][i] + 1;
		} else break;
	}
	if(!has && sum > best) best = sum - 1;
}

int main () {
	int i, j;
	char c = getchar();
	n = c - '0';
	while(isdigit(c = getchar()))
		n = (n << 3) + (n << 1) + (c - '0');
	while(isspace(c = getchar()));
	s[0] = c;
	for(i = 1; i < n; i++) s[i] = getchar();


	//printf("%d\n%s\n", n, s);
	for(j = 0; j < 26; j++) nx[j][n] = n;
	for(j = 0; j < 26; j++)
		for(i = n - 1; i >= 0; i--)
			if(s[i] == 'a' + j)
				nx[j][i] = i;
			else
				nx[j][i] = nx[j][i + 1];
	for(i = 0; i < 26; i++)
		for(j = 0; j < 26; j++)
			if(i != j)
				go(i, j);
	printf("%d\n", best);
}
