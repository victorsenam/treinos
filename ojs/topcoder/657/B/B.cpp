#include<string>
#include<cstdio>
#include<vector>
#include<iostream>

using namespace std;

class ProblemSetsEasy {
    public:
    int static maxSets(int E, int EM, int M, int MH, int H) {
        int r = 0;
        r += E*(EM+M)*(MH+H);
        r += E*MH*(MH-1);
        r += E*MH*H;
        r += EM*(EM-1)*(MH+H);
        r += EM*M*(MH+H);
        r += EM*MH*(MH-1);
        r += EM*MH*H;
        return r;
    }
};

int main () {
    int a, b, c, d, e;

    while (scanf("%d %d %d %d %d", &a, &b, &c, &d, &e) != EOF) {
        printf("%d\n", ProblemSetsEasy::maxSets(a, b, c, d, e));
    }
}
