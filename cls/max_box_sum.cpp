#include <iostream>
using namespace std;

int main(){
	int x,y,sum=0,t,bn=1,nct;cin>>x>>y;x*=y;
	bool has0=0;
	for(int i=0;i<x;i++){
		cin>>t;
		if(t<0){
			sum-=t;nct++;
			if(bn==1||t>bn)bn=t;
		}else sum+=t;
		if(t==0)has0=1;
	}
	if(nct%2==0||has0)cout<<sum;
	else cout<<sum+bn+bn;
	cout<<'\n';
}

/*
input width, height, numbers

int total, largest_negative, negative_count
bool has_zero

for number n:
	if n is negative:
		subtract n from total
		increment negative_count
		update largest_negative
	else: add n to total
	if n is 0: has_zero = true

if negative_count is even or has_zero: sysout(total)
else sysout(total + largest_negative*2)
*/
