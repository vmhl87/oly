#include <iostream>
using namespace std;

void test_case(){
	int a,b,c;cin>>a>>b>>c;
	// we put all of the 2-child nodes first,
	// and everything else hangs down. Because
	// each 2-child node increases the number
	// of leaves of the tree by 1, and initially
	// there is only 1 leaf, there will always
	// be exactly a+1 leaves on the tree. Each
	// 0-child node must be a leaf.
	// This is the only failiure case.
	if(c!=a+1){
		cout<<-1<<'\n';
		return;
	}
	// when we put all of the 2-child nodes
	// at the root of the tree, some might be
	// at a higher depth than others. We compute
	// the number of nodes at smaller depth, r,
	// and the number of nodes at larger depth, t.
	// We also store the smaller depth as `depth`
	int t=a+a+2;
	int depth=-2,r=1;
	// don't worry about the math going on - it is
	// pretty scuffed and stuff
	while(r<=t){
		r<<=1;depth++;
	}
	r>>=1;t-=r;r>>=1;r-=t>>1;
	// weird edge case where there are no 1-child
	// nodes idk
	if(!b){
		if(t)cout<<depth+1;
		else cout<<depth;
	// if all of the 1-child nodes fit into the
	// smaller depth region, we return the height of
	// the larger depth region
	}else if(b<=r)cout<<depth+1;
	// otherwise we fill optimally and find ending depth
	else{
		b-=r;
		cout<<depth+2+(b-1)/c;
	}
	cout<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
