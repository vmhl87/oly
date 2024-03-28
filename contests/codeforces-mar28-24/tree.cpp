#include <iostream>
using namespace std;

void test_case(){
	int a,b,c;cin>>a>>b>>c;
	if(c!=a+1){
		cout<<-1<<'\n';
		return;
	}
	int t=a+a+2;
	int depth=-2,r=1;
	while(r<=t){
		r<<=1;depth++;
	}
//cout<<"at depth "<<depth<<" (size "<<r<<")\n";
	r>>=1;t-=r;r>>=1;r-=t>>1;
//cout<<"tr "<<t<<','<<r<<'\n';
	if(!b){
		if(t)cout<<depth+1;
		else cout<<depth;
	}else if(b<=r)cout<<depth+1;
	else{
		b-=r;
		cout<<depth+2+(b-1)/c;
	}
	cout<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
