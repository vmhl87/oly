#include <iostream>
#include <cmath>
using namespace std;

int main(){
	int t;cin>>t;
	while(t--){
		double a,o;char c;
		cin>>a>>o>>c;
		if(c=='+'){
			// output is o*a/100
			long double ret=o*a/100.;
			cout<<(long long)ret;
			ret-=(long long)ret;
			ret*=100000;
			long long r=round(ret);
			if(r)cout<<'.'<<r;
			cout<<'\n';
		}else{
			// output is a*100/o
			long double ret=(a*100.)/o;
			cout<<(long long)ret;
			ret-=(long long)ret;
			ret*=100000;
			long long r=round(ret);
			if(r)cout<<'.'<<r;
			cout<<'\n';
		}
	}
}
