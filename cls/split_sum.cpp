#include <iostream>
using namespace std;

int main(){
	long long s;cin>>s;
	if(s==1){
		cout<<-1<<'\n';
		return 0;
	}
	long long a=2,n=0,m=2;
	while(m<=s){
		a+=2;m+=a;n++;
	}
	cout<<n<<'\n';
	return 0;
}
