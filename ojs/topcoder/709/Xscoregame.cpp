#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int N = (1<<15);
const int M = 64;

vector<int> a;
int n;
ll memo[N][M];

ll pd (int msk, int y) {
    if (msk == (1<<n)-1)
        return 0;

    ll & me = memo[msk][y];
    
    if (me != -1)
        return me;

    for (int i = 0; i < n; i++) {
        if (msk&(1<<i)) continue;

        ll x = pd(msk|(1<<i), a[i]);
        ll vl = (x + (x^a[i]));
        
        if (me == -1 || vl + (vl^y) > me + (me^y))
            me = vl;
    }

    assert(me != -1);

    return me;
}

class Xscoregame
{ 
    public: 
        int getscore(vector <int> A) 
        { 
            memset(memo, -1, sizeof memo);
n = A.size();
            a = A;

            return int(pd(0,0));
        } 

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { int Arr0[] = {1,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; verify_case(0, Arg1, getscore(Arg0)); }
        void test_case_1() { int Arr0[] = {10,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 80; verify_case(1, Arg1, getscore(Arg0)); }
        void test_case_2() { int Arr0[] = {1,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, getscore(Arg0)); }
        void test_case_3() { int Arr0[] = {1,0,1,0,1,0,1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 170; verify_case(3, Arg1, getscore(Arg0)); }
        void test_case_4() { int Arr0[] = {50,0,1,0,1,0,1,0,1,0,1,0,1,0,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 830122; verify_case(4, Arg1, getscore(Arg0)); }

        // END CUT HERE

}; 

// BEGIN CUT HERE 
int main()
{
    Xscoregame ___test; 
    printf("%d\n", ___test.getscore({63,50}));
    ___test.run_test(-1); 
} 
// END CUT HERE 

