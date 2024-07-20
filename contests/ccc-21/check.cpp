#include <iostream>
#include <set>

using LL = long long;

int main(){
	int n, m, k; std::cin >> n >> m >> k;

	std::set<int> row, col;

	for(int i=0; i<k; ++i){
		char c; std::cin >> c;
		int w; std::cin >> w;

		if((c == 'R' ? row : col).count(w))
			(c == 'R' ? row : col).erase(w);
		else (c == 'R' ? row : col).insert(w);
	}

	// ans is literally just rows + cols - intersect*2
	
	LL ret = (LL)m * row.size() + (LL)n * col.size();

	ret -= 2*((LL)row.size() * col.size());

	std::cout << ret << '\n';
}
