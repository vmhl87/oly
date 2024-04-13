#include <iostream>
using namespace std;

void test_case(){
	int n;cin>>n;
	long long sum=0;
	for(int i=1;i<n;++i)
		for(int j=i;j<n;++j)sum+=j+1;
	sum<<=1;
	sum+=(n*(n+1))>>1;
	cout<<sum<<' '<<(n<<1)<<'\n';
	for(int i=0;i<n;++i){
		cout<<1<<' '<<i+1;
		for(int j=0;j<n;++j)cout<<' '<<n-j;
		cout<<'\n';
		cout<<2<<' '<<i+1;
		for(int j=0;j<n;++j)cout<<' '<<n-j;
		cout<<'\n';
	}
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
