#include <algorithm>
#include <iostream>
using namespace std;

int main(){
	int n;cin>>n;
	long long cows[n];
	for(int i=0;i<n;++i)
		cin>>cows[i];
	long long old[n];
	for(int i=0;i<n;++i)
		old[i]=cows[i];
	sort(cows,cows+n);
	long long psum[n+1];psum[0]=0;
	for(int i=0;i<n;++i)
		psum[i+1]=psum[i]+cows[i];
	long long total=0;
	for(int i=0;i<n;++i)
		total+=(long long)(i+1)*cows[i];
	int q;cin>>q;
	while(q--){
		long long a,b;cin>>a>>b;
		a=old[a-1];
		if(b>a){
			long long ub=lower_bound(cows,cows+n,b)-cows,
				lb=upper_bound(cows,cows+n,a+1)-cows;
			long long ret=total+ub*b-lb*a;
			ret-=psum[ub];
			ret+=psum[lb];
			cout<<ret<<'\n';
		}else{
			long long ub=lower_bound(cows,cows+n,a)-cows,
				lb=lower_bound(cows,cows+n,b+1)-cows;
			long long ret=total+(lb+1)*b-(ub+1)*a;
			ret+=psum[ub];
			ret-=psum[lb];
			cout<<ret<<'\n';
		}
	}
}
