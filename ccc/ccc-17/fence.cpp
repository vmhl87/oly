#include <iostream>
#include <array>
#include <map>

// heights of each piece, compressed count of each height
int h[1000000];
std::array<int, 2> comp[2001];

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> h[i];

	// coordinate compress with map
	std::map<int, int> freq;
	for(int i=0; i<n; ++i) ++freq[h[i]];

	auto p = comp;
	for(const auto &[num, count] : freq) *(p++) = {num, count};
	n = p - comp;

	// determine all possible sizes of boards, and how
	// many different ones can be built
	std::map<int, int> board;

	for(int i=0; i<n; ++i){
		// with n planks of size x, floor(n/2) boards of
		// size x*2 can be made
		board[comp[i][0]*2] += comp[i][1]/2;

		// with n planks of size x and m planks of size y,
		// min(n+m) boards of size x+y can construct
		for(int j=i+1; j<n; ++j)
			board[comp[i][0]+comp[j][0]] += std::min(comp[i][1], comp[j][1]);
	}

	// best length of fence, # of different heights of this best length
	int len = 0, count = 0;

	for(const auto &[height, num] : board)
		if(num > len) len = num, count = 1;
		else if(num == len) ++count;

	std::cout << len << ' ' << count << '\n';
}
