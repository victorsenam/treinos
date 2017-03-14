#include <bits/stdc++.h>
using namespace std;

bool A[323];

int angle (int h, int m) {
    int ang = abs(h-m) * 6;
    if (ang > 180) ang = 360-ang;
    return ang;
}

int main(){
    int n;
    int m = 0;
    for(int h = 0; h < 60; h++){
        for(int i = 0; i < 12; i++) {
            A[angle(h,m)] = true;    
            m++; m %= 60;
        }
    }

    while(scanf("%d",&n) != EOF){
        if(A[n]) puts("Y");
        else puts("N");
    }
}
