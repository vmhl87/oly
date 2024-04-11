#include <iostream>
using namespace std;

int main(){
	// does not work - need exact division?
	long long n;cin>>n;
	long long sum=0;
	long long a[n];
	for(long long i=0;i<n;++i){
		cin>>a[i];
		sum+=a[i];
	}
	long long opt=((sum<<1)+n)/(n<<1);
	long long ret=0;
	for(long long i:a){
		if(i>opt)ret+=i-opt;
		else ret+=opt-i;
	}
	cout<<opt<<'\n';
	cout<<ret<<'\n';
}
