#include <iostream>
using namespace std;

void test_case(){
	long long k;cin>>k;
	long long bound=9,last=0,step=9,level=1;
	while(bound<k){
		last=bound;
		step*=10;level++;bound+=step*level;
	}
	k-=last+1;
	bound=k/level+step/9;
	int place=level-k%level-1;
	step=1;while(place-->0)step*=10;
	bound/=step;cout<<bound%10<<'\n';
}

int main(){
	int n;cin>>n;
	while(n-->0)test_case();
}
