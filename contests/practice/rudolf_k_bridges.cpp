#include <iostream>
#include <queue>
#include <set>
using namespace std;

void test_case(){
	int n,m,k,d;cin>>n>>m>>k>>d;
	// best cost of building a bridge over row i
	long long best[n];
	for(int x=0;x<n;++x){
		// heights
		long long h[m];for(int i=0;i<m;++i)cin>>h[i];
		// dp - compute the cheapest way to build a bridge
		// from 0 to i, construct recursively by picking the
		// smallest possible location for the previous support
		// and adding the current support
		// we use a multiset to autosort the previous (d+1)
		// supports - this is a trick I learned from editorial
		multiset<long long> dp;
		// ensure that dp always contains only the last (d+1)
		// computations
		queue<long long> past;
		long long last=-1;
		for(int i=0;i<m;++i){
			// find optimal previous support
			long long opt=0;
			// smallest elem out of multiset
			if(dp.size())opt=*dp.begin();
			opt+=h[i]+1;
			// update multiset
			dp.insert(opt);
			past.push(opt);
			// mantain size
			if(dp.size()>d+1){
				dp.erase(dp.find(past.front()));
				past.pop();
			}
			last=opt;
		}
		best[x]=last;
	}
	// sliding window type algorithm to compute optimal
	// selection of rows to build bridges over
	long long ret=0;bool ns=1;
	long long sum=0;
	for(int i=0;i<n;++i){
		// expand
		sum+=best[i];
		// contract if necessary
		if(i-k>=0)sum-=best[i-k];
		// count when length of window is right
		if(i>=k-1){
			ret=(ns||sum<ret?sum:ret);
			ns=0;
		}
	}
	cout<<ret<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
