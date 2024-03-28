// Array Description  -  https://cses.fi/problemset/result/8855465/
//
// We can't use global DP for this problem, as there is too large
// of a search space. Rather we use a local DP-like approach
// for each block of numbers separated by zeroes.
// It is a very simplistic way-counting "sliding window" type thing.

#include <iostream>
using namespace std;

#define M 1000000007

int m;

// compute the # of ways to traverse from position l to r over
// a distance d, mod M
long long ways(int l,int r,int d){
	// normalize to array indices - this will shift 0 (any)
	// to the -1 position
	l--;r--;
	// sliding window arrays
	long long cur[m],next[m];
	// fill up arrays
	for(int i=0;i<m;++i)
		cur[i]=(i==l||l<0);
	// repeat for d iterations - if d = 0 then do nothing
	while(d--){
		// generate next mapping by (i-1 i i+1) -> i
		for(int i=0;i<m;++i){
			next[i]=cur[i];
			if(i)next[i]+=cur[i-1];
			if(i<m-1)next[i]+=cur[i+1];
			next[i]%=M;
		}
		// swap arrays - this could theoretically be done
		// with a virtual swap, but lazy
		for(int i=0;i<m;++i)
			cur[i]=next[i];
	}
	// if ending is 'any', sum up all, otherwise return at r
	if(r<0){
		long long ret=0;
		for(int i=0;i<m;++i)ret+=cur[i];
		ret%=M;
		return ret;
	}
	return cur[r];
}

int main(){
	int n;cin>>n>>m;
	long long ret=1;
	// because there might be zeroes at the start, we
	// set last to the 'any' indicator
	int last=0,dist=0;
	for(int i=0;i<n;++i){
		int x;cin>>x;
		// if we inputted a positive number then compute
		// otherwise advance distance
		if(x){
			// offsets are weird when mixing any and normal
			if(last)dist++;
			ret=(ret*ways(last,x,dist))%M;
			last=x;dist=0;
		}else dist++;
	}
	// if ending zeroes compute
	if(dist){
		if(!last)dist--;
		ret=(ret*ways(last,0,dist))%M;
	}
	cout<<ret<<'\n';
}
