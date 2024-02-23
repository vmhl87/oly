#include <iostream>
using namespace std;

#define MOD 1000000007

int main(){
	int n;cin>>n;
	int fact[n][2];
	for(int i=0;i<n;++i){
		cin>>fact[i][0]>>fact[i][1];
	}
	long long num=1;
	for(int i=0;i<n;++i)
		num=(num*(fact[i][1]+1))%MOD;
	cout<<n<<' ';
	
	cout<<'\n';
}
