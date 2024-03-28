// Removal Game  -  https://cses.fi/problemset/result/8855194/
//
// Literally just a dp bash on all possible subgames on ranges

#include <iostream>
#include <vector>
using namespace std;

vector<long long> ns;

// dp arrays :| so messy
vector<vector<pair<long long,long long>>> dp;
vector<vector<bool>> fin;

// find the optimal score for the first player in the subgame
// ranging from l to r (returns score of first and second players)
pair<long long,long long> best(int l,int r){
	// dp accelerate
	if(fin[l][r])return dp[l][r];
	pair<long long,long long> ret;
	// base case
	if(l==r)ret.first=ns[l];
	else{
		// bruteforce step - find the best possible score for
		// second player if at this move we remove left or right
		// (rl = remove left, rr = remove right)
		pair<long long,long long> rl=best(l+1,r),rr=best(l,r-1);
		// find the one that optimizes our score (and minimizes
		// player 2 score)
		if(rr.second+ns[r]>rl.second+ns[l]){
			ret.first=rr.second+ns[r];
			ret.second=rr.first;
		}else{
			ret.first=rl.second+ns[l];
			ret.second=rl.first;
		}
	}
	// dp accelerate
	dp[l][r]=ret;
	fin[l][r]=1;
	return ret;
}

int main(){
	int n;cin>>n;
	ns.resize(n);
	// so messy :|
	dp.resize(n,vector<pair<long long,long long>>(n));
	fin.resize(n,vector<bool>(n));
	for(int i=0;i<n;++i)cin>>ns[i];
	cout<<best(0,n-1).first<<'\n';
}
