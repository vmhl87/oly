#include <iostream>

int main(){
	int n,ret=1;std::cin>>n;
	while(n-->0){
		ret*=2;
		if(ret>1000000007)ret-=1000000007;
	}
	std::cout<<ret;
}
