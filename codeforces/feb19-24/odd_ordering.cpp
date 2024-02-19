#include <iostream>
using namespace std;

void test_case(){
	long long n,k;cin>>n>>k;
	int mult=1;
	while(n){
		if(k>(n+1)>>1)k-=(n+1)>>1;
		else{
			cout<<(k*2-1)*mult<<'\n';
			return;
		}
		n=n>>1;mult=mult<<1;
	}
}

int main(){
	int t;cin>>t;
	while(t-->0)test_case();
}
