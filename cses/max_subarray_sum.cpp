#include <iostream>
using namespace std;

int main(){
	ios::sync_with_stdio(false);cin.tie(0);
	int n;cin>>n;
	long long max=0,best=0;
	bool nset=1;
	for(int i=0;i<n;i++){
		long long t;cin>>t;
		if(max<0)max=0;
		max+=t;
		if(max>best||nset){
			best=max;nset=0;
		}
	}
	cout<<best<<'\n';
}
