#include <bits/stdc++.h>
#define y2 saduicvasiduhf
using namespace std;
const double eps = 1e-5;
const int K = 12;
int p1[K], p2[K], q1[K], q2[K];
int w, d, a, k;
double _y1, _y2;

void calc(double x){
    double num = p1[0], den = q1[0];    
    double num2 = p2[0], den2 = q2[0];    
    double q = x;
    for (int i = 1; i < k + 1; i++) {
        num += p1[i]*q;
        den += q1[i]*q;
        num2 += p2[i]*q;
        den2 += q2[i]*q;
        q *= x;
    }
    _y1 = num/den;
    _y2 = num2/den2;
}

double area (double mid){
    double ans = 0;
    mid = -mid;
    for(double i = 0; i <= w; i += eps) {
        calc(i);
        if(_y1 >= mid) {
            if(_y2 >= mid)
                ans += (_y1 - _y2)*eps;
            else
                ans += (_y1 - mid)*eps;
        }
    }
    return ans;
}


int main(){
    while(scanf("%d %d %d %d", &w, &d, &a, &k) != EOF) {    
        for(int i = 0; i < k+1; i++) scanf("%d",p1+i);
        for(int i = 0; i < k+1; i++) scanf("%d",q1+i);
        for(int i = 0; i < k+1; i++) scanf("%d",p2+i);
        for(int i = 0; i < k+1; i++) scanf("%d",q2+i);

        double lo = eps, hi = d;
        while(fabs(hi-lo) > eps){
            double mid = (hi+lo)/2.;    
            if(area(mid) >= a) hi = mid;
            else lo = mid+eps;
        }
        printf("%.5lf\n",lo);
    }
}
