#include <bits/stdc++.h>
using namespace std;
class SetPartialOrder { 
	public:
	string compareSets(vector <int> a, vector <int> b) {
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        if (a.size() == b.size()) {
            for (int i =0 ; i < a.size(); i++)
                if (a[i] != b[i])
                    return (string) "INCOMPARABLE";
            return (string) "EQUAL";
        } else {
            bool sw = (a.size() > b.size());
            if (sw)
                swap(a,b);
            int j = 0;
            for (int i = 0; i < a.size(); i++) {
                while (j < b.size() && a[j] < a[i])
                    j++;
                if (j == b.size() || a[j] != a[i])
                    return (string) "INCOMPARABLE";
                j++;
            }
            if (!sw) return (string) "LESS";
            else return (string) "GREATER";
        }
	} 

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 2, 3, 5, 8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {8, 5, 1, 3, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "EQUAL"; verify_case(0, Arg2, compareSets(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {2, 3, 5, 7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "LESS"; verify_case(1, Arg2, compareSets(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {2, 4, 6, 8, 10, 12, 14, 16}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 4, 8, 16}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "GREATER"; verify_case(2, Arg2, compareSets(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {42, 23, 17}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {15, 23, 31}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "INCOMPARABLE"; verify_case(3, Arg2, compareSets(Arg0, Arg1)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main() {
SetPartialOrder ___test; 
___test.run_test(-1); 
} 
// END CUT HERE 
