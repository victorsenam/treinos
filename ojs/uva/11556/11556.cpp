#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

num n, m;
int b;

int main () { 
	while (scanf("%lld %d", &n, &b) != EOF) {
		if (n > (1ll<<(b+1))-1)
			printf("no\n");
		else
			printf("yes\n");
	}
}
