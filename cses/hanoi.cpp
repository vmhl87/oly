#include <iostream>
using namespace std;

void move(int n,int s,int e){
	if(!n)return;
	int o=6-s-e;
	move(n-1,s,o);
	cout<<s<<' '<<e<<'\n';
	move(n-1,o,e);
}

int main(){
	int n;cin>>n;
	cout<<(1<<n)-1<<'\n';
	move(n,1,3);
}
