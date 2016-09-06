#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 19;
const int M = (1<<N);

char str[30];
int p[M], ip[M];
map<string, int> mp;
int n, m, q;

void swapit (int l, int r) {
	int mid = (l+r)/2;

	for (int i = 0; i < mid-l; i++)
		swap(p[i+l], p[i+mid]);
}

bool beats (int a, int b, int l, int r) {
	if (l == a) {
		return (l <= b && b < r);
	} else {
		int mid = (l+r)/2;
		if (a < mid)
			return beats(a, b, l, mid);
		else
			return beats(a, b, mid, r);
	}
}

int main () {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	m = (1<<n);

	for (int i = 0; i < m; i++) {
		scanf(" %s", str);
		mp[str] = i;
		p[i] = i;
	}

	for (int k = 1; k <= n; k++) {
		for (int i = 0; i < m; i += (1<<k)) {
			char c;
			scanf(" %c", &c);
			if (c == 'L')
				swapit(i, i+(1<<k));
		}
	}

	for (int i = 0; i < m; i++) {
		ip[p[i]] = i;
	}

	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		int a, b;
		scanf(" %s", str);
		a = ip[mp[str]];
		scanf(" %s", str);
		b = ip[mp[str]];

		if (beats(a, b, 0, m))
			printf("Win\n");
		else if (beats(b, a, 0, m))
			printf("Lose\n");
		else
			printf("Unknown\n");
	}
}
