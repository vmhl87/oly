#include <algorithm>
#include <iostream>
using namespace std;

void test_case(){
	int n;cin>>n;
	int s[n];for(int i=0;i<n;++i)cin>>s[i];
	int p[n+3];p[0]=-s[0];p[1]=0;
	for(int i=0;i<n;++i)p[i+2]=p[i+1]+s[i];
	p[n+2]=p[n+1]+s[n-1];
	
	int lm[n],um[n];
	int last=s[0],ln=0;lm[0]=0;
	for(int i=1;i<n;++i){
		if(last==s[i]||(ln&&last<s[i]))ln++;
		else ln=0;
		lm[i]=ln;
		if(last!=s[i])ln=0;
		last=s[i];
	}
	last=s[n-1];ln=0;um[n-1]=0;
	for(int i=n-2;i>=0;--i){
		if(last==s[i]||(ln&&last<s[i]))ln++;
		else ln=0;
		um[i]=ln;
		if(last!=s[i])ln=0;
		last=s[i];
	}
	
//	for(int i:lm)cout<<i<<' ';cout<<'\n';
//	for(int i:um)cout<<i<<' ';cout<<'\n';
	
	for(int i=0;i<n;++i){
		if(i)cout<<' ';
		auto l=lower_bound(p,p+n+3,p[i+1]-s[i])-1,
			u=upper_bound(p,p+n+3,p[i+2]+s[i]);
		
		if(l>=p+i+1-lm[i])l=p+i-lm[i];
		if(u<=p+i+2+um[i])u=p+i+3+um[i];
		
		int lb=n+n,ub=n+n;
		if(l>p&&i)lb=p+i+1-l;
		if(u<p+n+2&&i<n-1)ub=u-p-i-2;
		
//cout<<':'<<i<<' '<<s[i]<<'\n';
//cout<<"  searching for "<<p[i+1]-s[i]-1<<','<<p[i+2]+s[i]<<'\n';
//cout<<"  found at "<<*l<<','<<*u<<'\n';
//cout<<" :"<<l-p<<' '<<u-p<<'\n';
//cout<<"  "<<i+1<<' '<<i+2<<'\n';
		
//		if(lb<=lm[i])lb=lm[i]+1;
//		if(ub<=um[i])ub=um[i]+1;

//cout<<" result: ";
		
		int best=min(lb,ub);
		if(best==n+n)cout<<-1;
		else cout<<best;

//cout<<'\n';

	}
	cout<<'\n';
}

int main(){
	int t;cin>>t;
	while(t-->0)test_case();
}
