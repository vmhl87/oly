#include <iostream>
using namespace std;

int main(){
	int n,x;cin>>n>>x;
	int ret=0,a[n];
	int csum=0,bp=0;
	for(int i=0;i<n;i++){
		cin>>a[i];csum+=a[i];
		if(csum==x)ret++;
		while(csum>x){
			csum-=a[bp++];
			if(csum==x)ret++;
		}
	}
	cout<<ret<<'\n';
}
