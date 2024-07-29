// How Does the Rook Move?  -  https://codeforces.com/contest/1957/problem/C
//
// First we can make the observation that the set of available columns and
// available rows will always be identical. Notice that when the player
// places a rook at (r,c), then both values r and c will be removed from
// the set of available columns/rows. Furthermore, we can notice that the row
// r will be taken by player and the row c will be taken by computer, and opposite
// for the columns.
//
// For the sake of simplicity, let us ignore the diagonal formed by cells (x,x).
// If we look at who controls each column, this set must be the inverse of
// the set of who controls each row - if player controls column x, computer controls
// row x. We can then notice that if we only look at the mapping of who controls each
// column and row, there are x! ways to construct a valid configuration of rooks
// where x is the number of columns that are controlled by the player.
//
// To compute the number of ways to map 2*k columns such that k are controlled by
// player and k are controlled by computer, we compute nck(2*k, k).
//
// To account for the player possibly setting rooks along the diagonal, we can look at
// the problem from a constructive persepective. We pick some number 0 <= i <= n/2
// columns for the player to control, and therefore i columns for the computer
// to control, and then the remaining columns and rows must be controlled by rooks
// along the diagonal, trivially.

#include <iostream>
#include <cmath>
using namespace std;

// modulus
#define M 1000000007

// dp-accelerated factorial
long long dp[300001];
long long fact(int n){
	if(dp[n])return dp[n];
	long long ret=1;
	if(n>1)ret=(fact(n-1)*n)%M;
	dp[n]=ret;
	return ret;
}

// modular inverse of i, mod M - required for nck()
long long inv(long long i){
	long long ret=1,p=1,p2=M-2;
	while(p<p2){
		if(p2&p)ret=(ret*i)%M;
		i=(i*i)%M;
		p<<=1;
	}
	return ret;
}

// standard nck() - n! / (k! (n-k)!) using modular inverse
long long nck(int n,int k){
	return (fact(n)*inv((fact(k)*fact(n-k))%M))%M;
}

void test_case(){
	int n,k;cin>>n>>k;
	// to account for the moves that already happened we can
	// just 'virtually shrink' the board because the columns
	// and rows that start out occupied essentially do not exist
	// to us
	for(int i=0;i<k;++i){
		int r,c;cin>>r>>c;
		if(r==c)++n;
		n-=2;
	}
	long long ret=0;
	// choose i - the number of mirrored moves
	for(int i=0;i<=n>>1;++i){
		// there will be n-(i*2) columns and rows that aren't covered
		// by the mirrored moves, and will be covered instead on the
		// diagonal - here we choose which those will be
		long long way=nck(n,i<<1);
		// choose which out of the i*2 columns that are controlled by
		// mirrored moves will be controlled by player
		long long choice=nck(i<<1,i);
		// permute (cross-link)
		choice=(choice*fact(i))%M;
		ret=(ret+way*choice)%M;
	}
	cout<<ret<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
