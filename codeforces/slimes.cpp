#include <algorithm>
#include <iostream>
using namespace std;

void test_case(){
	int n;cin>>n;
	int s[n];for(int i=0;i<n;++i)cin>>s[i];
	int p[n+2];p[0]=-s[0];p[1]=0;
	for(int i=0;i<n;++i)p[i+2]=p[i+1]+s[i];
	int lm[n],um[n];
	lm[0]=1;int last=s[0],bl=1;
	bool lag=0;
	for(int i=1;i<n;++i){
		if(s[i]==last||lag)bl++;
		else bl=1;
		lm[i]=bl;
		lag=0;if(s[i]==last)lag=1;
		last=s[i];
	}
	lag=0;bl=1;um[n-1]=1;
	last=s[n-1];
	for(int i=n-2;i>=0;--i){
		if(s[i]==last||lag)bl++;
		else bl=1;
		um[i]=bl;
		lag=0;if(s[i]==last)lag=1;
		last=s[i];
	}
for(int i:lm)cout<<i<<' ';cout<<'\n';
for(int i:um)cout<<i<<' ';cout<<'\n';
	for(int i=0;i<n;++i){
//		if(i)cout<<' ';
		auto l=lower_bound(p,p+n+2,p[i+1]-s[i]-1),
			u=upper_bound(p,p+n+2,p[i+2]+s[i]);
		int lb=n+n,ub=n+n;
		if(l!=p)lb=p+i+1-l;
		if(u!=p+n+1)ub=u-p-i-2;
		if(lb<lm[i]&&(lb>1&&s[i]!=s[i-1]))lb=lm[i];
		if(ub<um[i]&&(ub>1&&s[i]!=s[i+1]))ub=um[i];
		int best=min(lb,ub);
cout<<lb<<' '<<ub<<' '<<l-p<<' '<<u-p<<' '<<p[i+1]-s[i]-1<<' '<<p[i+2]+s[i]<<"\n :";
		if(best==n+n)cout<<-1;
		else cout<<best;
cout<<'\n';
	}
	cout<<'\n';
}

int main(){
	int t;cin>>t;
	while(t-->0)test_case();
}
