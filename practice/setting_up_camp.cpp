// codeforces round 935 problem A

#include <iostream>
using namespace std;

int main(){
	int t;cin>>t;
	while(t--){
		int a,b,c;cin>>a>>b>>c;
		a+=b/3;b%=3;
		if(b){
			if(c+b>=3){
				a++;c-=(3-b);b=0;
			}else{
				cout<<-1<<'\n';
				continue;
			}
		}
		if(c)a+=1+(c-1)/3;
		cout<<a<<'\n';
	}
}
