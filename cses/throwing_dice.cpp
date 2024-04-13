// Throwing Dice  -  https://cses.fi/problemset/task/1096/
//
// We can make this problem recursive - let f(x) be the # of ways
// to create the sum x out of the numbers 1..6.
// Then observe that f(x) = f(x-1) + f(x-2) + ... + f(x-6).
// 
// However due to the input size (10^18) this is not a viable approach.
// We here use matrix exponentiation - from the recursive formula, we
// can generate a 6x6 matrix that can transform f(x), f(x+1), ... , f(x+5)
// into the values f(x+6), f(x+7), ... , f(x+11). Then by binary exp we can
// speed this up so our solution is essentially O(log n).

#include <iostream>
#include <vector>
using namespace std;

#define M 1000000007

// base matrix for transformation - upon first implementing this sol, I
// miscalculated this matrix, (specifically the cells (4, 0) and (4, 1)),
// and spent a while trying to figure out why my solution failed on large
// cases, thinking incorrectly that it was due to int overflow.
vector<long long> base={
	1, 1, 2, 4, 8, 16,
	1, 2, 3, 6, 12, 24,
	1, 2, 4, 7, 14, 28,
	1, 2, 4, 8, 15, 30,
	1, 2, 4, 8, 16, 31,
	1, 2, 4, 8, 16, 32
};

// multiply a vector by a matrix - this is necessary because our set of
// values f(x), f(x+1), ... , f(x+5) is represented as a 6x1 vector that
// we then multiply by a 6x6 matrix.
vector<long long> vmul(vector<long long> v,vector<long long>mat){
	// we don't need to worry about making this more efficient because the
	// constant factor is quite small, and O(log n) is extremely fast.
	vector<long long> ret(6);
	for(int i=0;i<6;++i)
		for(int j=0;j<6;++j)
			ret[i]+=(v[j]*mat[j*6+i])%M;
	for(int i=0;i<6;++i)ret[i]%=M;
	return ret;
}

// multiply a matrix by a matrix - this is n^3, but fast enough overall
vector<long long> mmul(vector<long long> m1,vector<long long> m2){
	vector<long long> ret(36);
	for(int i=0;i<6;++i)
		for(int j=0;j<6;++j)
			for(int a=0;a<6;++a)
				ret[i*6+j]+=(m1[i*6+a]*m2[a*6+j])%M;
	for(int i=0;i<36;++i)ret[i]%=M;
	return ret;
}

// similar to standard binary exponentiation with integers, but instead with
// matrices and vectors. works in O(log n)
vector<long long> bexp(vector<long long> v,vector<long long> mat,long long iter){
	long long p=1;
	while(p<=iter){
		if(p&iter)v=vmul(v,mat);
		mat=mmul(mat,mat);
		p<<=1;
	}
	return v;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	long long n;cin>>n;
	// the initial set of values I started with are actually the values
	// f(-5), f(-4), f(-3), ... , f(0) because they are simpler to use.
	vector<long long> v={0,0,0,0,0,1};
	v=bexp(v,base,1+(n-1)/6);
	// because our output is a set of 6 values, we need to extract the right one
	cout<<v[(n-1)%6]<<'\n';
}
