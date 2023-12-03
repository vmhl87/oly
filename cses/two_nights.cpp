#include <iostream>
using namespace std;

long long mx(long long b){
	if(b>0)return b;
	return 0;
}

long long count(long long n){
	if(n==1)return 0;
	if(n==2)return 6;
	if(n==3)return 28;
	long long ret=(n*n*(n*n-1))/2;
	//corner1
	ret-=2*2;
	//corner2
	ret-=2*4;
	//corner3
	ret-=4*3;
	//edge1
	ret-=4*mx(n-4)*2;
	//edge2
	ret-=4*mx(n-4)*3;
	//center
	ret-=mx(n-4)*mx(n-4)*4;
	return ret;
}

int main(){
	int n;cin>>n;
	for(long long i=0;i<n;i++)cout<<count(i+1)<<'\n';
}
