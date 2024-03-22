#include <iostream>
using namespace std;

void test_case(){
	int n,x;cin>>n>>x;
	int p[n];
	for(int i=0;i<n;++i)cin>>p[i];
	int real=0;
	for(int i=0;i<n;++i)if(p[i]==x){real=i;break;}
	int l=1,r=n+1;
	while(l<r-1){
		int m=(r+l)/2;
		// compare m, p[m], real
	}
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
