#include <bits/stdtr1c++.h> 
  
using namespace std; 
  
typedef long double ld; 
typedef unsigned long long ll; 
typedef pair<ll, ll> pii; 
typedef complex<ld> pt; 
  
int period[70];  
ll c[65][65]; 
void init() { 
  //soln: have to determine number of #s with 
  //period p in range l<= x<= r. 
  //can find number of #s in period p within first r numbers. 
  //fortunately we can brute force when r <= 70. 
  //since the binary digital sum for any number < 10^18 
  //is less than 70, we can just count how many numbers less 
  //than r have k bits set. then check if period[k] = p-1. 
  //try this for all k, sum up the results. 
    
  //to get the ans for ranges restricted from l-r, we can just subtract f(r-1) from f(l). 
  period[0] = 0; period[1] = 0; 
  for (int i = 2; i < 70; i++) { 
    int v = __builtin_popcount(i); 
    period[i] = 1+period[v]; 
    printf("%d ", period[i]);
  } 
  for (int i = 0; i <= 64; i++) { 
    c[i][0] = 1; 
  } 
  for (int n = 1; n <= 64; n++) { 
    for (int k = 1; k <= n; k++) { 
      c[n][k] = c[n-1][k] + c[n-1][k-1]; 
    } 
  } 
} 
  
ll leading(ll n) { 
  ll t = 0; 
  while (n >>= 1) t++; 
  return t; 
} 
  
ll f(ll n, ll k) { 
  if (n < (ll(1)<<k)-1) return 0; 
  if (k==0) { 
    return 1; 
  } 
  ll t = leading(n); 
  ll bit = 1; bit <<= t; 
  return c[t][k]+f(n-bit,k-1); 
} 
  
ll solve(ll lim, ll p) { 
  if (p == 0) return (lim >= 1); 
  ll m = 64; 
  ll ans = 0; 
  for (int i = 1; i <= min(ll(63),lim-1); i++) { 
    if (period[i] == p-1) { 
      ll del = f(lim,i); 
      if (del > 0 && p == 1) del--; 
      ans += del; 
    } 
  } 
  return ans; 
} 
  
int main() { 
  ll l, r, p; 
  init(); 
  while (cin >> l >> r >> p) { 
    if (!(l||r||p)) break; 
    cout << solve(r,p) - solve(l-1,p) << endl; 
  } 
    return 0; 
}
