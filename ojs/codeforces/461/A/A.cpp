#include <bits/stdc++.h>

using namespace std;

const int N = 1000007;
typedef unsigned long long int num;

int n;
num a[N];
num res;

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%I64u", a+i);
	
	sort(a, a+n);

	for (int i = 0; i < n; i++) {
		res += ((num)i+2llu)*a[i];
	}


	printf("%I64u\n", res - a[n-1]);
}
