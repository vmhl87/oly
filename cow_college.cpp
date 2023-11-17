#include <iostream>
#include <algorithm>

int main(){
	int n;std::cin>>n;
	int t[n];for(int i=0;i<n;i++)std::cin>>t[i];
	std::sort(t,t+n);
	long long opt=0,m;
	int ot=t[n-1];
	for(int i=0;i<n;i++){
		m=n-i;m*=t[i];
		if(m>opt){opt=m;ot=t[i];}
	}
	std::cout<<opt<<' '<<ot<<'\n';
}
