#include <iostream>
using namespace std;

int main(){
	int n,h=0,ret=0;cin>>n;
	while(n-->0){
		int t;cin>>t;
		if(t>h)ret+=t-h;
		h=t;
	}
	cout<<ret<<'\n';
	return 0;
}

/*

13
7 1234567
5 12345
6 123458
6 123458
9 1234589{10}{11}
3 123
2 12
1 1
5 1{12}{13}{14}{15}
7 1{12}{13}{14}{15}{16}{17}
3 1{12}{13}
5 1{12}{13}{18}{19}
3 1{12}{13}

*/
