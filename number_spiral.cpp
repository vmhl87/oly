#include <iostream>

void test_case(){
	long long x,y;std::cin>>y>>x;
	if(y>=x){
		std::cout<<4*(y/2)*(y/2)+y%2+(x-1)*(2*(y%2)-1);
	}else{
		std::cout<<(2*((x+1)/2)-1)*(2*((x+1)/2)-1)+1-x%2-(y-1)*(2*(x%2)-1);
	}
	std::cout<<'\n';
}

int main(){
	int n;std::cin>>n;
	while(n-->0)test_case();
}
