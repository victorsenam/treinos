#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 2e5;
int n, s, ans, v[N];

int main () {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf(" %d%d", &n, &s);
	for(int i=0;i<n;i++) v[i] = 2e7;
	for(int i=0;i<n;i++) {
		int _s, _c; scanf(" %d%d", &_s, &_c);
		--_s;
		v[_s] = min(v[_s], _c);
	}
	sort(v,v+n);
	for(int i=0;i<n;i++)
		if(s < v[i]) break;
		else {
			s -= v[i];
			ans++;
		}
	printf("%d\n", ans);
}
