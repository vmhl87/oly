/*  Sum of Three Values

	We can show that this is doable in N^2 log N time
	by bruteforcind the first and second elements and
	binary searching for the third
*/

#include <algorithm>
#include <iostream>
using namespace std;

// datastructure with comparison operators
typedef struct val{
	long long v;
	// preserves initial location
	int i;
	bool operator<(const val o)const{
		return v<o.v;
	}
	bool operator==(const val o)const{
		return v==o.v;
	}
}val;

int main(){
	int n;long long x;
	cin>>n>>x;
	val ns[n];
	for(int i=0;i<n;i++){
		cin>>ns[i].v;
		ns[i].i=i+1;
	}
	sort(ns,ns+n);
	// bruteforces first and second indexes (i,j)
	for(int i=0;i<n-2;i++){
		for(int j=i+1;j<n-1;j++){
			// due to the way builtin binary search works
			// we need to construct a new val object and fill
			// it with the appropriate value
			val target;target.v=x-ns[i].v-ns[j].v;
			// yes
			if(target.v<=0)break;
			// find range of values that we can use (there may
			// be multiple, and we need to make sure we don't use
			// the same number twice, which may happen when i or j
			// correspond to an element of the right value
			auto lower=equal_range(ns,ns+n,target);
			// first check if we even found the right value
			if((*lower.first).v==target.v){
				// loop through all possible positions, and check for
				// overlap with i,j
				for(auto k=lower.first;k!=lower.second;k++)
					if((*k).i!=ns[i].i&&(*k).i!=ns[j].i){
						cout<<(*k).i<<' '<<ns[i].i<<' '<<ns[j].i<<'\n';
						return 0;
					}
			}
		}
	}
	cout<<"IMPOSSIBLE\n";
}
