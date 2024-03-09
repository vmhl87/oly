#include <algorithm>
#include <iostream>
using namespace std;

int main(){
	long long k,m,n;cin>>k>>m>>n;
	k%=(m+n);
	long long a=min(m,n);
	bool aw=((k/a)%2)>0;
	if(k>=m+n-a)aw=1;
	if(aw)cout<<"Alex\n";
	else cout<<"Barbossa\n";
}
