/*  Range Xor Queries  -  https://cses.fi/problemset/task/1650/

	This problem is quite trivial. We apply the same idea
	as we can use for standard range sums, except instead of
	adding and subtracting to compute ranges, we use binary
	xor.
*/

#include <iostream>
using namespace std;

int main(){
	int n,q;cin>>n>>q;
	int val[n+1];val[0]=0;
	for(int i=0;i<n;i++){
		int t;cin>>t;
		val[i+1]=t^val[i];
	}
	for(int i=0;i<q;i++){
		int a,b;cin>>a>>b;a--;b--;
		cout<<(val[b+1]^val[a])<<'\n';
	}
}
