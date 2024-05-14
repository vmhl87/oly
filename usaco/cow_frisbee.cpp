// Cow Frisbee  -  https://usaco.org/index.php?page=viewproblem2&cpid=1183
//
// Each cow can only see, to its left, the cows which form a monotonically
// decreasing sequence starting from the maximum. For example:
//     3 5 4 2 [6] 1  <-  the 6 can only see (5, 4, 2)
// We can simulate this by storing a stack of the current decreasing seq,
// and when we encounter a new cow, by iterating to the right, we pop
// items off of the stack before pushing this new cow to mantain decreasingness.
// for example:
//     stack = (5, 4, 2), cow = 3: stack will become (5, 4, 3) by popping the 2

#include <iostream>
#include <array>
#include <stack>

int main(){
	int n; std::cin >> n;
	long long ret = 0;
	
	// because we need to compute the sum of differences in positions,
	// each frame of the stack must hold not only the height of the cow
	// but also its position
	std::stack<std::array<int, 2>> v;

	// we can get away with inputting on the go
	for(int i=0; i<n; ++i){
		int t; std::cin >> t;

		// because the stack must be decreasing, if the current top of the
		// stack is less than the current cow, we must pop it off
		while(v.size() && v.top()[0] < t){
			// when popping off of the stack, we also add to our sum total
			// the difference in positions
			ret += i - v.top()[1] + 1, v.pop();
		}

		// after popping the stack, if there is still an item on it (like
		// in our example, after popping the 2 off, there is (5, 4)) then
		// this top cow can throw the frisbee to our current cow. we process
		// this here
		if(v.size()) ret += i - v.top()[1] + 1;

		// add to stack, it is now guaranteed nondecreasing
		v.push({t, i});
	}

	std::cout << ret << '\n';
}
