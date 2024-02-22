/*  Counting Numbers

	This problem is quite complex! We can break it down into
	several sub-problems.
	
	First, we need to count the number of good numbers between
	a and b, but we can break this down into:
		# of good numbers <= b - # of good numbers <= a
	
	Next, we need a good way to compute the number of good #s.
	We can use a form of induction for this: rather than checking
	every single number less than b, we can try to construct the
	number one digit at a time.
	
	This is actually quite easy to do:
	
		# of good numbers with length n ending in x =
			sum of (good #s with length n-1 ending in {0..9 but not x})
	
	This recursion works because there will never at any point be
	two adjacent digits with equal value.
	
	Our base case is where the length of the number is 1, in which
	there is only 1 possible number.
	
	However, this isn't useable yet. This will give us the number of
	good numbers with a certain length, but we want a specific bound.
	To do this I broke down the problem once again.
	
	Let's say our upper bound is 3125. My algorithm broke this down
	into a series of ranges:
	
		3120 - 3125
		3100 - 3120
		3000 - 3100
		0000 - 3000
	
	These might seem odd, but these ranges are actually approximately
	similar to the following:
		0 - 5
		0 - 20
		0 - 100
		0 - 3000
	
	These are actually ranges we can compute with what we have so far.
	Our sequence generation function (let's call it seq(end, length))
	can find the numbers from 0 to 3000 like so:
	
		  seq(2, 4)   good numbers between 2000 and 2999
		+ seq(1, 4)   good numbers between 1000 and 1999
		
		+ seq(0, 4)   good numbers between 0100 and 0999
		+ seq(0, 3)   good numbers between 010 and 099
		+ seq(0, 2)   good numbers between 01 and 09
	
	Note that we are actually using seq() such that the "end" digit
	is the biggest one; this gives us more control.
	
	We are missing a few edge cases, such as 0, but these ranges
	are a good enough approximation for our algorithm to work with them.
	
	In my implementation, I defined a fract() function to (fract)ure a
	number n into its component ranges.
	
	fract() accepted a number n and a zeroes count, like so:
	
		3125 ->
		
			3120 - 3125   n=3125 z=0
			3100 - 3120   n=312  z=1
			3000 - 3100   n=31   z=2
			0000 - 3000   n=3    z=3
	
	The reason why we need this is because the range 3100-3120 is not
	as simple as just the range 00-20, because we do have to account
	for the rest of the number. For example, in the range 00-20, the
	number 12 is valid, but in the range 3100-3120, this corresponds
	to 3112, which is not valid. Additionally, in the range 3000-3100,
	we can't have the number 001, because that would map to 3001.
*/

#include <iostream>
using namespace std;

// we store already calculated sequence counts to improve speed
long long dp[19][10];
bool f[19][10];

// method that calculates the # of good sequences ending in end and
// with length n (end means biggest digit, so 3125 -> 3)
long long seq(int end,int n){
	// base case: when length is 1, only 1 possibility
	if(n==1)return 1;
	// if already calculated, return that
	if(f[n][end])return dp[n][end];
	long long ret=0;
	// loop through possible preceding digits; if it is not
	// the same as our current ending digit, it is a possible match
	for(int i=0;i<10;i++)
		if(i!=end)ret+=seq(i,n-1);
	// store calculation
	f[n][end]=1;dp[n][end]=ret;
	return ret;
}

// process fracture n with zeroes z
long long fract(long long n,int z){
	// when n is less than 10, this is the last range,
	// and we can and should count all possibilities (this includes
	// sequences with multiple leading zeroes)
	if(n<10){
		long long ret=0;
		// if there are no zeroes, this is the only fracture,
		// so we need to include n in our final count. Normal
		// fractures account for the count themselves, but this
		// case isn't processed normally.
		if(!z)ret=1;
		// stage 1 - count sequences of same length
		// in our example of 3125, this would be the range 0-3000,
		// and in this stage we calculate the ranges 1000-1999 and
		// 2000-2999.
		for(int i=1;i<n;i++)
			// all ends from 1 up to (and not including) n are
			// valid. The length of the sequence is the number
			// of trailing zeroes plus one; remember that the
			// range 0-3000 would be represented as n=3 z=3
			ret+=seq(i,z+1);
		// stage 2 - count sequences with leading zeroes
		// in our example, this would be 100-999, 10-99, 1-9
		// here, i represents the length of the sequence
		for(int i=1;i<=z;i++)
			// to avoid extra leading zeroes that we aren't accounting
			// for, we actually count these sequences with 1 more length
			// and an endpoint of 0 (so 100-999 would be 0100 - 0999)
			ret+=seq(0,i+1);
		return ret;
	}
	// otherwise, this isn't the ending fracture
	// we find the units digit (u) of n and remove it from n
	int u=n%10;n/=10;
	// now we need to check if this range is even possible
	// for example, when fracturing 31125, the range 31120-31125
	// is invalid because it contains two adjacent identical digits
	// to do this, we clone n
	long long t=n;
	// we also store the last digit we saw to compare
	int last=-1;
	// while t is nonzero
	while(t){
		// if the last digit of t is identical to the previously
		// seen one, we know this range isn't possible
		if(t%10==last)return 0;
		// update last digit
		last=t%10;
		// cut last digit off of t
		t/=10;
	}
	// at this point we know the range is ok, so we can cut off
	// the rest of n
	n=n%10;
	long long ret=0;
	// we only count n itself in the count if we are processing
	// the topmost range, which happens when there are 0 trailing
	// zeroes. Also, we need to check if the units digit is identical
	// to the last digit of n, because if it does, then n is not valid.
	if(!z&&n!=u)ret=1;
	// we iterate through all possible units digits and count the ones
	// that don't conflict with n
	for(int i=0;i<u;i++)if(i!=n)
		// the sequence will have length one more than the zeroes count:
		// in our example the range 3100 - 3140 (1 zero) would form
		// numbers such as 3123, which is represented as 23, and has
		// 2 digits
		ret+=seq(i,z+1);
	return ret;
}

// method to fracture n into its component ranges
long long all(long long n){
	// 0 never gets counted in any of our ranges
	long long ret=1;
	// z = current zero count
	int z=0;
	// while n is nonzero
	while(n){
		// fracture n with the zero count
		ret+=fract(n,z);
		// cut the last digit off of n, and advance zero count
		n/=10;z++;
	}
	return ret;
}

int main(){
	// set computational storage
	for(int i=0;i<19;i++)
		for(int j=0;j<10;j++)
			f[i][j]=0;
	long long a,b;cin>>a>>b;
	// handling the range a-b instead of 0-a or 0-b is a bit
	// complex and to actually include a we need to subtract off
	// the number of good numbers less than or equal to a-1; this
	// obviously causes issues when a is 0
	long long ret=all(b);
	if(a>0)ret-=all(a-1);
	cout<<ret<<'\n';
}
