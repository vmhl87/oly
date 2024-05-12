// Sliding Window Median  -  https://cses.fi/problemset/task/1076/
// This is pretty trivial with ordered_set, but I decided to use some
// goofy multiset pointer stuff. Basically, it mantains a pointer at
// the median of the multiset, and depending on if the elements that
// are added and removed from the sliding window are before or after
// said pointer, the pointer is incremented or decremented.
// Really hacky, but works.

#include <iostream>
#include <queue>
#include <set>

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);
	int n, k; std::cin >> n >> k;
	// to remove elements from the set in the right order, we also
	// mantain a queue
	std::multiset<int> s;
	std::queue<int> q;
	// fill multiset with initial window
	for(int i=0; i<k; ++i){
		int t; std::cin >> t;
		s.insert(t);
		q.push(t);
	}
	// x = pointer to median element
	auto x = s.begin();
	for(int i=0; i<(k-1)>>1; ++i) ++x;
	std::cout << *x;
	// loop through the rest of the values and process
	for(int i=k; i<n; ++i){
		std::cout << ' ';
		// fr = change to forward count of elements (if there are
		// overall more elements added ahead of the median, fr is
		// positive, and x needs to be incremented)
		int t, fr = 0; std::cin >> t;
		// if the currently added element is bigger than the median,
		// it will increase the forward count, otherwise, it will
		// increase the backward count
		if(t < *x) --fr;
		else ++fr;
		// removal is really weird when there is only one element
		// in the multiset, so we just hardcode it
		if(s.size() == 1){
			x = s.end();
			s.insert(t);
			s.erase(s.find(q.front()));
			x = s.begin();
			fr = 0;
		// otherwise, if the removed element is less than or greater
		// than the median, we update the forward count accordingly
		}else if(q.front() < *x) ++fr;
		else if(q.front() > *x) --fr;
		// if the removed element has the same value as the median we
		// need to be careful that we aren't trying to remove the
		// value at x, because that will cause a hang
		else{
			// we do a goofy incremenet to push x forward or smth
			if(s.find(q.front()) == x) s.insert(t), ++x, --fr;
			else ++fr;
		}
		// removal and insertion
		if(s.size() > 1){
			s.erase(s.find(q.front()));
			// sometimes insertion has already happened because of
			// goofies and it needs to be handled
			if(s.size() < k) s.insert(t);
		}
		// update queue
		q.push(t);
		q.pop();
		// increment x
		if(fr > 0) ++x;
		else if(fr < 0) --x;
		// print current median value
		std::cout << *x;
	}
	std::cout << '\n';
}
