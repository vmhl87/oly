#include <iostream>
using namespace std;

void test_case(){
	int n;cin>>n;
	bool w[n];for(int i=0;i<n;++i)w[i]=0;
	int m=0;
	for(int i=0;i<n;++i){
		if(i)cout<<' ';
		int p;cin>>p;
		// assume not new
		int a=m-p;
		// check if impossible
		if(a<0||a>=n||a==m||w[a]){
			cout<<m;w[m]=1;
			while(w[m])m++;
		}else{
			w[a]=1;
			cout<<a;
		}
	}
	cout<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
