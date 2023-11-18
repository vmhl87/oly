#include <iostream>

int main(){
	long long n;std::cin>>n;
	long long target=n*n;
	target+=n;target/=2;
	if((n+1)%4>1){
		std::cout<<"NO\n";return 0;
	}else{
		target/=2;
		long long s=0;
		for(long long i=n;i>0;i--){
			s+=i;
			if(s>target){
				std::cout<<"YES\n"<<n-i+1-(target+i==s?1:0)<<'\n';
				for(long long j=n;j>i;j--)std::cout<<j<<' ';
				if(target+i!=s)std::cout<<target-s+i;
				std::cout<<'\n'<<i-1+(target+i==s?1:0)<<'\n';
				for(long long j=i;j>0;j--)if(j!=target-s+i)std::cout<<j<<' ';
				std::cout<<'\n';
				return 0;
			}
		}
	}
}
