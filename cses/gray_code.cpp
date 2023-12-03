#include <iostream>
using namespace std;

int main(){
	int n,m=1;cin>>n;
	int p2[n+1];p2[0]=1;
	for(int i=0;i<n;i++){
		m*=2;p2[i+1]=m;
	}
	for(int i=0;i<m;i++){
		for(int j=n;j>0;j--){
			cout<<((i+p2[j-1])/p2[j])%2;
		}
		cout<<'\n';
	}
}
