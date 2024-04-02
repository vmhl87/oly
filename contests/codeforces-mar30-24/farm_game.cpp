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
	// ret = all ways
	long long ret=nck(l,n<<1);
	// lose = ways where distances are even
	// need to count for all amounts of odd seg
	// between b_i, a_i+1
	long long lose=0;
	// i odd seg
	for(long long i=0;i<n;++i){
		// check if reachable
		if(i+(n<<1)>l)break;
		long long seg=1+((l^i)&1);
		// n-1 locations, i sel
		seg=(seg*nck(n-1,i))%M;
		// (l-n-n-i)/2 blocks, n+n bars
		seg=(seg*nck((n<<1)+((l-i-(n<<1))>>1),n<<1))%M;
		lose+=seg;if(lose>=M)lose-=M;
	}
	// subtract
	ret-=lose;if(ret<0)ret+=M;
	// double
	ret<<=1;if(ret>=M)ret-=M;
	cout<<ret<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
