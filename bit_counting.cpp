#include <iostream>
using namespace std;

int main(){
	long long n,k,ret=0;
	cin>>n>>k;
	for(long long i=1;i<=n;i*=k){ // loop thru place values
	
		// basically, we can look at each place value seperately,
		// and observe a pattern: (ex. n = 13, k = 3, i = 3)
		//   0 0 0 1 1 1 2 2 2 0 0 0 1
		// notice that these values are divided into blocks
		// of k, and that the value of block n is n%k. We can
		// use this to calculate the number of values == 1:
		//   1. count number of blocks with value 1, and multiply
		//      by i
		//   2. check if the last block (the unfinished one) has
		//      value 1: if it does, find out how many values
		//      are in it
		// this is relatively simple to implement
		
		// find number of blocks of i elements up till n:
		//   blocks = ((n+1)/i)
		// find number of blocks which will be of value 1:
		// we calculate this by shifting all the blocks over
		// by 1 in the negative direction, and then count number
		// of blocks of value 0 (divide by k and round up)
		//   val_1 = (((blocks-1)+k-1/k)
		// check if the last (possibly incomplete) block is
		// of value 1:
		// index of last block will always be # blocks + 1
		//   if( (blocks+1) % k == 1 ) {
		// find number of elements in this last block:
		// since the last element is n, and we start blocks from
		// 0, there are n+1 total elements
		//   n_elem = (n+1)%i
		// add these all up:
		//  ret += val_1*i + n_elem
		
		ret+=i*((((n+1)/i)+k-2)/k);
		if(((n+1)/i)%k==1)ret+=(n+1)%i;
	}
	cout<<ret<<'\n';
	return 0;
}
