#include <bits/stdc++.h>

using namespace std;
typedef unsigned int ui;
typedef int64_t ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 32;
typedef bitset<N> bi;

bool str[N];
int n;
ui v;

bool get (ui v, int k) {
	return ((1u<<k)&v);
}

ui asum (ui v, int k) {
	return (v + (v << k));
}

ui usum (ui v, int k) {
	ll x = v;
	bool carr = 0;
	for (int i = k; i < N; i++) {
		bool curr = (get(v,i-k)^carr);
		if (get(v,i-k)^carr)
			v ^= (1u<<i);
		int nw = (get(v,i-k) + carr + get(v, i));
		carr = (nw&2);
	}

	if (asum(v, k) != x)
		printf("err sum %s %d -> %s\n", bi(x).to_string().c_str(), k, bi(v).to_string().c_str());
	return v;
}

ui axor (ui v, int k) {
	return (v ^ (v >> k));
}

ui uxor (ui v, int k) {
	ll x = v;
	for (int i = N-k-1; i >= 0; i--)
		if (get(v,i+k))
			v ^= (1u<<i);
	if (axor(v, k) != x)
		printf("err xor %u %d\n", x, k);
	return v;
}

ui hasha (ui a) {
	a = a + (a << 10);
	a = a ^ (a >> 6);
	a = a + (a << 3);
	a = a ^ (a >> 11);
	a = a + (a << 16);
	return a;
}

int main () {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);

	while (n--) {
		scanf("%u", &v);

		v = usum(v, 16);
		v = uxor(v, 11);
		v = usum(v, 3);
		v = uxor(v, 6);
		v = usum(v, 10);

		printf("%u\n", v);
	}
}
