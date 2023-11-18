#include <iostream>

int main(){
	int n,ret=0;std::cin>>n;
	while(n>0){
		ret+=n/5;
		n/=5;
	}
	std::cout<<ret;
}
