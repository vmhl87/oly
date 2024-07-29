#include <iostream>
using namespace std;

int main(){
	long long n,a,b;
	cin>>n>>a>>b;

	long long best=-1;

	long long t=0;
	do{
		if((t+n)%b==0){
			best=t+n;
			break;
		}
		t+=a;
	}while(t%b!=0);

	t=0;
	do{
		if((t+n)%a==0){
			if(t+n<best||best<0)
				best=t+n;
			break;
		}
		t+=b;
	}while(t%a!=0);

	cout<<best<<'\n';
}
