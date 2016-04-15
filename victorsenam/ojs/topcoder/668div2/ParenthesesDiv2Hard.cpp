// BEGIN CUT HERE
// PROBLEM STATEMENT
// Correct parentheses sequences can be defined recursively as follows:

The empty string "" is a correct sequence.
If "X" and "Y" are correct sequences, then "XY" (the concatenation of X and Y) is a correct sequence.
If "X" is a correct sequence, then "(X)" is a correct sequence.
Each correct parentheses sequence can be derived using the above rules.

Examples of correct parentheses sequences include "", "()", "()()()", "(()())", and "(((())))".


You are given a string s.
You are also given vector <int>s L and R, each with the same number of elements.
These encode a set of conditions.
For each valid i, you have to satisfy the following condition:
the substring of s that begins at the 0-based index L[i] and ends at the 0-based index R[i] must be a correct parentheses sequence.
Note that the constraints guarantee that all the given ranges of indices are pairwise disjoint.


You can only modify s in one way: in each step you can choose two characters of s and swap them.
Return the minimal number of swaps needed to produce a string that satisfies all the given conditions.
If it is impossible, return -1 instead.

DEFINITION
Class:ParenthesesDiv2Hard
Method:minSwaps
Parameters:string, vector <int>, vector <int>
Returns:int
Method signature:int minSwaps(string s, vector <int> L, vector <int> R)


CONSTRAINTS
-s will contain between 1 and 50 characters, inclusive.
-Each character in s will be '(' or ')'.
-L will contain between 1 and 50 elements, inclusive.
-L and R will contain the same number of elements.
-For each valid i, 0 <= L[i] <= R[i] < |s|.
-For different i and j, intervals [(L[i]), (R[i])] and [(L[j]), (R[j])] will not intersect.


EXAMPLES

0)
")("
{0}
{1}

Returns: 1

We have one condition:
The substring that begins at index 0 and ends at index 1 must be a correct parentheses sequence.
In this case, this means that the entire string s must be a correct parentheses sequence.

We can achieve that by swapping s[0] with s[1].
This swap produces the string "()".

1)
"(())"
{0,2}
{1,3}

Returns: 1

The only way to satisfy both conditions is to change s into "()()".
This can be done in 1 swap: by swapping s[1] with s[2].

2)
"(((())"
{0,2}
{1,3}

Returns: 2

This time we do swap(s[1],s[4]) and swap(s[3],s[5]).

3)
"((((((((("
{0,2}
{1,3}

Returns: -1



4)
"))()())((()()()()()())))(((((("
{1,6,13,17,23,25}
{4,7,16,20,24,28}

Returns: 5



5)
"("
{0}
{0}

Returns: -1



// END CUT HERE
#line 106 "ParenthesesDiv2Hard.cpp"
#include <bits/stdc++.h>
class ParenthesesDiv2Hard {
	public:
	int minSwaps(string s, vector <int> L, vector <int> R) {
		
	}
};
