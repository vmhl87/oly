#include <iostream>
#include <multiset>
using namespace std;

multiset<long long> factors(long long n){
	for(int i=2;i

long long gcd(long long a,long long b){
	if(b==0)return a;
	if(a<b)return gcd(b,a);
	return gcd(b,a%b);
}

typedef struct fract{
	long long num=1,den=1;
	void norm(){
		long long s=gcd(num,den);
		if(s>1){
			num/=s;
			den/=s;
		}
	}
}fract;

void test_case(){
	int c;cin>>c;
	fract co[c+1];
	for(int i=0;i<c+1;++i)
		cin>>co[i].num;

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
