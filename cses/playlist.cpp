// Playlist  -  https://cses.fi/problemset/task/1141/
// Basically a two pointer alg, except we mantain a set
// of all values currently in the sliding window and we
// always mantain uniqueness inside said set.
// We can prove that both pointers must always increment
// right, because if the range [a, b] is the maximum
// range ending in b, then [a, b+1] is the theoretical
// maximum range ending in b+1, as [a-1, b+1] will
// contain [a-1, b] which is not possible, as we know
// that [a, b] is the maximum range ending in b.

#include <iostream>
#include <queue>
#include <set>

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);
	int n; std::cin >> n;
	// queue to pop songs off in order, set to store which
	// songs are in the current sliding window
	std::queue<int> q;
	std::set<int> s;
	// running maximum length
	int m = 0;
	// repeat over all vals
	while(n--){
		int t; std::cin >> t;
		// if t is already in the set, erase values from
		// the set until t is no longer in the set
		while(s.count(t)){
			s.erase(q.front());
			q.pop();
		}
		// insert t into the set and queue
		s.insert(t);
		q.push(t);
		// update running max
		m = (s.size() > m ? s.size() : m);
	}
	std::cout << m << '\n';
}
