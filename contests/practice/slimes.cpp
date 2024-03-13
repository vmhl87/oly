/*  Slimes  -  Codeforces round 162 problem D

	We can notice that a collection of slimes
	will, if they are not all of equal size,
	be able to form into a single slime after n steps.
	
	Essentially, to solve this question, we need to create
	a partial sum array which we can binary search to find
	the smallest collection of slimes on the left or right
	which sum up to more than the current slime's size.
	We do need to then account for groupings of slimes that
	are entirely the same size, though that is mostly trivial.
*/

#include <algorithm>
#include <iostream>
using namespace std;

void test_case(){
	int n;cin>>n;
	long long s[n];for(int i=0;i<n;++i)cin>>s[i];
	// partial sums
	long long p[n+1];p[0]=0;
	for(int i=0;i<n;++i)p[i+1]=p[i]+s[i];
	// lm, um represent the minimum number of slimes
	// needed to the left or the right in order for the
	// collection to be of nonuniform size.
	int lm[n],um[n];
	int last=s[0],len=0;lm[0]=0;um[n-1]=0;
	for(int i=1;i<n;++i){
		if(last==s[i])len++;
		else len=0;
		lm[i]=len;
		last=s[i];
	}
	last=s[n-1];len=0;
	for(int i=n-2;i>=0;--i){
		if(last==s[i])len++;
		else len=0;
		um[i]=len;
		last=s[i];
	}
	for(int i=0;i<n;++i){
		if(i)cout<<' ';
		// binary search to find minimum collections
		long long *l=lower_bound(p,p+n+1,p[i]-s[i])-1,
			*u=upper_bound(p,p+n+1,p[i+1]+s[i]);
		// prepare bounds with lm[], um[]
		long long *ln=p+i,
			*un=p+i+1;
		if(lm[i])ln-=lm[i]+1;
		else if(i>0&&lm[i-1]&&s[i]>s[i-1])ln-=lm[i-1]+2;
		if(um[i])un+=um[i]+1;
		else if(i<n-1&&um[i+1]&&s[i]>s[i+1])un+=um[i+1]+2;
		// enforce bounds
		if(l>ln)l=ln;
		if(u<un)u=un;
		// use iterators to find bound lengths
		int lb=n+n,ub=n+n;
		if(l>=p)lb=p+i-l;
		if(u<=p+n)ub=u-p-i-1;
		int best=min(lb,ub);
		if(best==n+n)cout<<-1;
		else cout<<best;
	}
	cout<<'\n';
}

int main(){
	int t;cin>>t;
	while(t-->0)test_case();
}
