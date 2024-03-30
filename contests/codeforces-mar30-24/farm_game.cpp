#include <iostream>
using namespace std;

#define M 998244353

long long fact(long long i){
	long long ret=1;
	for(long long j=2;j<=i;++j)
		ret=(ret*j)%M;
	return ret;
}

long long inv(long long i){
	int pow=M-2,p=1;
	long long ret=1;
	while(p<pow){
		if(pow&p)ret=ret*i%M;
		i=i*i%M;p<<=1;
	}
	return ret;
}

long long nck(long long n,long long k){
	long long num=fact(n),den=fact(k);
	den=(den*fact(n-k))%M;
	return (num*inv(den))%M;
}

void test_case(){
	long long l,n;cin>>l>>n;
	long long ret=2-(l&1);
	ret=(ret*nck(n+1+((l-n-n-n)>>1),n+1))%M;
//	cout<<"total:"<<ret<<'\n';
//	cout<<ret<<':'<<n+1+((l-n-n-n)>>1)<<','<<n+1<<'\n';
	ret=(ret+ret)%M;
	cout<<ret<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
