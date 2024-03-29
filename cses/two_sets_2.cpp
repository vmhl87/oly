// Two Sets II  -  https://cses.fi/problemset/result/8869761/
//
// There is probably a better way to go about doing this,
// but I did a pretty standard DP bruteforce. For a collection
// of n integers, the number of ways to partition it into two
// sets with difference 0 is equal to the number of ways to
// partition the first n-1 integers of the collection into
// two sets of difference equal to +- of the nth integer.

#include <iostream>
using namespace std;

#define M 1000000007

// probably makes minimal difference, but difference nonetheless
#pragma GCC optimize("O3")

// sizing on these dp arrays is extremely questionable
long long dp[501][1<<18];
bool fin[501][1<<18];
// # of ways to partition the first `len` integers into two
// sets of difference `shift`
long long ways(int shift,short len){
	// base case
	if(len==1)return (shift==1||shift==-1);
	// shift may be negative, but array indices must always
	// be positive, so we upshift by half the arr size
	int s2=shift|(1<<17);
	// dp accelerate
	if(fin[len][s2])return dp[len][s2];
	// # of ways to add the last element to essentially
	// either the left or right set
	long long ret=ways(shift+len,len-1);
	ret+=ways(shift-len,len-1);
	ret%=M;
	// dp accelerate
	fin[len][s2]=1;
	dp[len][s2]=ret;
	return ret;
}

int main(){
	int n;cin>>n;
	// computation doublecounts because it does not account
	// for swapping the sets on either side - we take a
	// modular division by two
	long long ret=ways(0,n);
	if(ret&1)ret+=M;
	ret>>=1;
	cout<<ret<<'\n';
}
