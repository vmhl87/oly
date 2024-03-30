// Minimizing Coins  -  https://cses.fi/problemset/result/8873761/
//
// Yet another shameless DP bash - compute for each sum s the
// minimum number of coins required recursively, adding one coin
// on at a time according to which is optimal

#include <iostream>
#include <vector>
using namespace std;

// i am really just too lazy
vector<int> coins;

// because we must handle the -1 (no valid construction) case
// and I am lazy I created a utility to merge the results of
// sub-sum computations and "best" - a is best and b is subsum
int comb(int a,int b){
	// if subsum is -1 then always return a
	if(b<0)return a;
	// otherwise if subum is better than current best return
	// subsum + 1 (adding one for the one coin we used)
	if(b<a||a<0)return b+1;
	// default
	return a;
}

int dp[1000001];
bool f[1000001];
// (min)imum (c)oins required to construct sum t
int minc(int t){
	// base case
	if(t==0)return 0;
	if(f[t])return dp[t];
	// assume no construction possible
	int best=-1;
	// for every valid coin to use:
	for(int i:coins)if(t-i>=0){
		// find how many coins the subsum would need
		// and combine
		int p=minc(t-i);
		best=comb(best,p);
	}
	f[t]=1;dp[t]=best;
	return best;
}

int main(){
	int n,x;cin>>n>>x;
	coins.resize(n);
	for(int i=0;i<n;++i)cin>>coins[i];
	cout<<minc(x)<<'\n';
}
