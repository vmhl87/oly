#include <iostream>
using namespace std;

#define M 1000000007

long long inv(long long a,long long p){
	long long p2=1,iter=0,pn=p-2;
	long long pa=a,ret=1;
	while(p2<=pn){
		if(pn&(1<<iter))ret=(ret*pa)%p;
		pa=(pa*pa)%p;
		p2*=2;
		iter++;
	}
	return ret;
}

long long nck(int n,int k){
	long long num=1,den=1;
	for(long long i=0;i<k;i++){
		den=(den*(i+1))%M;
		num=(num*(n-i))%M;
	}
	den=inv(den,M);
	return (num*den)%M;
}

long long choose(int n,int k){
	return nck(n,min(k,n-k));
}

int main(){
	int a,b;cin>>a>>b;
	cout<<choose(a+b-1,b)<<'\n';
}
