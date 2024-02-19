#include <iostream>
using namespace std;

int scf(int n){
	return (n*(n+1))/2;
}

int sof(int n){
	return 45*(n/10)+scf((n%10)-1);
}

void test_case(){
	int n;cin>>n;n++;
	int rem=0,pow=1,ret=0;
	while(n){
		ret+=sof(n)*pow;
		ret+=rem*(n%10);
		rem+=(n%10)*pow;
		pow*=10;n/=10;
	}
	cout<<ret<<'\n';
}

int main(){
	int n;cin>>n;
	while(n-->0)test_case();
}
