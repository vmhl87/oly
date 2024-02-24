#include <algorithm>
#include <iostream>
using namespace std;

void test_case(){
	int n;cin>>n;
	int s[n];for(int i=0;i<n;++i)cin>>s[i];
	int p[n+1];p[0]=0;
	for(int i=0;i<n;++i)p[i+1]=p[i]+s[i];
//for(int i:p)cout<<i<<' ';cout<<'\n';
	for(int i=0;i<n;++i){
		if(i)cout<<' ';
		auto l=lower_bound(p,p+n+1,p[i+1]-s[i]*2-1),
			u=upper_bound(p,p+n+1,p[i+1]+s[i]);
		int lb=n+n,ub=n+n;
		if(l!=p)lb=p+i+1-l;
		if(u!=p+n+1)ub=u-p-i-1;
//cout<<*l<<' '<<p[i+1]<<' '<<*u<<'\n';
		cout<<min(lb,ub);
	}
	cout<<'\n';
}

int main(){
	int t;cin>>t;
	while(t-->0)test_case();
}
