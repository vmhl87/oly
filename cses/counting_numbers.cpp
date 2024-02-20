#include <iostream>
using namespace std;

long long dp[19][10];
bool f[19][10];

// # of sequences ending (biggest digit) in end with length n
long long seq(int end,int n){
//cout<<"   seq called on "<<end<<','<<n<<'\n';
	if(n==1)return 1;
	if(f[n][end])return dp[n][end];
	long long ret=0;
	for(int i=0;i<10;i++)
		if(i!=end)ret+=seq(i,n-1);
	f[n][end]=1;dp[n][end]=ret;
	return ret;
}

// n: number to fracture, z: hidden zeroes
long long fract(long long n,int z){
//cout<<"  received "<<n<<','<<z<<'\n';
	// edge case: n < 10
	if(n<10){
		// normally we don't count n
		long long ret=0;
		// we only count n when z=0, no preceding
		if(!z)ret=1;
		//  in our example, this would be 0000 - 2999 so
		//	we have to divide into sections: first
		//		2000 - 2999
		//		1000 - 1999
		//	then
		//		100 - 999
		//		10 - 99
		//		1 - 9
		// clip down n
		n=n%10;
		// stage 1
		for(int i=1;i<n;i++)
			//  everything from i000 to i999
			//	starts i, zeroes z -> length z+1
			ret+=seq(i,z+1);
		// stage 2
		for(int i=0;i<z;i++)
			// essentially a sequence of length i+1 starting in 0
			ret+=seq(0,i+2);
//cout<<"  return "<<ret<<'\n';
		return ret;
	}
	// split units digit from n
	int u=n%10;n/=10;
	// check for adjacent identical digits
	long long t=n;
	int last=-1;
	while(t){
		// if there is overlap, just return 0
//if(t%10==last)cout<<"  overlap\n";
		if(t%10==last)return 0;
		last=t%10;
		t/=10;
	}
	// we can assume no adj - discard rest of n
	n=n%10;
	// we don't count n unless special case
	long long ret=0;
	// z=0, n!=u
	if(!z&&n!=u)ret=1;
	//  in example: from 3125: the range 3100-3120 represented as
	//	312; we slice this down to n=1 u=2, so we iterate through all
	//	numbers starting 0 to u-1 ending in z zeroes - this would be
	//	from 3100 to 3119 (doesn't count n)
	for(int i=0;i<u;i++)if(i!=n)
		//  sequence in question has z zeroes so therefore z+1 length
		//	and starts with i (when z = 0, this is consistent)
		ret+=seq(i,z+1);
//cout<<"  return "<<ret<<'\n';
	return ret;
}

// find all from 0 to n, inclusive
long long all(long long n){
	// weird edge case
	if(!n)return 1;
//cout<<"process "<<n<<'\n';
	// account for 0
	long long ret=1;
	int z=0;
	int pow=1;
	while(n){
		// process last digit
//cout<<" fracture "<<(n-n%10)*pow<<" - "<<n*pow<<'\n';
		ret+=fract(n,z);
		n/=10;z++;pow*=10;
	}
	return ret;
}

// simple brute force
long long bforce(long long n){
	long long ret=0;
	for(long long i=0;i<=n;i++){
		int last=-1;
		long long s=i;
		bool w=1;
		while(s){
			if(s%10==last)w=0;
			last=s%10;
			s/=10;
		}
//cout<<i<<" does ";if(!w)cout<<"not ";cout<<"work\n";
		if(w)ret++;
	}
	return ret;
}

int main(){
	for(int i=0;i<19;i++)
		for(int j=0;j<10;j++)
			f[i][j]=0;
	long long a,b;cin>>a>>b;
//cout<<all(a)<<'\n'<<all(b)<<'\n';
	long long ret=all(b);
	if(a>0)ret-=all(a-1);
	cout<<ret<<'\n';
//	ret=bforce(b)-bforce(a-1);
//	cout<<ret<<'\n';
}
