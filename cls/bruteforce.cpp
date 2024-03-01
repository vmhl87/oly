#include <iostream>
#include <vector>
using namespace std;

#define MOD 100000000

// datastructure - stores an integer of arbitrary length
// by splitting it up into blocks of size MOD
typedef struct lint{
	vector<int> ints;
	// constructor
	lint():ints(1,0){}
	// the only operation we really need is addition
	void add(lint i){
		// keep track of carries
		int carry=0;
		for(int j=0;j<i.ints.size();j++){
			if(j>=ints.size())ints.push_back(0);
			ints[j]+=carry+i.ints[j];
			carry=ints[j]/MOD;
			ints[j]=ints[j]%MOD;
		}
		if(carry){
			if(i.ints.size()>=ints.size())
				ints.push_back(carry);
			else ints[i.ints.size()]+=carry;
		}
	}
	void add(int i){
		ints[0]+=i;
		int carry=ints[0]/MOD;
		ints[0]=ints[0]%MOD;
		if(carry){
			if(ints.size()<2)ints.push_back(carry);
			else ints[1]+=carry;
		}
	}
	// copy values from existing
	void set(lint i){
		ints=i.ints;
	}
	// print out
	void printseg(int i){
		if(i==ints.size()-1){
			cout<<ints[i];
			return;
		}
		int digits=0,s=ints[i];
		while(s){
			digits++;
			s/=10;
		}
		for(int i=0;i<8-digits;++i)
			cout<<'0';
		cout<<ints[i];
		return;
	}
	void print(){
		for(int i=ints.size()-1;i>=0;--i)
			printseg(i);
		cout<<'\n';
	}
}lint;

// storage array for computations we've already done - indexed
// by [n][x]; note that we do not need to store the # of seq
// ending in a string of 8 heads because that is what we compute
lint dp[100][7];
bool calc[100][7]; // automatically set to 0

// computes # of sequences of length n that end in a string of
// x consecutive heads
lint seq(int n,int x){
	// base case: n=0, all will return 0 except for x=0
	if(!n){
		lint ret;
		if(!x)ret.add(1);
		return ret;
	}
	// check if already computed
	if(calc[n][x])return dp[n][x];
	lint ret; // return value - auto set to 0
	// we create a sequence of length x by finding all sequences
	// of length x-1 and length n-1 - first we do need to account
	// for x=0 because that is a special case
	if(!x){
		// to create a string with 0 ending heads, we take any seq
		// with n-1 length and append a tail to it
		for(int i=0;i<8;++i)
			ret.add(seq(n-1,0));
	}else{
		// any seq of length n-1 with ending x-1
		ret.add(seq(n-1,x-1));
	}
	// set in computed array
	calc[n][x]=1;
	dp[n][x].set(ret);
	return ret;
}

int main(){
	lint allways;
	// we want all ways to construct a sequence of 8 heads - this
	// can take place by constructing a sequence of anywhere from
	// 0 to 92 flips not ending in any heads and adding 8 heads to it
	for(int i=0;i<93;++i)
		allways.add(seq(i,0));
	allways.print();
}
