#include <iostream>
using namespace std;

int main(){
	int n;cin>>n;
	char start='-',last='-';int len=0,min=0,max=0,step=2;
	while(n-->0){
		char c;cin>>c;
		if(c=='F')len++;
		else{
			if(len>0){
				if(start=='-'){
					max+=len;
					step=1;
				}else if(start==c){
					max+=len+1;
					min+=(1-len%2);
				}else{
					max+=len;
					min+=len%2;
				}
			}
			if(c==last){
				max++;min++;
			}
			start=c;
			len=0;
		}
		last=c;
	}
	if(len>0){
		max+=len;
		if(start=='-')max--;
		step=1;
	}
	cout<<1+(max-min)/step<<'\n';
	for(int i=min;i<=max;i+=step)cout<<i<<'\n';
	return 0;
}
