#include <iostream>
#include <set>

std::set<int> seen;
int n;

int cycle(int i){
	return ((i&1)<<(n-1)) | (i>>1);
}

int main(){
	std::cin >> n;
	for(int i=0; i<1<<n; ++i){
		int o = i;
		bool skip = 0;
		for(int j=0; j<n; ++j){
			o = cycle(o);
			if(seen.count(o)) skip = 1;
		}
		if(!skip) seen.insert(o);
	}
	std::cout << seen.size() << '\n';
}
