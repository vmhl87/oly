#include <iostream>
#include <map>
#include <set>

int a[300000];

void test_case(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i];
	std::map<int, int> lastoc;
	for(int i=0; i<n; ++i) lastoc[a[i]] = i;
	std::set<int> bounds;
	// bounds will be distinct by nature
	for(const auto &[a, b] : lastoc) bounds.insert(b);
	std::set<int> used;
	std::map<int, int> cand;
	int right = 0;  // current searching loc
	int left = 0;  // cleanup
	int parity = 0;  // neg
	std::cout << bounds.size() << '\n';
	while(bounds.size()){
		// infill set up till lastoc
		// we want smallest bound
		int bound = *(bounds.begin());
		// add to set
		for(; right<=bound; ++right)
			if(!used.count(a[right]))
				++cand[a[right]];
		//std::cout << left << " - " << right << " have: ";
		//for(const auto &[x, y] : cand) std::cout << x << ' ';
		//std::cout << '\n';
		// pick and process
		//int best = a[right];
		//if(cand.size()){
			//if(parity) best = std::min(best, *cand.begin());
			//else best = std::max(best, *(--cand.end()));
		//}
		int best;
		if(cand.size()){
			if(parity) best = (cand.begin())->first;
			else best = (--cand.end())->first;
		}
		std::cout << best << ' ';
		cand.erase(best);
		used.insert(best);
		bounds.erase(lastoc[best]);
		parity ^= 1;
		for(; a[left] != best; ++left)if(!used.count(a[left])){
			--cand[a[left]];
			if(!cand[a[left]]) cand.erase(a[left]);
		}
	}
	std::cout << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test_case();
}
