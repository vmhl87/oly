#include <iostream>
#include <algorithm>
using namespace std;

bool abscomp(long long a,long long b){
	return (a>0?a:-a)<(b>0?b:-b);
}

int main(){
	int n;cin>>n;
	int ns[n];for(int i=0;i<n;i++)cin>>ns[i];
	sort(ns,ns+n);
	int depth=14;if(depth>n)depth=n;
	int p2=(1<<depth);
	long long sums[p2];for(int i=0;i<p2;i++)sums[i]=0;
	for(int i=n-1;i>n-1-depth;i--)for(int j=0;j<p2;j++){
		if(j&(1<<(n-1-i)))sums[j]+=ns[i];
		else sums[j]-=ns[i];
	}
	for(int i=n-1-depth;i>=0;i--){
		long long next[p2*2];
		for(int j=0;j<p2;j++){
			next[j]=sums[j]+ns[i];
			next[j+p2]=sums[j]-ns[i];
		}
		sort(next,next+p2*2,abscomp);
		for(int j=0;j<p2;j++)sums[j]=next[j];
	}
	sort(sums,sums+p2,abscomp);
	cout<<(sums[0]>0?sums[0]:-sums[0])<<'\n';
}
