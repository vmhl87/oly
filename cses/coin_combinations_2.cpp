// Coin Combinations II  -  https://cses.fi/problemset/task/1636/
//
// This was quite an interesting problem. I knew the general idea
// of how to solve it, but implementing efficiently enough proved
// to be quite an interesting challenge. The time complexity was
// theoretically good enough, however, many of my previous
// implementations failed.
//
// I went through several iterations of the algorithm, both the
// recursive and iterative approaches, and realized that iterative
// was the only reasonably performant approach. I eventually ended
// up with a double nested loop, which was too slow but by not
// very much - and then I realized that I could remove the nesting
// and simply use one loop. This also enabled me to do away with
// the double arrays, which I assume helped the entire array fit
// into cache for performance.

#include <iostream>
using namespace std;

#define M 1000000007
#pragma GCC optimize("O3")

long long a[1000001];
int main(){
	int n,x;cin>>n>>x;a[0]=1;
	while(n--){
		long long v;cin>>v;
		for(int i=0;i<=x-v;++i){
			a[i+v]+=a[i];
			if(a[i+v]>=M)a[i+v]-=M;
		}
	}
	cout<<a[x]<<'\n';
}
