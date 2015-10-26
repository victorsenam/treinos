#include <bits/stdc++.h>
using namespace std;

typedef unsigned int num;

class Tdetectived2 { 
	public:
	int reveal(vector <string> s) {
        int n = s.size();
        num q[(1u<<18)];
        bool visi[(1u<<18)];
        memset(visi, 0, sizeof visi);
        int qf, qi;
        qi = qf = 0;
        q[qf++] = (1u); 
        int ans[20];
        for (int i = 0; i < n; i++)
            ans[i] = INT_MAX;
        ans[0] = 0;
        int cnt = 1;

        while (qi < qf && cnt < n) {
            num att = q[qi++];
            
            int p[18];
            for (int i = 0; i < n; i++)
                p[i] = 0;
            
            for (int i = 0; i < n; i++) {
                if (!(att&(1u<<i)))
                    continue;
                
                for (int j = 0; j < n; j++)
                    p[j] = max(p[j], ((1u<<j)&att)?0:(s[i][j]-'0'));
            }

            int maxi = 0;
            for (int i = 0; i < n; i++) {
                if (att&(1u<<i))
                    continue;
                maxi = max(maxi, p[i]);
            }

            for (int i = 0; i < n; i++) {
                if (p[i] != maxi || (att&(1u<<i)))
                    continue;
                if (ans[i] == INT_MAX)
                    cnt++;
                ans[i] = min(ans[i], __builtin_popcount(att));
                if (visi[(att|(1u<<i))])
                    continue;
                visi[(att|(1u<<i))] = 1;
                q[qf++] = (att|(1u<<i));
            }
        }
        long long int res = 0;
        for (int i = 0; i < n; i++) {
            res += i*ans[i];
        }
        return res;
	} 

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"000","000","000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, reveal(Arg0)); }
	void test_case_1() { string Arr0[] = {"0224","2011","2104","4140"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(1, Arg1, reveal(Arg0)); }
	void test_case_2() { string Arr0[] = {"0886","8086","8801","6610"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; verify_case(2, Arg1, reveal(Arg0)); }
	void test_case_3() { string Arr0[] = {"064675511","603525154","430262731","652030511","726302420","552020464","517544052","153126500","141104200"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 170; verify_case(3, Arg1, reveal(Arg0)); }
	void test_case_4() { string Arr0[] = {"0313131","3030020","1301132","3010031","1010003","3233003","1021330"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 37; verify_case(4, Arg1, reveal(Arg0)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main() {
Tdetectived2 ___test; 
___test.run_test(-1); 
} 
// END CUT HERE 
