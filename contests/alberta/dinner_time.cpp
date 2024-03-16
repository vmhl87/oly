#include <iostream>
using namespace std;

int main(){
	int n;cin>>n;
	long long p=0,g=0,ret=1;
	while(n--){
		char d;cin>>d;
		long long m;cin>>m;
		if(d=='P'){
			if(g>p&&g<=p+m)ret++;
			p+=m;
		}else{
			if(p>g){
				if(g+m>p){
					ret+=p-g;
				}else{
					ret+=m;
				}
			}
			g+=m;
		}
	}
	cout<<ret<<'\n';
}
