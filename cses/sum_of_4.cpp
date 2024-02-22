/*  Sum of Four Values

	We bruteforce the first two values, and use a
	cool greedy algorithm to determine the last 2:
	
	Keep two pointers, one at the bottom of the search
	range and another at the top, and update them as
	accordingly:
		if the sum is too big, decrement top pointer
		if sum is too small, increment bottom pointer
		otherwise, we are finished
	
	If we bounds check so that none of these pointers
	ever overlap, this is actually fast enough to pass
*/

#include <algorithm>
#include <iostream>
using namespace std;

// datastructure to hold values,indexes and sort
typedef struct val{
	long long v;
	int i;
	bool operator<(const val o)const{
		return v<o.v;
	}
	bool operator==(const val o)const{
		return v==o.v;
	}
}val;

int main(){
	int n;long long x;
	cin>>n>>x;
	val ns[n];
	for(int i=0;i<n;i++){
		cin>>ns[i].v;
		ns[i].i=i+1;
	}
	sort(ns,ns+n);
	// bruteforce first 2 (i,j)
	for(int i=0;i<n-3,ns[i].v<=x/4;++i){
		long long s=x-ns[i].v;
		for(int j=i+1;j<n-2,ns[j].v<=s/3;++j){
			// ts = target sum
			long long ts=s-ns[j].v;
			// l,u = lower,upper
			int l=j+1,u=n-1;
			// iterate until works
			while(l<u&&ns[l].v+ns[u].v!=ts){
				if(ns[l].v+ns[u].v<ts)l++;
				else u--;
			}
			if(l<u){
				cout<<ns[i].i<<' '<<ns[j].i<<' '<<ns[l].i<<' '<<ns[u].i<<'\n';
				return 0;
			}
		}
	}
	cout<<"IMPOSSIBLE\n";
}
