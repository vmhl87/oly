#include <iostream>
using namespace std;

void test_case(){
	int n;cin>>n;
	int ret=0;
	int buf=0;bool init=0;
	for(int i=0;i<n;++i){
		int s;cin>>s;
		if(s){
			if(init)ret+=buf;
			buf=0;
			init=1;
		}else buf++;
	}
	cout<<ret<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
