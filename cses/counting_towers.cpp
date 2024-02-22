/*  Counting Towers

	This problem requires us to break down a 2 by n
	rectangle into other rectangles of integer side
	length. The obvious bruteforce is far too slow.
	
	I realized that I could use dynamic programming
	by breaking down the finished 2 by n rectangle
	into the 2 by n-1 rectangle that consisted of
	all of the cells in the finished rectangle besides
	one, and divide that, etc.
	
	To store the state of the unfinished 2 by n-1, I
	realized that I could just care about the top of
	the rectangle, because that would be the part that
	would be added upon.
	
	I found six distinct states for the top:
	
		+-+-+    +-+ +    + +-+
		| | |    | | |    | | |
	
		+ + +    +   +    +---+
		| | |    |   |    |   |
	
	An open face (such as + +) indicates that the top
	of the 2 by n-1 was cut in the middle of a rectangle,
	and a closed face (like +-+) means that a rectangle
	ends there. It turns out that we only need these six
	states, and knowledge about how to go from one state
	to another, to calculate the answer.
*/

#include <iostream>
using namespace std;

#define MOD 1000000007

// for efficiency, if we have already calculated a count,
// we can store it in ways and set the appropriate element
// in fin. (finished)
long long ways[1000001][6];
bool fin[1000001][6];

// (rel)ationship mapping - rel[3][0] is true, because
// a rectangle ending in state 3 can be extended into
// a rectangle with a higher height ending in state 0.
// additionally we can prove that there is only one way
// to go from state a to state b, if possible.
bool rel[6][6]={
	{1,1,1,1,1,1},
	{1,1,1,1,0,0},
	{1,1,1,1,0,0},
	{1,1,1,1,0,0},
	{0,0,0,0,1,1},
	{1,1,1,1,1,1}
};

// this method uses induction to calculate the # of ways
// to construct a tower with height h and ending state t
int towerways(int h,int t){
	// base case: when height is 1, there is always only
	// one construction
	if(h==1)return 1;
	// if this value is already calculated, pull from storage
	if(fin[h][t])return ways[h][t];
	int ret=0;
	// loop through all possible next states, and if possible,
	// (using the relation mapping) we add the number of ways
	// to construct a tower with lower height and that state
	for(int i=0;i<6;i++)
		if(rel[i][t])
			ret=(ret+towerways(h-1,i))%MOD;
	// now that the value is computed, set it in storage
	fin[h][t]=1;ways[h][t]=ret;
	return ret;
}

// not really necessary, but a cleaner way to find the ways
// to construct a "finished" tower - one that has no open
// faces in it, which correspond to states 0 and 5
int allways(int h){
	int ret=0;
	ret=(ret+towerways(h,0))%MOD;
	ret=(ret+towerways(h,5))%MOD;
	return ret;
}

void test_case(){
	int n;cin>>n;
	cout<<allways(n)<<'\n';
}

int main(){
	// zero out finished array, because no calculations are
	// finished at this point
	for(int i=0;i<1000001;i++)
		for(int j=0;j<5;j++)
			fin[i][j]=0;
	int t;cin>>t;
	while(t-->0)test_case();
}
