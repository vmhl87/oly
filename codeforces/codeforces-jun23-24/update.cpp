#include <algorithm>
#include <iostream>

void test_case(){
	int n, m; std::cin >> n >> m;

	char res[n]; for(int i=0; i<n; ++i) std::cin >> res[i];

	int ind[m]; for(int i=0; i<m; ++i) std::cin >> ind[i], --ind[i];

	char mask[m]; for(int i=0; i<m; ++i) std::cin >> mask[i];

	std::sort(ind, ind+m), std::sort(mask, mask+m);

	int ptr = 0, at = -1;

	for(int i=0; i<m; ++i){
		if(ind[i] == at) continue;

		res[at = ind[i]] = mask[ptr++];
	}

	for(char c : res) std::cout << c; std::cout << '\n';
}

int main(){
	int n; std::cin >> n;

	while(n--) test_case();
}
