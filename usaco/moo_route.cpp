/*  Moo Route

	Essentially just a greedy algorithm - go right
	until we can't, then go left until we can't,
	etc.
*/

#include <iostream>
using namespace std;

int main(){
	int n;cin>>n;
	int c[n];
	for(int i=0;i<n;i++)cin>>c[i];
	// p = position, dir = direction (r=1 l=0)
	int p=0;
	bool dir=1;
	// while position is nonzero or pos is 0 and
	// we aren't done traversing, traverse more
	while(p||c[0]){
		// update count at position
		if(dir)c[p]--;
		else c[p-1]--;
		// update position
		if(dir)p++;
		else p--;
		// print direction
		if(dir)cout<<'R';
		else cout<<'L';
		// if we are moving backwards and either
		// pos 0 (forced to go fwd) or can't go into
		// lower region (filled with 1 - must finish
		// rest) move fwd
		if(!dir&&(p==0||c[p-1]<=1))dir=1;
		// if we are moving fwd and are forced to
		// go back, or have traversed all of front,
		// we move back; this also error corrects for
		// the previous case (doesn't catch the case
		// where we are finished traversing and must
		// go back)
		if(dir&&(p==n||!c[p]))dir=0;
	}
	cout<<'\n';
}
